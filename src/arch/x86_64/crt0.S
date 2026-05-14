.intel_syntax noprefix
.global _start
.text

_start:
        xor rbp, rbp
        pop rdi
        mov rsi, rsp
        and rsp, -16
        call runtime_start
        mov rax, 60
        mov rdi, 255
        syscall
        hlt
