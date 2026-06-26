#include "std.h"
#include "da.h"
#include "fs.h"
#include "process.h"
#include "memory.h"
#include "time.h"

/* TODO: Check return of the functions */

/* General variables which is setted in main - set_general */
typedef struct general_s general_t;
struct general_s {
    bool verbose;
    bool always_make;
    sl_u8_t ar;
    sl_u8_t cc;
    sl_u8_t c_ext;
    sl_u8_t old_ext;
    sl_u8_t obj_ext;
    sl_u8_t crt_name;
    sl_u8_t c_flags;
    sl_u8_t so_flags;
    sl_u8_t ar_flags;
    sl_u8_t freestanding_flags;
    sl_u8_t build_yourself_flags;
};

/* Packed struct which is used in callbacks to pass data around */
/* Pointers used for smaller struct size - things which will live in the function scope */
typedef struct packed_s packed_t;
struct packed_s {
    general_t* general;
    std_t *std;
    path_t *build_dir;
    da_proc_t* procs;
    da_path_t* obj_files;
    path_t full;
    path_t ext;
};

void build_file(path_t* full_path, path_t* out_path, packed_t *pack, bool is_crt);
/* Callback for iterating the directory list */
void callback(sl_cstr_t* path, sl_cstr_t* name, bool is_dir, void* arg);
void make_libs(std_t* std, packed_t* pack);
bool build_yourself(std_t* std, packed_t* pack);
void set_flags(std_t* std, packed_t* pack);
void set_general(packed_t* pack);

error_t main
(std_t* std)
{
    /* Init variables */
    path_t src = {0}, build_dir = {0};
    general_t general = {0};
    packed_t pack = {0};
    da_proc_t procs = {0};
    da_path_t objs = {0};
    usz count = 0;

    /* Set basics */
    pack.general = &general;
    set_general(&pack);
    set_flags(std, &pack);
    pack.std = std;
    pack.build_dir = &build_dir;
    pack.procs = &procs;
    pack.obj_files = &objs;

    /* Check if its needed */
    if(!build_yourself(std, &pack)) { return success; }

    /* Allocate */
    /* TODO: 12 is for cpu thread */
    da_init(std->alloc, pack.procs, 12);
    da_init(std->alloc, &objs, 128);
    str_init(std->alloc, &pack.full, 128);
    str_init(std->alloc, &pack.ext, 128);
    str_from_cstr(std->alloc, &src, "./src/");
    str_from_cstr(std->alloc, &build_dir, "./.build/");

    /* Create '.build' directory if it does not exist */
    dir_mkdir_ifnot_exists(&build_dir);

    /* Append 'src' to build directory create
     * if it does not exists and then roll-back the string
     */
    count = build_dir.count;
    str_cat(&build_dir, &src);
    dir_mkdir_ifnot_exists(&build_dir);
    slice_set(&build_dir, build_dir.items, count);

    /* Start iterating over the 'src' directory */
    dir_list_dir(&src, callback, &pack);

    /* Wait for all of the compilation units to finish */
    proc_wait(&procs);

    /* Make .so and .a files */
    make_libs(std, &pack);

    /* Wait for .so and .a files to finish */
    proc_wait(&procs);

    /* Free all of the allocated data */
    da_deinit(&procs);
    da_deinit(&objs);
    str_deinit(&src);
    str_deinit(&build_dir);
    str_deinit(&pack.full);
    str_deinit(&pack.ext);

    io_printf(std->io.out, "Done!\n");
    return success;
}

void build_file
(path_t* full_path, path_t* out_path, packed_t *pack, bool is_crt)
{
    /* Init variables */
    cmd_t cmd = {0};
    path_t tmp = {0};
    time_t in_time = {0}, out_time = {0};

    /* Get modification times of the files */
    path_mtime(full_path, &in_time);
    path_mtime(out_path, &out_time);

    /* Push the object file to list to link later */
    if(!is_crt) {
        str_dup(pack->std->alloc, out_path, &tmp);
        da_push(pack->obj_files, &tmp);
    }

    /* Check if it needs to be skipped or processed */
    if(in_time.sec <= out_time.sec && !pack->general->always_make) {
        if(pack->general->verbose)
        { io_printf(pack->std->io.out,"Skipping %v its up to date\n", full_path); }
        return;
    }
    if(pack->general->verbose)
    { io_printf(pack->std->io.out,"Gotta rebuild %v to %v\n", full_path, out_path); }

    /* Allocate cmd and start building it */
    str_init(pack->std->alloc, &cmd, 256);
    str_cat_sl(&cmd, &pack->general->cc);
    cmd_append(&cmd, &pack->general->freestanding_flags);
    cmd_append(&cmd, &pack->general->c_flags);
    /* Its safe to cast path_t* to slice_u8* */
    /* Dynamic arrays can decay to slices */
    cmd_append(&cmd, (sl_u8_t*)out_path);
    cmd_append(&cmd, (sl_u8_t*)full_path);

    /* Spawn new process within the limit which is procs capacity */
    proc_spawn_fixed(cmd, pack->std->env, pack->procs);

    /* Free the memory which is allocated */
    str_deinit(&cmd);
}

