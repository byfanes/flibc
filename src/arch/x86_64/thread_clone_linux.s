.intel_syntax noprefix
.text
.global __thread_clone_linux

__thread_clone_linux:
        mov rax, 56
        mov r10, rcx
        xor r8, r8
        syscall
        test rax, rax
        jnz .L_parent_thread
        mov rdi, rsi
        mov rsp, rsi
        and rsp, -16
        call __os_thread_dispatcher
.L_parent_thread:
        ret
