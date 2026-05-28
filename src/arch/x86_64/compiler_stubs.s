.intel_syntax noprefix
.text
.global memset
.global memcpy

memset:
    mov rax, rdi
    mov rcx, rdx
    mov edx, esi
    mov rdi, rax
    mov al, dl
    rep stosb
    ret

memcpy:
    mov rax, rdi
    mov rcx, rdx
    rep movsb
    ret