void callback
(sl_cstr_t* path, sl_cstr_t* name, bool is_dir, void* arg)
{
    /* Init variables */
    usz count = 0;
    bool eq = false;
    packed_t *pack = arg, new = *pack;
    path_t* tmp = &pack->full;

    /* Create the full path */
    /* strset */
    str_clear(tmp);
    str_cat_sl(tmp, path);
    path_join(tmp, name);

    /* If its a directory iterate it too */
    if(is_dir) {
        if(pack->general->verbose)
        { io_printf(pack->std->io.out, "Building files in'%v'\n", tmp); }

        /* Create a sub-directory in build directory with same name
         * if it does not exists and then roll-back the string
         */
        count = pack->build_dir->count;
        str_cat(pack->build_dir, tmp);
        dir_mkdir_ifnot_exists(pack->build_dir);
        slice_set(pack->build_dir, pack->build_dir->items, count);

        /* Allocate new full path (which is a buffer) to use */
        str_init(pack->std->alloc, &new.full, 128);
        dir_list_dir(tmp, callback, &new);
        str_deinit(&new.full);
        return;
    }

    /* Check if its the crt file or not */
    mem_cmp(name, &pack->general->crt_name, &eq);

    /* Get extension */
    path_ext(tmp, &pack->ext);

    /* If it is a 'c' or 's' file we build it skipping the headers etc. */
    if(str_eq_cstr(&pack->ext, "c") || str_eq_cstr(&pack->ext, "s")) {
        /* Take a snap of the current index */
        count = pack->build_dir->count;

        /* Construct output path */
        str_cat_sl(pack->build_dir, path);
        path_join(pack->build_dir, name);
        path_change_ext(pack->build_dir, &pack->general->obj_ext);

        /* Build the current file */
        build_file(tmp, pack->build_dir, arg, eq);

        /* Roll-back to old index */
        slice_set(pack->build_dir, pack->build_dir->items, count);
    }
}

void make_libs
(std_t* std, packed_t* pack)
{
    /* Init variables */
    cmd_t so_cmd = {0}, arc_cmd = {0};
    u32 i = 0;
    da_path_t* objs = pack->obj_files;

    /* Set .a library command and flags */
    str_init(std->alloc, &arc_cmd, 2048);
    cmd_append(&arc_cmd, &pack->general->ar);
    cmd_append(&arc_cmd, &pack->general->ar_flags);

    /* Set .a library command and flags */
    str_init(std->alloc, &so_cmd, 2048);
    cmd_append(&so_cmd, &pack->general->cc);
    cmd_append(&so_cmd, &pack->general->freestanding_flags);
    cmd_append(&so_cmd, &pack->general->so_flags);

    /* Iterate over the objects list and append to commands and free it */
    io_printf(std->io.out, "Compiling now %d amount of objects to shared object and libray\n", objs->count);
    for(; i < objs->count; ++i) {
        if(pack->general->verbose)
        { io_printf(std->io.out, "Adding %v to list\n", (objs->items + i)); }
        cmd_append(&so_cmd, (sl_u8_t*)(objs->items + i));
        cmd_append(&arc_cmd, (sl_u8_t*)(objs->items + i));
        str_deinit(objs->items + i);
    }

    /* Spawn both of the commands */
    proc_spawn(so_cmd, std->env, pack->procs);
    proc_spawn(arc_cmd, std->env, pack->procs);

    /* Free commands */
    str_deinit(&so_cmd);
    str_deinit(&arc_cmd);
}

