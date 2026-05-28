.intel_syntax noprefix
.globl syscall_0_linux
.globl syscall_1_linux
.globl syscall_2_linux
.globl syscall_3_linux
.globl syscall_4_linux
.globl syscall_5_linux
.globl syscall_6_linux
.text

syscall_0_linux:
    mov rax, rdi
    syscall
    ret

syscall_1_linux:
    mov rax, rdi
    mov rdi, rsi
    syscall
    ret

syscall_2_linux:
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    syscall
    ret

syscall_3_linux:
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    syscall
    ret

syscall_4_linux:
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    mov r10, r8
    syscall
    ret

syscall_5_linux:
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    mov r10, r8
    mov r8, r9
    syscall
    ret

syscall_6_linux:
    mov rax, rdi
    mov rdi, rsi
    mov rsi, rdx
    mov rdx, rcx
    mov r10, r8
    mov r8, r9
    mov r9, [rsp + 8]
    syscall
    ret
