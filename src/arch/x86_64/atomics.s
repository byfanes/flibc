.intel_syntax noprefix
.text

.global atomic_cas_u32
.global atomic_cas_u64
.global atomic_cas_usz
.global atomic_cas_i32
.global atomic_cas_i64
.global atomic_cas_ssz
.global atomic_load_u32
.global atomic_load_u64
.global atomic_load_usz
.global atomic_load_i32
.global atomic_load_i64
.global atomic_load_ssz
.global atomic_xchg_u32
.global atomic_xchg_u64
.global atomic_xchg_usz
.global atomic_xchg_i32
.global atomic_xchg_i64
.global atomic_xchg_ssz
.global atomic_fetch_add_u32
.global atomic_fetch_add_u64
.global atomic_fetch_add_usz
.global atomic_fetch_add_i32
.global atomic_fetch_add_i64
.global atomic_fetch_add_ssz
.global atomic_fetch_sub_u32
.global atomic_fetch_sub_u64
.global atomic_fetch_sub_usz
.global atomic_fetch_sub_i32
.global atomic_fetch_sub_i64
.global atomic_fetch_sub_ssz
.global atomic_memory_barrier

atomic_memory_barrier:
        mfence
        ret

atomic_cas_u32:
atomic_cas_i32:
        mov     eax, esi
        lock cmpxchg dword ptr [rdi], edx
        sete    al
        movzx eax, al
        ret

atomic_cas_usz:
atomic_cas_ssz:
atomic_cas_u64:
atomic_cas_i64:
        mov     rax, rsi
        lock cmpxchg qword ptr [rdi], rdx
        sete    al
        movzx rax, al
        ret

atomic_load_u32:
atomic_load_i32:
        mov     eax, dword ptr [rdi]
        ret

atomic_load_usz:
atomic_load_ssz:
atomic_load_u64:
atomic_load_i64:
        mov     rax, qword ptr [rdi]
        ret

atomic_xchg_u32:
atomic_xchg_i32:
        mov     eax, esi
        xchg    eax, dword ptr [rdi]
        ret

atomic_xchg_usz:
atomic_xchg_ssz:
atomic_xchg_u64:
atomic_xchg_i64:
        mov     rax, rsi
        xchg    rax, qword ptr [rdi]
        ret

atomic_fetch_add_u32:
atomic_fetch_add_i32:
        mov     eax, esi
        lock xadd dword ptr [rdi], eax
        ret

atomic_fetch_add_usz:
atomic_fetch_add_ssz:
atomic_fetch_add_u64:
atomic_fetch_add_i64:
        mov     rax, rsi
        lock xadd qword ptr [rdi], rax
        ret

atomic_fetch_sub_u32:
atomic_fetch_sub_i32:
        mov     eax, esi
        neg     eax
        lock xadd dword ptr [rdi], eax
        ret

atomic_fetch_sub_usz:
atomic_fetch_sub_ssz:
atomic_fetch_sub_u64:
atomic_fetch_sub_i64:
        mov     rax, rsi
        neg     rax
        lock xadd qword ptr [rdi], rax
        ret
