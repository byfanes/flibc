.intel_syntax noprefix
.text
.global thread_clone_linux

thread_clone_linux:
        mov rax, rsi
        sub rsi, 32

        mov [rsi +  0], rdx
        mov [rsi +  8], rcx
        mov [rsi + 16], r8
        mov [rsi + 24], rax

        mov rax, 56
        xor rdx, rdx
        xor r10, r10
        xor r8, r8
        syscall

        test rax, rax
        jz .L_child_thread
        ret

.L_child_thread:
        mov rsp, rsi

        and rsp, -16

        mov rax, [rsp + 0]
        mov rdi, [rsp + 8]
        mov rsi, [rsp + 16]
        mov rbx, [rsp + 24]

        cmp rdi, 0
        jne .L_not_null_std
        mov rdi, rsi
        xor rsi, rsi
.L_not_null_std:
        call rax

        mov rdi, rbx
        mov rsi, rax
        call __thread_end

        mov rax, 60
        xor rdi, rdi
        syscall
