; CalcZ_Aavx.asm
; void CalcZ_Aavx(float* z, const float* x, const float* y, size_t n)
; rdi = z, rsi = x, rdx = y, rcx = n

global CalcZ_Aavx
section .text

NSE equ 8

CalcZ_Aavx:
    xor rax, rax                ; i = 0

.loop1:
    mov r8, rcx                 ; r8 = n
    sub r8, rax                 ; r8 = n - i
    cmp r8, NSE
    jb .loop2                   ; if (n - i) < 8 salta a loop2

    ; Cargar 8 floats de x e y
    vmovups ymm0, [rsi + rax*4] ; ymm0 = x[i..i+7]
    vmovups ymm1, [rdx + rax*4] ; ymm1 = y[i..i+7]
    vaddps  ymm2, ymm0, ymm1    ; suma
    vmovups [rdi + rax*4], ymm2 ; guardar en z

    add rax, NSE
    jmp .loop1

.loop2:
    cmp rax, rcx
    jae .done

    vmovss xmm0, [rsi + rax*4]
    vmovss xmm1, [rdx + rax*4]
    vaddss xmm2, xmm0, xmm1
    vmovss [rdi + rax*4], xmm2

    inc rax
    jmp .loop2

.done:
    vzeroupper
    ret