bool build_yourself
(std_t* std, packed_t* pack)
{
    /* Init variables */
    path_t c_file = {0}, exe_file = {0}, old_exe = {0};
    time_t exe_time = {0}, c_time = {0};
    cmd_t cmd = {0};
    u32 i = 0;
    error_t ret = 0;

    /* Allocate memory for file paths +2 is for '.o' extension
     * not mandatory but saves as a little bit of time
     */
    str_init(std->alloc, &c_file, std->exe.count + 2);
    str_init(std->alloc, &exe_file, std->exe.count);

    /* Construct the paths */
    str_cat_sl(&c_file, &std->exe);
    str_cat_sl(&exe_file, &std->exe);
    path_change_ext(&c_file, &pack->general->c_ext);

    /* Get last modification times */
    path_mtime(&c_file, &c_time);
    path_mtime(&exe_file, &exe_time);

    /* Check if its up to date and free the paths */
    if(c_time.sec <= exe_time.sec) {
        io_printf(std->io.out, "Up to date script...\n");
        str_deinit(&c_file);
        str_deinit(&exe_file);
        return true;
    }

    io_printf(std->io.out, "Building script...\n");
    io_printf(std->io.out, "This will rebuild all of the files...\n");
    io_flush(std->io.out);

    /* Construct old path which 'build.old' and rename the 'build' file */
    str_dup(std->alloc, &exe_file, &old_exe);
    path_change_ext(&old_exe, &pack->general->old_ext);
    path_rename(&exe_file, &old_exe);

    /* Construct the command */
    str_init(std->alloc, &cmd, 128);
    cmd_append(&cmd, &pack->general->cc);
    cmd_append(&cmd, &pack->general->freestanding_flags);
    /* Its safe to cast path_t* to slice_u8* */
    /* Dynamic arrays can decay to slices */
    cmd_append(&cmd, (sl_u8_t*)&c_file);
    cmd_append(&cmd, &pack->general->build_yourself_flags);
    cmd_append(&cmd, (sl_u8_t*)&exe_file);

    /* Print the command if program is started with verbose */
    if(pack->general->verbose) {
        io_printf(std->io.out, "Command which will be executed is: %v\n", &cmd);
        io_flush(std->io.out);
    }

    /* Run and wait the command */
    proc_run(cmd, std->env);

    /* Clear and start construct the new command and append the args */
    str_clear(&cmd);
    cmd_append(&cmd, (sl_u8_t*)&exe_file);
    str_cat_cstr(&cmd, " -b");
    for(i = 0; i < std->args.count; ++i) {
        cmd_append(&cmd, std->args.items + i);
    }

    /* Overwrite the current program and start the new build script  */
    ret = system_run_env(cmd, std->env);
    if(ret) {
        io_printf(std->io.out, "Could not execute the new build script...\n");
        path_rename(&old_exe, &exe_file);
    }

    /* Free in case it fails otherwise program wont reach here */
    str_deinit(&cmd);
    str_deinit(&c_file);
    str_deinit(&exe_file);
    str_deinit(&old_exe);

    return false;
}

void set_flags
(std_t* std, packed_t* pack)
{
    /* Init variables */
    u32 i = 0;
    char* arg = 0;

    /* Iterate over the args and find given flags - arguments which are not a flag will be ignored */
    for(; i < std->args.count; ++i) {
        arg = (char*)std->args.items[i].items;
        if(cstr_eq("-v", arg)) { pack->general->verbose = true; }
        if(cstr_eq("-b", arg)) { pack->general->always_make = true; }
    }
}

void set_general
(packed_t* pack)
{
    /* Set alias for general */
    general_t* general = pack->general;

    /* Set basic thins */
    slice_set_cstr(&general->ar, "ar");
    slice_set_cstr(&general->cc, "gcc");
    slice_set_cstr(&general->obj_ext, "o");
    slice_set_cstr(&general->crt_name, "fcrt0.s");

    /* c_flags ends with -o because in program we append
     * output name after the c_flags so its convenient
     */
    slice_set_cstr(&general->c_flags,
        "-O2 -g3 -fPIC "
        "-Wall -Wextra -Wpedantic "
        "-Wconversion -Wsign-conversion "
        "-Wformat -Wformat-overflow -Wformat-truncation "
        "-Wstrict-prototypes -Wmissing-prototypes "
        "-Wshadow -Wpointer-arith "
        "-Wwrite-strings -Wundef "
        "-Wfloat-equal -Wcast-align -Wno-int-conversion "
        "-Wswitch-default -std=c89 -pedantic -Werror "
        "-Iinclude -c -o ");

    slice_set_cstr(&general->so_flags, "-shared -fPIC -o .build/flibc.so");
    slice_set_cstr(&general->ar_flags, "rcs -o .build/flibc.a");

    slice_set_cstr(&general->freestanding_flags,
        "-ffreestanding -fno-builtin -nostdinc -nostdlib -Iinclude -nostartfiles -nodefaultlibs");

    slice_set_cstr(&general->c_ext, ".c");
    slice_set_cstr(&general->old_ext, ".old");

    /* It ends with -o reason same as c_flags */
    slice_set_cstr(&general->build_yourself_flags,
        "-Wl,-e,_start .build/src/arch/x86_64/fcrt0.o -L. -l:.build/flibc.so -Wl,-rpath=. -o");
}
