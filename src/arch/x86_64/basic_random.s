.intel_syntax noprefix
.text
.global __flibc_hardware_random
.global __flibc_fallback_random_by_time_and_sp

__flibc_hardware_random:
        push rbx
        push rcx
        push rdx

        mov eax, 1
        cpuid

        bt ecx, 30
        jnc .L_unsupported

        mov rcx, 10
.L_retry:
        rdrand rax
        jc .L_success
        dec rcx
        jnz .L_retry

.L_unsupported:
        xor rax, rax

.L_success:
        pop rdx
        pop rcx
        pop rbx
        ret

__flibc_fallback_random_by_time_and_sp:
        rdtsc
        shl rdx, 32
        or rax, rdx
        xor rax, rsp
        ret
