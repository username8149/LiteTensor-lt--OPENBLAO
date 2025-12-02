#pragma once

/***********************
OPENBLAO IMPLEMENT
*************************/

/*__INTREGER__*/

#define ADD_I32x16_A512(a, b, c)                \
    asm volatile(                                                    \
        "vmovdqu32 %1, %%zmm0\n"                    \
        "vmovdqu32 %2, %%zmm1\n"                     \
        "vpaddd %%zmm1, %%zmm0, %%zmm2 \n"  \
        "vmovdqu32 %%zmm2, %0\n"                            \
        : "=m"(c)                                                                    \
        : "m"(a), "m"(b)                                                           \
        : "zmm0", "zmm1", "zmm2", "memory" )
        
#define ADD_I32x8_AVX2(a, b, c)                  \
    asm volatile(                                                    \
        "vmovdqu %1, %%ymm0\n"                        \
        "vmovdqu %2, %%ymm1\n"                          \
        "vpaddd %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovdqu %%ymm2, %0\n"                                   \
        "vzeroupper\n"                                                           \
        : "=m"(c)                                                                        \
        : "m"(a), "m"(b)                                                               \
        : "ymm0", "ymm1", "ymm2"                                           \
    )

#define ADD_I32x4_SSE22(a, b, c)                   \
    asm volatile(                                                     \
        "movdqu %1, %%xmm0\n"                           \
        "movdqu %2, %%xmm1\n"                             \
        "paddd  %%xmm1, %%xmm0\n"                     \
        "movdqu %%xmm0, %0\n"                                 \
        : "=m"(c)                                                                  \
        : "m"(a), "m"(b)                                                         \
        : "xmm0", "xmm1")
        
#define ADD_I32x4_ARM(a, b, c)                   \
    asm volatile(                                                    \
        "ld1 {v0.4s}, [%1]        \n"                              \
        "ld1 {v1.4s}, [%2]        \n"                                \
        "add v2.4s, v0.4s, v1.4s  \n"                           \
        "st1 {v2.4s}, [%0]        \n"                                    \
        :                                                                                \
        : "r"(c), "r"(a), "r"(b)                                                 \
        : "v0", "v1", "v2", "memory")
        
#define ADD_I32x4_ARMv7(a, b, c)                          \
    asm volatile(                                                               \
        "vld1.32 {q0}, [%1]     \n"                                          \
        "vld1.32 {q1}, [%2]     \n"                                            \
        "vadd.i32 q2, q0, q1   \n"                                             \
        "vst1.32 {q2}, [%0]     \n"                                                \
        :                                                                                            \
        : "r"(c), "r"(a), "r"(b)                                                             \
        : "q0", "q1", "q2", "memory")        

#define ADD_I32_SVE2(a, b, c, count) \
    asm volatile( \
        "mov     x4, #0\n" \
        "1:\n" \
        "whilelt p0.s, x4, %3\n" \
        "b.none  p0, 2f\n" \
        "ld1w    z0.s, p0/z, [%1, x4, lsl #2]\n" \
        "ld1w    z1.s, p0/z, [%2, x4, lsl #2]\n" \
        "add     z2.s, z0.s, z1.s\n" \
        "st1w    z2.s, p0, [%0, x4, lsl #2]\n" \
        "whilelt p1.s, x4, %3\n" \
        "incw    x4, ALL, MUL #1\n" \
        "b.any   p1, 1b\n" \
        "2:\n" \
        : \
        : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","p1","z0","z1","z2","memory" \
    )
    
#define ADD_I32_SVE(a, b, c, count) \
    asm volatile( \
        "mov     x4, #0\n" \
        "1:\n" \
        "whilelt p0.s, x4, %3\n" \
        "b.none  p0, 2f\n" \
        "ld1w    z0.s, p0/z, [%1, x4, lsl #2]\n" \
        "ld1w    z1.s, p0/z, [%2, x4, lsl #2]\n" \
        "add     z2.s, z0.s, z1.s\n" \
        "st1w    z2.s, p0, [%0, x4, lsl #2]\n" \
        "incw    x4\n" \
        "b       1b\n" \
        "2:\n" \
        : \
        : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )

/*__SUB__*/
    
#define SUB_I32x16_A512(a, b, c) \
    asm volatile( \
        "vmovdqu32 (%1), %%zmm0\n" \
        "vmovdqu32 (%2), %%zmm1\n" \
        "vpsubd %%zmm0, %%zmm1, %%zmm2\n"\
        "vmovdqu32 %%zmm2, (%0)\n" \
        : \
        : "r"(c), "r"(a), "r"(b) \
        : "zmm0","zmm1","zmm2","memory" \
    )
        
#define SUB_I32x8_AVX2(a, b, c) \
    asm volatile( \
        "vmovdqu (%1), %%ymm0\n" \
        "vmovdqu (%2), %%ymm1\n" \
        "vpsubd %%ymm1, %%ymm0, %%ymm2\n" \
        "vmovdqu %%ymm2, (%0)\n" \
        "vzeroupper\n" \
        : \
        : "r"(c), "r"(a), "r"(b) \
        : "ymm0", "ymm1", "ymm2", "memory" \
    )

#define SUB_I32x4_SSE22(a, b, c) \
    asm volatile( \
        "movdqu (%1), %%xmm0\n" \
        "movdqu (%2), %%xmm1\n" \
        "psubd  %%xmm1, %%xmm0\n" \
        "movdqu %%xmm0, (%0)\n" \
        : \
        : "r"(c), "r"(a), "r"(b) \
        : "xmm0","xmm1","memory" \
    )
        
#define SUB_I32x4_ARM(a, b, c)                   \
    asm volatile(                                                    \
        "ld1 {v0.4s}, [%1]        \n"                              \
        "ld1 {v1.4s}, [%2]        \n"                                \
        "sub v2.4s, v0.4s, v1.4s  \n"                           \
        "st1 {v2.4s}, [%0]        \n"                                    \
        :                                                                                \
        : "r"(c), "r"(a), "r"(b)                                                 \
        : "v0", "v1", "v2", "memory")
        
#define SUB_I32x4_ARMv7(a, b, c)                          \
    asm volatile(                                                               \
        "vld1.32 {q0}, [%1]     \n"                                          \
        "vld1.32 {q1}, [%2]     \n"                                            \
        "vsub.i32 q2, q0, q1   \n"                                             \
        "vst1.32 {q2}, [%0]     \n"                                                \
        :                                                                                            \
        : "r"(c), "r"(a), "r"(b)                                                             \
        : "q0", "q1", "q2", "memory")        

#define SUB_I32_SVE2(a, b, c, count) \
    asm volatile( \
        "mov     x4, #0\n" \
        "1:\n" \
        "whilelt p0.s, x4, %3\n" \
        "b.none  p0, 2f\n" \
        "ld1w    z0.s, p0/z, [%1, x4, lsl #2]\n" \
        "ld1w    z1.s, p0/z, [%2, x4, lsl #2]\n" \
        "sub     z2.s, z0.s, z1.s\n" \
        "st1w    z2.s, p0, [%0, x4, lsl #2]\n" \
        "incw    x4\n" \
        "b       1b\n" \
        "2:\n" \
        : \
        : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
#define SUB_I32_SVE(a, b, c, count) \
    asm volatile( \
        "mov     x4, #0\n" \
        "1:\n" \
        "whilelt p0.s, x4, %3\n" \
        "cntp   x5, p0, p0.s\n" \
        "cbz    x5, 2f\n" \
        "ld1w    z0.s, p0/z, [%1, x4, lsl #2]\n" \
        "ld1w    z1.s, p0/z, [%2, x4, lsl #2]\n" \
        "sub     z2.s, z0.s, z1.s\n" \
        "st1w    z2.s, p0, [%0, x4, lsl #2]\n" \
        "incw    x4\n" \
        "b       1b\n" \
        "2:\n" \
        : \
        : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","x5","p0","z0","z1","z2","memory" \
    )
    
#define MUL_I32x16_A512(a, b, c)                \
    asm volatile(                                                    \
        "vmovdqu32 %1, %%zmm0\n"                    \
        "vmovdqu32 %2, %%zmm1\n"                     \
        "vpmulld %%zmm1, %%zmm0, %%zmm2 \n"  \
        "vmovdqu32 %%zmm2, %0\n"                            \
        : "=m"(c)                                                                    \
        : "m"(a), "m"(b)                                                           \
        : "zmm0", "zmm1", "zmm2", "memory" )
        
#define MUL_I32x8_AVX2(a, b, c)                  \
    asm volatile(                                                    \
        "vmovdqu %1, %%ymm0\n"                        \
        "vmovdqu %2, %%ymm1\n"                          \
        "vpmulld %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovdqu %%ymm2, %0\n"                                   \
        "vzeroupper\n"                                                           \
        : "=m"(c)                                                                        \
        : "m"(a), "m"(b)                                                               \
        : "ymm0", "ymm1", "ymm2"                                           \
    )

#define MUL_I32x4_SSE22(a, b, c)                   \
    asm volatile(                                  \
        "movdqu %1, %%xmm0\n\t"                   \
        "movdqu %2, %%xmm1\n\t"                   \
        "pmulld %%xmm1, %%xmm0\n\t"               \
        "movdqu %%xmm0, %0"                       \
        : "=m"(c)                                 \
        : "m"(a), "m"(b)                          \
        : "xmm0", "xmm1")
        
#define MUL_I32x4_ARM(a, b, c)                   \
    asm volatile(                                                    \
        "ld1 {v0.4s}, [%1]        \n"                              \
        "ld1 {v1.4s}, [%2]        \n"                                \
        "mul v2.4s, v0.4s, v1.4s  \n"                           \
        "st1 {v2.4s}, [%0]        \n"                                    \
        :                                                                                \
        : "r"(c), "r"(a), "r"(b)                                                 \
        : "v0", "v1", "v2", "memory")
        
#define MUL_I32x4_ARMv7(a, b, c)                          \
    asm volatile(                                                               \
        "vld1.32 {q0}, [%1]     \n"                                          \
        "vld1.32 {q1}, [%2]     \n"                                            \
        "vmul.i32 q2, q0, q1   \n"                                             \
        "vst1.32 {q2}, [%0]     \n"                                                \
        :                                                                                            \
        : "r"(c), "r"(a), "r"(b)                                                             \
        : "q0", "q1", "q2", "memory")        

#define MUL_I32_SVE2(a, b, c, count) \
    asm volatile( \
        "mov     x4, #0\n" \
        "1:\n" \
        "whilelt p0.s, x4, %3\n" \
        "b.none  p0, 2f\n" \
        "ld1w    z0.s, p0/z, [%1, x4, lsl #2]\n" \
        "ld1w    z1.s, p0/z, [%2, x4, lsl #2]\n" \
        "mul     z2.s, z0.s, z1.s\n" \
        "st1w    z2.s, p0, [%0, x4, lsl #2]\n" \
        "incw    x4\n" \
        "b       1b\n" \
        "2:\n" \
        : \
        : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
#define MUL_I32_SVE(a, b, c, count) \
    asm volatile( \
        "mov     x4, #0\n" \
        "1:\n" \
        "whilelt p0.s, x4, %3\n" \
        "b.none  p0, 2f\n" \
        "ld1w    z0.s, p0/z, [%1, x4, lsl #2]\n" \
        "ld1w    z1.s, p0/z, [%2, x4, lsl #2]\n" \
        "mul     z2.s, z0.s, z1.s\n" \
        "st1w    z2.s, p0, [%0, x4, lsl #2]\n" \
        "incw    x4\n" \
        "b       1b\n" \
        "2:\n" \
        : \
        : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
/*__EXSLUSIVE INTEGER DIVISION__*/

#define DIV_I32x8_x86_64(a, b, c) \
    asm volatile( \
        "xor %%rcx, %%rcx\n" \
        "loop_start_x86:\n" \
        "cmp $8, %%rcx\n" \
        "jge loop_end_x86\n" \
        "mov eax, DWORD PTR [%0 + %%rcx*4]\n" \
        "cdq\n" \
        "idiv DWORD PTR [%1 + %%rcx*4]\n" \
        "mov DWORD PTR [%2 + %%rcx*4], eax\n" \
        "inc %%rcx\n" \
        "jmp loop_start_x86\n" \
        "loop_end_x86:\n" \
        : \
        : "r"(a), "r"(b), "r"(c) \
        : "rax", "rdx", "rcx", "memory" \
    )

#define DIV_I32x8_x86_32(a, b, c) \
    asm volatile( \
        "xor %%ecx, %%ecx\n" \
        "loop_start_x86_32:\n" \
        "cmp $8, %%ecx\n" \
        "jge loop_end_x86_32\n" \
        "mov eax, DWORD PTR [%0 + %%ecx*4]\n" \
        "cdq\n" \
        "idiv DWORD PTR [%1 + %%ecx*4]\n" \
        "mov DWORD PTR [%2 + %%ecx*4], eax\n" \
        "inc %%ecx\n" \
        "jmp loop_start_x86_32\n" \
        "loop_end_x86_32:\n" \
        : \
        : "r"(a), "r"(b), "r"(c) \
        : "eax", "edx", "ecx", "memory" \
    )
    
#define DIV_I32x8_ARM(a, b, c) \
    asm volatile( \
        "mov x0, #0\n" \
        "loop_start:\n" \
        "cmp x0, #8\n" \
        "b.ge loop_end\n" \
        "ldr w1, [%0, x0, LSL #2]\n" \
        "ldr w2, [%1, x0, LSL #2]\n" \
        "sdiv w3, w1, w2\n" \
        "str w3, [%2, x0, LSL #2]\n" \
        "add x0, x0, #1\n" \
        "b loop_start\n" \
        "loop_end:\n" \
        : \
        : "r"(a), "r"(b), "r"(c) \
        : "x0","w1","w2","w3","memory" \
    )

#define DIV_I32x8_ARMv7(a, b, c) \
    asm volatile( \
        "mov r0, #0\n" \
        "loop_start_armv7:\n" \
        "cmp r0, #8\n" \
        "bge loop_end_armv7\n" \
        "ldr r1, [%0, r0, LSL #2]\n" \
        "ldr r2, [%1, r0, LSL #2]\n" \
        "sdiv r3, r1, r2\n" \
        "str r3, [%2, r0, LSL #2]\n" \
        "add r0, r0, #1\n" \
        "b loop_start_armv7\n" \
        "loop_end_armv7:\n" \
        : \
        : "r"(a), "r"(b), "r"(c) \
        : "r0","r1","r2","r3","memory" \
    )
    
/*__INTERGER 16 BIT__*/

#define ADD_I16x32_A512(a, b, c) \
    asm volatile( \
        "vmovdqu16 (%1), %%zmm0\n" \
        "vmovdqu16 (%2), %%zmm1\n" \
        "vpaddw %%zmm1, %%zmm0, %%zmm2\n" \
        "vmovdqu16 %%zmm2, (%0)\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "zmm0","zmm1","zmm2","memory" \
    )
    
#define ADD_I16x16_AVX2(a, b, c) \
    asm volatile( \
        "vmovdqu (%1), %%ymm0\n" \
        "vmovdqu (%2), %%ymm1\n" \
        "vpaddw %%ymm1, %%ymm0, %%ymm2\n" \
        "vmovdqu %%ymm2, (%0)\n" \
        "vzeroupper\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "ymm0","ymm1","ymm2","memory" \
    )

#define ADD_I16x8_ARM(a, b, c) \
    asm volatile( \
        "ld1 {v0.8h}, [%1]\n" \
        "ld1 {v1.8h}, [%2]\n" \
        "add v2.8h, v0.8h, v1.8h\n" \
        "st1 {v2.8h}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "v0","v1","v2","memory" \
    )
    
#define ADD_I16x8_ARMv7(a, b, c) \
    asm volatile( \
        "vld1.16 {q0}, [%1]\n" \
        "vld1.16 {q1}, [%2]\n" \
        "vadd.i16 q2, q0, q1\n" \
        "vst1.16 {q2}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "q0","q1","q2","memory" \
    )
    
#define ADD_I16_SVE(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.h, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1h z0.h, p0/z, [%1, x4, LSL #1]\n" \
        "ld1h z1.h, p0/z, [%2, x4, LSL #1]\n" \
        "add z2.h, z0.h, z1.h\n" \
        "st1h z2.h, p0, [%0, x4, LSL #1]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
#define ADD_I16_SVE2(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.h, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1h z0.h, p0/z, [%1, x4, LSL #1]\n" \
        "ld1h z1.h, p0/z, [%2, x4, LSL #1]\n" \
        "add z2.h, z0.h, z1.h\n" \
        "st1h z2.h, p0, [%0, x4, LSL #1]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
#define SUB_I16x32_A512(a, b, c) \
    asm volatile( \
        "vmovdqu16 (%1), %%zmm0\n" \
        "vmovdqu16 (%2), %%zmm1\n" \
        "vpsubw %%zmm1, %%zmm0, %%zmm2\n" \
        "vmovdqu16 %%zmm2, (%0)\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "zmm0","zmm1","zmm2","memory" \
    )
    
#define SUB_I16x16_AVX2(a, b, c) \
    asm volatile( \
        "vmovdqu (%1), %%ymm0\n" \
        "vmovdqu (%2), %%ymm1\n" \
        "vpsubw %%ymm1, %%ymm0, %%ymm2\n" \
        "vmovdqu %%ymm2, (%0)\n" \
        "vzeroupper\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "ymm0","ymm1","ymm2","memory" \
    )

#define SUB_I16x8_ARM(a, b, c) \
    asm volatile( \
        "ld1 {v0.8h}, [%1]\n" \
        "ld1 {v1.8h}, [%2]\n" \
        "sub v2.8h, v0.8h, v1.8h\n" \
        "st1 {v2.8h}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "v0","v1","v2","memory" \
    )
    
#define SUB_I16x8_ARMv7(a, b, c) \
    asm volatile( \
        "vld1.16 {q0}, [%1]\n" \
        "vld1.16 {q1}, [%2]\n" \
        "vsub.i16 q2, q0, q1\n" \
        "vst1.16 {q2}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "q0","q1","q2","memory" \
    )
    
#define SUB_I16_SVE(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.h, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1h z0.h, p0/z, [%1, x4, LSL #1]\n" \
        "ld1h z1.h, p0/z, [%2, x4, LSL #1]\n" \
        "sub z2.h, z0.h, z1.h\n" \
        "st1h z2.h, p0, [%0, x4, LSL #1]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
#define SUB_I16_SVE2(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.h, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1h z0.h, p0/z, [%1, x4, LSL #1]\n" \
        "ld1h z1.h, p0/z, [%2, x4, LSL #1]\n" \
        "sub z2.h, z0.h, z1.h\n" \
        "st1h z2.h, p0, [%0, x4, LSL #1]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
#define MUL_I16x32_A512(a, b, c) \
    asm volatile( \
        "vmovdqu16 (%1), %%zmm0\n" \
        "vmovdqu16 (%2), %%zmm1\n" \
        "vpmullw %%zmm1, %%zmm0, %%zmm2\n" \
        "vmovdqu16 %%zmm2, (%0)\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "zmm0","zmm1","zmm2","memory" \
    )
    
#define MUL_I16x16_AVX2(a, b, c) \
    asm volatile( \
        "vmovdqu (%1), %%ymm0\n" \
        "vmovdqu (%2), %%ymm1\n" \
        "vpmullw %%ymm1, %%ymm0, %%ymm2\n" \
        "vmovdqu %%ymm2, (%0)\n" \
        "vzeroupper\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "ymm0","ymm1","ymm2","memory" \
    )

#define MUL_I16x8_ARM(a, b, c) \
    asm volatile( \
        "ld1 {v0.8h}, [%1]\n" \
        "ld1 {v1.8h}, [%2]\n" \
        "mul v2.8h, v0.8h, v1.8h\n" \
        "st1 {v2.8h}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "v0","v1","v2","memory" \
    )
    
#define MUL_I16x8_ARMv7(a, b, c) \
    asm volatile( \
        "vld1.16 {q0}, [%1]\n" \
        "vld1.16 {q1}, [%2]\n" \
        "vmul.i16 q2, q0, q1\n" \
        "vst1.16 {q2}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "q0","q1","q2","memory" \
    )
    
#define MUL_I16_SVE(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.h, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1h z0.h, p0/z, [%1, x4, LSL #1]\n" \
        "ld1h z1.h, p0/z, [%2, x4, LSL #1]\n" \
        "mul z2.h, z0.h, z1.h\n" \
        "st1h z2.h, p0, [%0, x4, LSL #1]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
#define MUL_I16_SVE2(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.h, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1h z0.h, p0/z, [%1, x4, LSL #1]\n" \
        "ld1h z1.h, p0/z, [%2, x4, LSL #1]\n" \
        "mul z2.h, z0.h, z1.h\n" \
        "st1h z2.h, p0, [%0, x4, LSL #1]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )

#define DIV_I16x8_X86_64(a, b, c)                \
asm volatile(                                    \
    "xor %%rcx, %%rcx\n"                         \
"1:\n"                                           \
    "cmp $8, %%rcx\n"                            \
    "jge 2f\n"                                   \
    "movsx eax, WORD PTR [%0 + %%rcx*2]\n"       \
    "cdq\n"                                      \
    "idiv WORD PTR [%1 + %%rcx*2]\n"            \
    "mov WORD PTR [%2 + %%rcx*2], ax\n"         \
    "inc %%rcx\n"                                \
    "jmp 1b\n"                                   \
"2:\n"                                           \
    :                                            \
    : "r"(a), "r"(b), "r"(c)                     \
    : "rax","rdx","rcx","memory"                \
)

#define DIV_I16x8_X86_32(a, b, c)                \
asm volatile(                                    \
    "xor %%ecx, %%ecx\n"                         \
"1:\n"                                           \
    "cmp $8, %%ecx\n"                            \
    "jge 2f\n"                                   \
    "movsx eax, WORD PTR [%0 + %%ecx*2]\n"       \
    "cdq\n"                                      \
    "idiv WORD PTR [%1 + %%ecx*2]\n"            \
    "mov WORD PTR [%2 + %%ecx*2], ax\n"         \
    "inc %%ecx\n"                                \
    "jmp 1b\n"                                   \
"2:\n"                                           \
    :                                            \
    : "r"(a), "r"(b), "r"(c)                     \
    : "eax","edx","ecx","memory"                \
)

#define DIV_I16x8_ARM(a, b, c)                 \
asm volatile(                                    \
    "mov x4, #0\n"                               \
"1:\n"                                           \
    "cmp x4, #8\n"                               \
    "b.ge 2f\n"                                  \
    "ldrh w1, [%0, x4, LSL #1]\n"               \
    "ldrh w2, [%1, x4, LSL #1]\n"               \
    "sxth w1, w1\n"                              \
    "sxth w2, w2\n"                              \
    "sdiv w3, w1, w2\n"                          \
    "strh w3, [%2, x4, LSL #1]\n"               \
    "add x4, x4, #1\n"                           \
    "b 1b\n"                                     \
"2:\n"                                           \
    :                                            \
    : "r"(a), "r"(b), "r"(c)                     \
    : "x4","w1","w2","w3","memory"              \
)

#define DIV_I16x8_ARMv7(a, b, c)                 \
asm volatile(                                    \
    "mov r4, #0\n"                               \
"1:\n"                                           \
    "cmp r4, #8\n"                               \
    "bge 2f\n"                                   \
    "ldrh r5, [%0, r4, LSL #1]\n"               \
    "ldrh r6, [%1, r4, LSL #1]\n"               \
    "sxth r5, r5\n"                              \
    "sxth r6, r6\n"                              \
    "sdiv r7, r5, r6\n"                          \
    "strh r7, [%2, r4, LSL #1]\n"               \
    "add r4, r4, #1\n"                           \
    "b 1b\n"                                     \
"2:\n"                                           \
    :                                            \
    : "r"(a), "r"(b), "r"(c)                     \
    : "r4","r5","r6","r7","memory"              \
)

/*__INTERGER 8__*/
#define ADD_I8x64_A512(a, b, c) \
    asm volatile( \
        "vmovdqu8 (%1), %%zmm0\n" \
        "vmovdqu8 (%2), %%zmm1\n" \
        "vpaddb %%zmm1, %%zmm0, %%zmm2\n" \
        "vmovdqu8 %%zmm2, (%0)\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "zmm0","zmm1","zmm2","memory" \
    )

#define ADD_I8x32_AVX2(a, b, c) \
    asm volatile( \
        "vmovdqu (%1), %%ymm0\n" \
        "vmovdqu (%2), %%ymm1\n" \
        "vpaddb %%ymm1, %%ymm0, %%ymm2\n" \
        "vmovdqu %%ymm2, (%0)\n" \
        "vzeroupper\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "ymm0","ymm1","ymm2","memory" \
    )

#define ADD_I8x16_ARM(a, b, c) \
    asm volatile( \
        "ld1 {v0.16b}, [%1]\n" \
        "ld1 {v1.16b}, [%2]\n" \
        "add v2.16b, v0.16b, v1.16b\n" \
        "st1 {v2.16b}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "v0","v1","v2","memory" \
    )

#define ADD_I8x16_ARMv7(a, b, c) \
    asm volatile( \
        "vld1.8 {q0}, [%1]\n" \
        "vld1.8 {q1}, [%2]\n" \
        "vadd.i8 q2, q0, q1\n" \
        "vst1.8 {q2}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "q0","q1","q2","memory" \
    )

#define ADD_I8_SVE(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.b, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1b z0.b, p0/z, [%1, x4]\n" \
        "ld1b z1.b, p0/z, [%2, x4]\n" \
        "add z2.b, z0.b, z1.b\n" \
        "st1b z2.b, p0, [%0, x4]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )

#define ADD_I8_SVE2(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.b, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1b z0.b, p0/z, [%1, x4]\n" \
        "ld1b z1.b, p0/z, [%2, x4]\n" \
        "add z2.b, z0.b, z1.b\n" \
        "st1b z2.b, p0, [%0, x4]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )

#define SUB_I8x64_A512(a, b, c) \
    asm volatile( \
        "vmovdqu8 (%1), %%zmm0\n" \
        "vmovdqu8 (%2), %%zmm1\n" \
        "vpsubb %%zmm1, %%zmm0, %%zmm2\n" \
        "vmovdqu8 %%zmm2, (%0)\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "zmm0","zmm1","zmm2","memory" \
    )

#define SUB_I8x32_AVX2(a, b, c) \
    asm volatile( \
        "vmovdqu (%1), %%ymm0\n" \
        "vmovdqu (%2), %%ymm1\n" \
        "vpsubb %%ymm1, %%ymm0, %%ymm2\n" \
        "vmovdqu %%ymm2, (%0)\n" \
        "vzeroupper\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "ymm0","ymm1","ymm2","memory" \
    )

#define SUB_I8x16_ARM(a, b, c) \
    asm volatile( \
        "ld1 {v0.16b}, [%1]\n" \
        "ld1 {v1.16b}, [%2]\n" \
        "sub v2.16b, v0.16b, v1.16b\n" \
        "st1 {v2.16b}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "v0","v1","v2","memory" \
    )

#define SUB_I8x16_ARMv7(a, b, c) \
    asm volatile( \
        "vld1.8 {q0}, [%1]\n" \
        "vld1.8 {q1}, [%2]\n" \
        "vsub.i8 q2, q0, q1\n" \
        "vst1.8 {q2}, [%0]\n" \
        : : "r"(c), "r"(a), "r"(b) \
        : "q0","q1","q2","memory" \
    )

#define SUB_I8_SVE(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.b, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1b z0.b, p0/z, [%1, x4]\n" \
        "ld1b z1.b, p0/z, [%2, x4]\n" \
        "sub z2.b, z0.b, z1.b\n" \
        "st1b z2.b, p0, [%0, x4]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )

#define SUB_I8_SVE2(a, b, c, count) \
    asm volatile( \
        "mov x4, #0\n" \
        "1:\n" \
        "whilelt p0.b, x4, %3\n" \
        "b.none p0, 2f\n" \
        "ld1b z0.b, p0/z, [%1, x4]\n" \
        "ld1b z1.b, p0/z, [%2, x4]\n" \
        "sub z2.b, z0.b, z1.b\n" \
        "st1b z2.b, p0, [%0, x4]\n" \
        "inch x4\n" \
        "b 1b\n" \
        "2:\n" \
        : : "r"(c), "r"(a), "r"(b), "r"(count) \
        : "x4","p0","z0","z1","z2","memory" \
    )
    
#define MUL_I8x64_A512(a, b, c) \
asm volatile( \
"vmovdqu8 (%1), %%zmm0\n" \
"vmovdqu8 (%2), %%zmm1\n" \
"vpmulb %%zmm1, %%zmm0, %%zmm2\n" \
"vmovdqu8 %%zmm2, (%0)\n" \
: : "r"(c), "r"(a), "r"(b) \
: "zmm0","zmm1","zmm2","memory" \
)

#define MUL_I8x32_AVX2(a, b, c) \
asm volatile( \
"vmovdqu (%1), %%ymm0\n" \
"vmovdqu (%2), %%ymm1\n" \
"vpmulb %%ymm1, %%ymm0, %%ymm2\n" \
"vmovdqu %%ymm2, (%0)\n" \
"vzeroupper\n" \
: : "r"(c), "r"(a), "r"(b) \
: "ymm0","ymm1","ymm2","memory" \
)

#define MUL_I8x16_ARM(a, b, c) \
asm volatile( \
"ld1 {v0.16b}, [%1]\n" \
"ld1 {v1.16b}, [%2]\n" \
"mul v2.16b, v0.16b, v1.16b\n" \
"st1 {v2.16b}, [%0]\n" \
: : "r"(c), "r"(a), "r"(b) \
: "v0","v1","v2","memory" \
)

#define MUL_I8x16_ARMv7(a, b, c) \
asm volatile( \
"vld1.8 {q0}, [%1]\n" \
"vld1.8 {q1}, [%2]\n" \
"vmul.i8 q2, q0, q1\n" \
"vst1.8 {q2}, [%0]\n" \
: : "r"(c), "r"(a), "r"(b) \
: "q0","q1","q2","memory" \
)

#define MUL_I8_SVE(a, b, c, count) \
asm volatile( \
"mov x4, #0\n" \
"1:\n" \
"whilelt p0.b, x4, %3\n" \
"b.none p0, 2f\n" \
"ld1b z0.b, p0/z, [%1, x4]\n" \
"ld1b z1.b, p0/z, [%2, x4]\n" \
"mul z2.b, z0.b, z1.b\n" \
"st1b z2.b, p0, [%0, x4]\n" \
"inch x4\n" \
"b 1b\n" \
"2:\n" \
: : "r"(c), "r"(a), "r"(b), "r"(count) \
: "x4","p0","z0","z1","z2","memory" \
)

#define MUL_I8_SVE2(a, b, c, count) \
asm volatile( \
"mov x4, #0\n" \
"1:\n" \
"whilelt p0.b, x4, %3\n" \
"b.none p0, 2f\n" \
"ld1b z0.b, p0/z, [%1, x4]\n" \
"ld1b z1.b, p0/z, [%2, x4]\n" \
"mul z2.b, z0.b, z1.b\n" \
"st1b z2.b, p0, [%0, x4]\n" \
"inch x4\n" \
"b 1b\n" \
"2:\n" \
: : "r"(c), "r"(a), "r"(b), "r"(count) \
: "x4","p0","z0","z1","z2","memory" \
)

#define DIV_I8x16_X86_64(a, b, c)                 \
asm volatile(                                     \
    "xor %%rcx, %%rcx\n"                          \
"1:\n"                                            \
    "cmp $16, %%rcx\n"                            \
    "jge 2f\n"                                    \
    "movsx eax, BYTE PTR [%0 + %%rcx]\n"          \
    "cdq\n"                                       \
    "idiv BYTE PTR [%1 + %%rcx]\n"                \
    "mov BYTE PTR [%2 + %%rcx], al\n"             \
    "inc %%rcx\n"                                 \
    "jmp 1b\n"                                    \
"2:\n"                                            \
    :                                             \
    : "r"(a), "r"(b), "r"(c)                      \
    : "rax","rdx","rcx","memory"                  \
)

#define DIV_I8x16_X86_32(a, b, c)                 \
asm volatile(                                     \
    "xor %%ecx, %%ecx\n"                          \
"1:\n"                                            \
    "cmp $16, %%ecx\n"                            \
    "jge 2f\n"                                    \
    "movsx eax, BYTE PTR [%0 + %%ecx]\n"          \
    "cdq\n"                                       \
    "idiv BYTE PTR [%1 + %%ecx]\n"                \
    "mov BYTE PTR [%2 + %%ecx], al\n"             \
    "inc %%ecx\n"                                 \
    "jmp 1b\n"                                    \
"2:\n"                                            \
    :                                             \
    : "r"(a), "r"(b), "r"(c)                      \
    : "eax","edx","ecx","memory"                  \
)

#define DIV_I8x16_ARM(a, b, c)                     \
asm volatile(                                      \
    "mov x4, #0\n"                                 \
"1:\n"                                             \
    "cmp x4, #16\n"                                \
    "b.ge 2f\n"                                    \
    "ldrb w1, [%0, x4]\n"                          \
    "ldrb w2, [%1, x4]\n"                          \
    "sxtb w1, w1\n"                                \
    "sxtb w2, w2\n"                                \
    "sdiv w3, w1, w2\n"                            \
    "strb w3, [%2, x4]\n"                          \
    "add x4, x4, #1\n"                             \
    "b 1b\n"                                       \
"2:\n"                                             \
    :                                              \
    : "r"(a), "r"(b), "r"(c)                       \
    : "x4","w1","w2","w3","memory"                 \
)

#define DIV_I8x16_ARMv7(a, b, c)                   \
asm volatile(                                      \
    "mov r4, #0\n"                                 \
"1:\n"                                             \
    "cmp r4, #16\n"                                \
    "bge 2f\n"                                     \
    "ldrb r5, [%0, r4]\n"                          \
    "ldrb r6, [%1, r4]\n"                          \
    "sxtb r5, r5\n"                                \
    "sxtb r6, r6\n"                                \
    "sdiv r7, r5, r6\n"                            \
    "strb r7, [%2, r4]\n"                          \
    "add r4, r4, #1\n"                             \
    "b 1b\n"                                       \
"2:\n"                                             \
    :                                              \
    : "r"(a), "r"(b), "r"(c)                       \
    : "r4","r5","r6","r7","memory"                 \
)

/*__FLOATING POINT__*/

#define ADD_F32x16_A512(a, b, c)                \
    asm volatile(                               \
        "vmovups %1, %%zmm0\n"                  \
        "vmovups %2, %%zmm1\n"                  \
        "vaddps  %%zmm1, %%zmm0, %%zmm2\n"     \
        "vmovups %%zmm2, %0\n"                  \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "zmm0", "zmm1", "zmm2", "memory")

#define ADD_F32x8_AVX2(a, b, c)                 \
    asm volatile(                               \
        "vmovups %1, %%ymm0\n"                  \
        "vmovups %2, %%ymm1\n"                  \
        "vaddps  %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovups %%ymm2, %0\n"                  \
        "vzeroupper\n"                          \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "ymm0", "ymm1", "ymm2")

#define ADD_F32x4_SSE22(a, b, c)                 \
    asm volatile(                               \
        "movups %1, %%xmm0\n"                   \
        "movups %2, %%xmm1\n"                   \
        "addps  %%xmm1, %%xmm0\n"               \
        "movups %%xmm0, %0\n"                   \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "xmm0", "xmm1")

#define ADD_F32x4_ARM(a, b, c)                  \
    asm volatile(                               \
        "ld1 {v0.4s}, [%1]\n"                   \
        "ld1 {v1.4s}, [%2]\n"                   \
        "fadd v2.4s, v0.4s, v1.4s\n"           \
        "st1 {v2.4s}, [%0]\n"                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "v0", "v1", "v2", "memory")

#define ADD_F32x4_ARMv7(a, b, c)                \
    asm volatile(                               \
        "vld1.32 {q0}, [%1]\n"                  \
        "vld1.32 {q1}, [%2]\n"                  \
        "vadd.f32 q2, q0, q1\n"                 \
        "vst1.32 {q2}, [%0]\n"                  \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "q0", "q1", "q2", "memory")

#define ADD_F32_SVE(a, b, c, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.s, x4, %3\n"                \
        "b.none  p0, 2f\n"                       \
        "ld1w z0.s, p0/z, [%1, x4, lsl #2]\n"   \
        "ld1w z1.s, p0/z, [%2, x4, lsl #2]\n"   \
        "fadd z2.s, z0.s, z1.s\n"               \
        "st1w z2.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b), "r"(count)   \
        : "x4","p0","z0","z1","z2","memory")

#define ADD_F32_SVE2(a, b, c, count)           \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.s, x4, %3\n"                \
        "b.none p0, 2f\n"                        \
        "ld1w z0.s, p0/z, [%1, x4, lsl #2]\n"   \
        "ld1w z1.s, p0/z, [%2, x4, lsl #2]\n"   \
        "fadd z2.s, z0.s, z1.s\n"               \
        "st1w z2.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b), "r"(count)   \
        : "x4","p0","z0","z1","z2","memory")

#define SUB_F32x16_A512(a, b, c)                \
    asm volatile(                               \
        "vmovups %1, %%zmm0\n"                  \
        "vmovups %2, %%zmm1\n"                  \
        "vsubps  %%zmm1, %%zmm0, %%zmm2\n"     \
        "vmovups %%zmm2, %0\n"                  \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "zmm0", "zmm1", "zmm2", "memory")

#define SUB_F32x8_AVX2(a, b, c)                 \
    asm volatile(                               \
        "vmovups %1, %%ymm0\n"                  \
        "vmovups %2, %%ymm1\n"                  \
        "vsubps  %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovups %%ymm2, %0\n"                  \
        "vzeroupper\n"                          \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "ymm0", "ymm1", "ymm2")

#define SUB_F32x4_SSE22(a, b, c)                 \
    asm volatile(                               \
        "movups %1, %%xmm0\n"                   \
        "movups %2, %%xmm1\n"                   \
        "subps  %%xmm1, %%xmm0\n"               \
        "movups %%xmm0, %0\n"                   \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "xmm0", "xmm1")

#define SUB_F32x4_ARM(a, b, c)                  \
    asm volatile(                               \
        "ld1 {v0.4s}, [%1]\n"                   \
        "ld1 {v1.4s}, [%2]\n"                   \
        "fsub v2.4s, v0.4s, v1.4s\n"           \
        "st1 {v2.4s}, [%0]\n"                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "v0", "v1", "v2", "memory")

#define SUB_F32x4_ARMv7(a, b, c)                \
    asm volatile(                               \
        "vld1.32 {q0}, [%1]\n"                  \
        "vld1.32 {q1}, [%2]\n"                  \
        "vsub.f32 q2, q0, q1\n"                 \
        "vst1.32 {q2}, [%0]\n"                  \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "q0", "q1", "q2", "memory")

#define SUB_F32_SVE(a, b, c, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.s, x4, %3\n"                \
        "b.none  p0, 2f\n"                       \
        "ld1w z0.s, p0/z, [%1, x4, lsl #2]\n"   \
        "ld1w z1.s, p0/z, [%2, x4, lsl #2]\n"   \
        "fsub z2.s, z0.s, z1.s\n"               \
        "st1w z2.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b), "r"(count)   \
        : "x4","p0","z0","z1","z2","memory")

#define SUB_F32_SVE2(a, b, c, count)           \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.s, x4, %3\n"                \
        "b.none p0, 2f\n"                        \
        "ld1w z0.s, p0/z, [%1, x4, lsl #2]\n"   \
        "ld1w z1.s, p0/z, [%2, x4, lsl #2]\n"   \
        "fsub z2.s, z0.s, z1.s\n"               \
        "st1w z2.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b), "r"(count)   \
        : "x4","p0","z0","z1","z2","memory")
        
#define MUL_F32x16_A512(a, b, c)                \
    asm volatile(                               \
        "vmovups %1, %%zmm0\n"                  \
        "vmovups %2, %%zmm1\n"                  \
        "vmulps  %%zmm1, %%zmm0, %%zmm2\n"     \
        "vmovups %%zmm2, %0\n"                  \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "zmm0", "zmm1", "zmm2", "memory")

#define MUL_F32x8_AVX2(a, b, c)                 \
    asm volatile(                               \
        "vmovups %1, %%ymm0\n"                  \
        "vmovups %2, %%ymm1\n"                  \
        "vmulps  %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovups %%ymm2, %0\n"                  \
        "vzeroupper\n"                          \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "ymm0", "ymm1", "ymm2")

#define MUL_F32x4_SSE22(a, b, c)                 \
    asm volatile(                               \
        "movups %1, %%xmm0\n"                   \
        "movups %2, %%xmm1\n"                   \
        "mulps  %%xmm1, %%xmm0\n"               \
        "movups %%xmm0, %0\n"                   \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "xmm0", "xmm1")

#define MUL_F32x4_ARM(a, b, c)                  \
    asm volatile(                               \
        "ld1 {v0.4s}, [%1]\n"                   \
        "ld1 {v1.4s}, [%2]\n"                   \
        "fmul v2.4s, v0.4s, v1.4s\n"           \
        "st1 {v2.4s}, [%0]\n"                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "v0", "v1", "v2", "memory")

#define MUL_F32x4_ARMv7(a, b, c)                \
    asm volatile(                               \
        "vld1.32 {q0}, [%1]\n"                  \
        "vld1.32 {q1}, [%2]\n"                  \
        "vmul.f32 q2, q0, q1\n"                 \
        "vst1.32 {q2}, [%0]\n"                  \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "q0", "q1", "q2", "memory")

#define MUL_F32_SVE(a, b, c, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.s, x4, %3\n"                \
        "b.none  p0, 2f\n"                       \
        "ld1w z0.s, p0/z, [%1, x4, lsl #2]\n"   \
        "ld1w z1.s, p0/z, [%2, x4, lsl #2]\n"   \
        "fmul z2.s, z0.s, z1.s\n"               \
        "st1w z2.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b), "r"(count)   \
        : "x4","p0","z0","z1","z2","memory")

#define MUL_F32_SVE2(a, b, c, count)           \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.s, x4, %3\n"                \
        "b.none p0, 2f\n"                        \
        "ld1w z0.s, p0/z, [%1, x4, lsl #2]\n"   \
        "ld1w z1.s, p0/z, [%2, x4, lsl #2]\n"   \
        "fmul z2.s, z0.s, z1.s\n"               \
        "st1w z2.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b), "r"(count)   \
        : "x4","p0","z0","z1","z2","memory")

#define DIV_F32x16_A512(a, b, c)                \
    asm volatile(                               \
        "vmovups %1, %%zmm0\n"                  \
        "vmovups %2, %%zmm1\n"                  \
        "vdivps  %%zmm1, %%zmm0, %%zmm2\n"     \
        "vmovups %%zmm2, %0\n"                  \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "zmm0", "zmm1", "zmm2", "memory")

#define DIV_F32x8_AVX2(a, b, c)                 \
    asm volatile(                               \
        "vmovups %1, %%ymm0\n"                  \
        "vmovups %2, %%ymm1\n"                  \
        "vdivps  %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovups %%ymm2, %0\n"                  \
        "vzeroupper\n"                          \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "ymm0", "ymm1", "ymm2")

#define DIV_F32x4_SSE22(a, b, c)            \
    asm volatile(                           \
        "movups %1, %%xmm0\n"              \
        "movups %2, %%xmm1\n"              \
        "divps %%xmm1, %%xmm0\n"           \
        "movups %%xmm0, %0\n"              \
        : "=m"(c)                           \
        : "m"(a), "m"(b)                    \
        : "xmm0", "xmm1")

#define DIV_F32x4_ARM(a, b, c)                  \
    asm volatile(                               \
        "ld1 {v0.4s}, [%1]\n"                   \
        "ld1 {v1.4s}, [%2]\n"                   \
        "fdiv v2.4s, v0.4s, v1.4s\n"           \
        "st1 {v2.4s}, [%0]\n"                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "v0", "v1", "v2", "memory")

#define DIV_F32x4_ARMv7(a, b, c)                \
    asm volatile(                               \
        "vld1.32 {q0}, [%1]\n"                  \
        "vld1.32 {q1}, [%2]\n"                  \
        "vdiv.f32 q2, q0, q1\n"                 \
        "vst1.32 {q2}, [%0]\n"                  \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "q0", "q1", "q2", "memory")

#define DIV_F32_SVE(a, b, c, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.s, x4, %3\n"                \
        "b.none  p0, 2f\n"                       \
        "ld1w z0.s, p0/z, [%1, x4, lsl #2]\n"   \
        "ld1w z1.s, p0/z, [%2, x4, lsl #2]\n"   \
        "fdiv z2.s, z0.s, z1.s\n"               \
        "st1w z2.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b), "r"(count)   \
        : "x4","p0","z0","z1","z2","memory")

#define DIV_F32_SVE2(a, b, c, count)           \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.s, x4, %3\n"                \
        "b.none p0, 2f\n"                        \
        "ld1w z0.s, p0/z, [%1, x4, lsl #2]\n"   \
        "ld1w z1.s, p0/z, [%2, x4, lsl #2]\n"   \
        "fdiv z2.s, z0.s, z1.s\n"               \
        "st1w z2.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b), "r"(count)   \
        : "x4","p0","z0","z1","z2","memory")

/*__FLOATING POINT 64 | DOUBLE__*/

#define ADD_F64x8_A512(a, b, c)                \
    asm volatile(                               \
        "vmovupd %1, %%zmm0\n"                  \
        "vmovupd %2, %%zmm1\n"                  \
        "vaddpd  %%zmm1, %%zmm0, %%zmm2\n"     \
        "vmovupd %%zmm2, %0\n"                  \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "zmm0","zmm1","zmm2","memory")

#define ADD_F64x4_AVX2(a, b, c)                \
    asm volatile(                               \
        "vmovupd %1, %%ymm0\n"                  \
        "vmovupd %2, %%ymm1\n"                  \
        "vaddpd  %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovupd %%ymm2, %0\n"                  \
        "vzeroupper\n"                          \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "ymm0","ymm1","ymm2")

#define ADD_F64x2_SSE22(a, b, c)                \
    asm volatile(                               \
        "movupd %1, %%xmm0\n"                   \
        "movupd %2, %%xmm1\n"                   \
        "addpd  %%xmm1, %%xmm0\n"               \
        "movupd %%xmm0, %0\n"                   \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "xmm0","xmm1")

#define ADD_F64x2_ARM(a, b, c)                  \
    asm volatile(                               \
        "ld1 {v0.2d}, [%1]\n"                   \
        "ld1 {v1.2d}, [%2]\n"                   \
        "fadd v2.2d, v0.2d, v1.2d\n"           \
        "st1 {v2.2d}, [%0]\n"                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "v0","v1","v2","memory")

#define ADD_F64_SVE(a, b, c, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.d, x4, %3\n"                \
        "b.none  p0, 2f\n"                       \
        "ld1d z0.d, p0/z, [%1, x4, lsl #3]\n"   \
        "ld1d z1.d, p0/z, [%2, x4, lsl #3]\n"   \
        "fadd z2.d, z0.d, z1.d\n"               \
        "st1d z2.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                   \
        :                                        \
        : "r"(c),"r"(a),"r"(b),"r"(count)      \
        : "x4","p0","z0","z1","z2","memory")

#define ADD_F64_SVE2(a, b, c, count)           \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.d, x4, %3\n"                \
        "b.none p0, 2f\n"                        \
        "ld1d z0.d, p0/z, [%1, x4, lsl #3]\n"   \
        "ld1d z1.d, p0/z, [%2, x4, lsl #3]\n"   \
        "fadd z2.d, z0.d, z1.d\n"               \
        "st1d z2.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                   \
        :                                        \
        : "r"(c),"r"(a),"r"(b),"r"(count)      \
        : "x4","p0","z0","z1","z2","memory")      
        
#define SUB_F64x8_A512(a, b, c)                \
    asm volatile(                               \
        "vmovupd %1, %%zmm0\n"                  \
        "vmovupd %2, %%zmm1\n"                  \
        "vsubpd  %%zmm1, %%zmm0, %%zmm2\n"     \
        "vmovupd %%zmm2, %0\n"                  \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "zmm0","zmm1","zmm2","memory")

#define SUB_F64x4_AVX2(a, b, c)                \
    asm volatile(                               \
        "vmovupd %1, %%ymm0\n"                  \
        "vmovupd %2, %%ymm1\n"                  \
        "vsubpd  %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovupd %%ymm2, %0\n"                  \
        "vzeroupper\n"                          \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "ymm0","ymm1","ymm2")

#define SUB_F64x2_SSE22(a, b, c)                \
    asm volatile(                               \
        "movupd %1, %%xmm0\n"                   \
        "movupd %2, %%xmm1\n"                   \
        "subpd  %%xmm1, %%xmm0\n"               \
        "movupd %%xmm0, %0\n"                   \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "xmm0","xmm1")

#define SUB_F64x2_ARM(a, b, c)                  \
    asm volatile(                               \
        "ld1 {v0.2d}, [%1]\n"                   \
        "ld1 {v1.2d}, [%2]\n"                   \
        "fsub v2.2d, v0.2d, v1.2d\n"           \
        "st1 {v2.2d}, [%0]\n"                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "v0","v1","v2","memory")

#define SUB_F64_SVE(a, b, c, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.d, x4, %3\n"                \
        "b.none  p0, 2f\n"                       \
        "ld1d z0.d, p0/z, [%1, x4, lsl #3]\n"   \
        "ld1d z1.d, p0/z, [%2, x4, lsl #3]\n"   \
        "fsub z2.d, z0.d, z1.d\n"               \
        "st1d z2.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                   \
        :                                        \
        : "r"(c),"r"(a),"r"(b),"r"(count)      \
        : "x4","p0","z0","z1","z2","memory")

#define SUB_F64_SVE2(a, b, c, count)           \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.d, x4, %3\n"                \
        "b.none p0, 2f\n"                        \
        "ld1d z0.d, p0/z, [%1, x4, lsl #3]\n"   \
        "ld1d z1.d, p0/z, [%2, x4, lsl #3]\n"   \
        "fsub z2.d, z0.d, z1.d\n"               \
        "st1d z2.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                   \
        :                                        \
        : "r"(c),"r"(a),"r"(b),"r"(count)      \
        : "x4","p0","z0","z1","z2","memory")      
        
#define MUL_F64x8_A512(a, b, c)                \
    asm volatile(                               \
        "vmovupd %1, %%zmm0\n"                  \
        "vmovupd %2, %%zmm1\n"                  \
        "vmulpd  %%zmm1, %%zmm0, %%zmm2\n"     \
        "vmovupd %%zmm2, %0\n"                  \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "zmm0","zmm1","zmm2","memory")

#define MUL_F64x4_AVX2(a, b, c)                \
    asm volatile(                               \
        "vmovupd %1, %%ymm0\n"                  \
        "vmovupd %2, %%ymm1\n"                  \
        "vmulpd  %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovupd %%ymm2, %0\n"                  \
        "vzeroupper\n"                          \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "ymm0","ymm1","ymm2")

#define MUL_F64x2_SSE22(a, b, c)                \
    asm volatile(                               \
        "movupd %1, %%xmm0\n"                   \
        "movupd %2, %%xmm1\n"                   \
        "mulpd  %%xmm1, %%xmm0\n"               \
        "movupd %%xmm0, %0\n"                   \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "xmm0","xmm1")

#define MUL_F64x2_ARM(a, b, c)                  \
    asm volatile(                               \
        "ld1 {v0.2d}, [%1]\n"                   \
        "ld1 {v1.2d}, [%2]\n"                   \
        "fmul v2.2d, v0.2d, v1.2d\n"           \
        "st1 {v2.2d}, [%0]\n"                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "v0","v1","v2","memory")

#define MUL_F64_SVE(a, b, c, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.d, x4, %3\n"                \
        "b.none  p0, 2f\n"                       \
        "ld1d z0.d, p0/z, [%1, x4, lsl #3]\n"   \
        "ld1d z1.d, p0/z, [%2, x4, lsl #3]\n"   \
        "fmul z2.d, z0.d, z1.d\n"               \
        "st1d z2.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                   \
        :                                        \
        : "r"(c),"r"(a),"r"(b),"r"(count)      \
        : "x4","p0","z0","z1","z2","memory")

#define MUL_F64_SVE2(a, b, c, count)           \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.d, x4, %3\n"                \
        "b.none p0, 2f\n"                        \
        "ld1d z0.d, p0/z, [%1, x4, lsl #3]\n"   \
        "ld1d z1.d, p0/z, [%2, x4, lsl #3]\n"   \
        "fmul z2.d, z0.d, z1.d\n"               \
        "st1d z2.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                   \
        :                                        \
        : "r"(c),"r"(a),"r"(b),"r"(count)      \
        : "x4","p0","z0","z1","z2","memory")      
        
#define DIV_F64x8_A512(a, b, c)                \
    asm volatile(                               \
        "vmovupd %1, %%zmm0\n"                  \
        "vmovupd %2, %%zmm1\n"                  \
        "vdivpd  %%zmm1, %%zmm0, %%zmm2\n"     \
        "vmovupd %%zmm2, %0\n"                  \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "zmm0","zmm1","zmm2","memory")

#define DIV_F64x4_AVX2(a, b, c)                \
    asm volatile(                               \
        "vmovupd %1, %%ymm0\n"                  \
        "vmovupd %2, %%ymm1\n"                  \
        "vdivpd  %%ymm1, %%ymm0, %%ymm2\n"     \
        "vmovupd %%ymm2, %0\n"                  \
        "vzeroupper\n"                          \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "ymm0","ymm1","ymm2")

#define DIV_F64x2_SSE22(a, b, c)                \
    asm volatile(                               \
        "movupd %1, %%xmm0\n"                   \
        "movupd %2, %%xmm1\n"                   \
        "divpd  %%xmm1, %%xmm0\n"               \
        "movupd %%xmm0, %0\n"                   \
        : "=m"(c)                               \
        : "m"(a), "m"(b)                        \
        : "xmm0","xmm1")

#define DIV_F64x2_ARM(a, b, c)                  \
    asm volatile(                               \
        "ld1 {v0.2d}, [%1]\n"                   \
        "ld1 {v1.2d}, [%2]\n"                   \
        "fdiv v2.2d, v0.2d, v1.2d\n"           \
        "st1 {v2.2d}, [%0]\n"                   \
        :                                        \
        : "r"(c), "r"(a), "r"(b)               \
        : "v0","v1","v2","memory")

#define DIV_F64_SVE(a, b, c, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.d, x4, %3\n"                \
        "b.none  p0, 2f\n"                       \
        "ld1d z0.d, p0/z, [%1, x4, lsl #3]\n"   \
        "ld1d z1.d, p0/z, [%2, x4, lsl #3]\n"   \
        "fdiv z2.d, z0.d, z1.d\n"               \
        "st1d z2.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                   \
        :                                        \
        : "r"(c),"r"(a),"r"(b),"r"(count)      \
        : "x4","p0","z0","z1","z2","memory")

#define DIV_F64_SVE2(a, b, c, count)           \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                   \
        "whilelt p0.d, x4, %3\n"                \
        "b.none p0, 2f\n"                        \
        "ld1d z0.d, p0/z, [%1, x4, lsl #3]\n"   \
        "ld1d z1.d, p0/z, [%2, x4, lsl #3]\n"   \
        "fdiv z2.d, z0.d, z1.d\n"               \
        "st1d z2.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                   \
        :                                        \
        : "r"(c),"r"(a),"r"(b),"r"(count)      \
        : "x4","p0","z0","z1","z2","memory")

/*__FIILS__*/

/*__FLOATING POINT 64 | DOUBLE__*/

#define FILL_F64x8_A512(a, val)           \
    asm volatile(                                    \
        "vbroadcastsd %%zmm0, %1\n"                 \
        "vmovupd %%zmm0, %0\n"                       \
        : "=m"(a)                               \
        : "m"(val)                                \
        : "zmm0","memory")
        
#define FILL_F64x4_AVX2(a, val)          \
    asm volatile(                                    \
        "vbroadcastsd %%ymm0, %1\n"                 \
        "vmovupd %%ymm0, %0\n"                       \
        : "=m"(a)                               \
        : "m"(val)                                \
        : "ymm0","memory")
        
#define FILL_F64x2_SSE22(a, val)          \
    asm volatile(                                    \
        "movupd %%xmm0, %1\n"                        \
        "movupd %%xmm0, %0\n"                        \
        : "=m"(a)                               \
        : "m"(val)                                \
        : "xmm0","memory")          
              
#define FILL_F64x2_ARM(a, val)             \
    asm volatile(                                \
        "dup v0.2d, %1\n"                        \
        "st1 {v0.2d}, [%0]\n"                     \
        :                                        \
        : "r"(a), "r"(val)                 \
        : "v0","memory")        

#define FILL_F64_SVE(a, val, count)       \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                  \
        "whilelt p0.d, x4, %2\n"               \
        "b.none p0, 2f\n"                       \
        "dup z0.d, %1\n"                        \
        "st1d z0.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b 1b\n"                                 \
        "2:\n"                                  \
        :                                        \
        : "r"(a), "r"(val), "r"(count)    \
        : "x4","p0","z0","memory")
        
#define FILL_F64_SVE2(a, val, count)      \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                  \
        "whilelt p0.d, x4, %2\n"               \
        "b.none p0, 2f\n"                       \
        "dup z0.d, %1\n"                        \
        "st1d z0.d, p0, [%0, x4, lsl #3]\n"     \
        "incd x4\n"                              \
        "b.any p0, 1b\n"                         \
        "2:\n"                                  \
        :                                        \
        : "r"(a), "r"(val), "r"(count)    \
        : "x4","p0","z0","memory")
        
/*__FLOATING POINT__*/        
        
#define FILL_F32x16_A512(a, val)                \
    asm volatile(                               \
        "vbroadcastss %%zmm0, %1\n"             \
        "vmovups %%zmm0, %0\n"                  \
        : "=m"(a)                               \
        : "m"(val)                              \
        : "zmm0","memory")

#define FILL_F32x8_AVX2(a, val)                 \
    asm volatile(                               \
        "vbroadcastss %%ymm0, %1\n"             \
        "vmovups %%ymm0, %0\n"                  \
        : "=m"(a)                               \
        : "m"(val)                              \
        : "ymm0","memory")
        
#define FILL_F32x4_SSE2(a, val)                  \
    asm volatile(                               \
        "movss %1, %%xmm0\n"                    \
        "shufps $0x00, %%xmm0, %%xmm0\n"        \
        "movups %%xmm0, %0\n"                   \
        : "=m"(a)                               \
        : "m"(val)                              \
        : "xmm0","memory")
        
#define FILL_F32x4_ARM(a, val)                  \
    asm volatile(                               \
        "dup v0.4s, %w1\n"                      \
        "st1 {v0.4s}, [%0]\n"                   \
        :                                        \
        : "r"(a), "r"(val)                      \
        : "v0","memory")
        
#define FILL_F32x4_ARMv7(a, val)               \
    asm volatile(                               \
        "vdup.32 q0, %1\n"                      \
        "vst1.32 {q0}, [%0]\n"                  \
        :                                       \
        : "r"(a), "r"(val)                      \
        : "q0", "memory")        
        
#define FILL_F32_SVE(a, val, count)             \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                  \
        "whilelt p0.s, x4, %2\n"                \
        "b.none p0, 2f\n"                       \
        "dup z0.s, %1\n"                        \
        "st1w z0.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                             \
        "b 1b\n"                                 \
        "2:\n"                                  \
        :                                        \
        : "r"(a), "r"(val), "r"(count)          \
        : "x4","p0","z0","memory")
        
#define FILL_F32_SVE2(a, val, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                  \
        "whilelt p0.s, x4, %2\n"                \
        "b.none p0, 2f\n"                       \
        "dup z0.s, %1\n"                        \
        "st1w z0.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                             \
        "b.any p0, 1b\n"                         \
        "2:\n"                                  \
        :                                        \
        : "r"(a), "r"(val), "r"(count)          \
        : "x4","p0","z0","memory")
        
/*__INTEGER__*/

#define FILL_I32x16_A512(a, val)                \
    asm volatile(                               \
        "vpbroadcastd %%zmm0, %1\n"             \
        "vmovdqu32 %%zmm0, %0\n"                \
        : "=m"(a)                               \
        : "m"(val)                               \
        : "zmm0","memory")
        
#define FILL_I32x8_AVX2(a, val)                 \
    asm volatile(                               \
        "vpbroadcastd %%ymm0, %1\n"             \
        "vmovdqu %%ymm0, %0\n"                  \
        : "=m"(a)                               \
        : "m"(val)                               \
        : "ymm0","memory")
        
#define FILL_I32x4_SSE2(a, val)                  \
    asm volatile(                               \
        "movd %1, %%xmm0\n"                     \
        "pshufd $0x00, %%xmm0, %%xmm0\n"        \
        "movdqu %%xmm0, %0\n"                   \
        : "=m"(a)                               \
        : "m"(val)                               \
        : "xmm0","memory")
        
#define FILL_I32x4_ARM(a, val)                  \
    asm volatile(                               \
        "dup v0.4s, %w1\n"                      \
        "st1 {v0.4s}, [%0]\n"                   \
        :                                        \
        : "r"(a), "r"(val)                      \
        : "v0","memory")

#define FILL_I32x4_ARMv7(a, val)                \
    asm volatile(                               \
        "vdup.32 q0, %1\n"                      \
        "vst1.32 {q0}, [%0]\n"                  \
        :                                        \
        : "r"(a), "r"(val)                      \
        : "q0","memory")

#define FILL_I32_SVE(a, val, count)             \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                  \
        "whilelt p0.s, x4, %2\n"                \
        "b.none p0, 2f\n"                       \
        "dup z0.s, %1\n"                        \
        "st1w z0.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                             \
        "b 1b\n"                                \
        "2:\n"                                  \
        :                                        \
        : "r"(a), "r"(val), "r"(count)          \
        : "x4","p0","z0","memory")

#define FILL_I32_SVE2(a, val, count)            \
    asm volatile(                               \
        "mov x4, #0\n"                          \
        "1:\n"                                  \
        "whilelt p0.s, x4, %2\n"                \
        "b.none p0, 2f\n"                       \
        "dup z0.s, %1\n"                        \
        "st1w z0.s, p0, [%0, x4, lsl #2]\n"     \
        "incw x4\n"                             \
        "b.any p0, 1b\n"                        \
        "2:\n"                                  \
        :                                        \
        : "r"(a), "r"(val), "r"(count)          \
        : "x4","p0","z0","memory")

#define FILL_I16x32_A512(a, val)                     \
    asm volatile(                                    \
        "movzx %w1, %%eax\n"                         \
        "vpbroadcastw %%ax, %%zmm0\n"                \
        "vmovdqu16 %%zmm0, (%0)\n"                   \
        :                                            \
        : "r"(a), "r"(val)                           \
        : "eax","zmm0","memory")

#define FILL_I16x16_AVX2(a, val)                     \
    asm volatile(                                    \
        "movzx %w1, %%eax\n"                         \
        "vpbroadcastw %%ax, %%ymm0\n"                \
        "vmovdqu %%ymm0, (%0)\n"                     \
        "vzeroupper\n"                               \
        :                                            \
        : "r"(a), "r"(val)                           \
        : "eax","ymm0","memory")

#define FILL_I16x8_SSE2(a, val)                      \
    asm volatile(                                    \
        "movzx %w1, %%eax\n"                         \
        "movd %%eax, %%xmm0\n"                       \
        "pshuflw $0x00, %%xmm0, %%xmm0\n"            \
        "pshufd  $0x00, %%xmm0, %%xmm0\n"            \
        "movdqu %%xmm0, (%0)\n"                      \
        :                                            \
        : "r"(a), "r"(val)                           \
        : "eax","xmm0","memory")

#define FILL_I16x8_ARM(a, val)                       \
    asm volatile(                                    \
        "dup v0.8h, %w1\n"                           \
        "st1 {v0.8h}, [%0]\n"                        \
        :                                            \
        : "r"(a), "r"(val)                           \
        : "v0","memory")

#define FILL_I16x8_ARMv7(a, val)                     \
    asm volatile(                                    \
        "vdup.16 q0, %1\n"                           \
        "vst1.16 {q0}, [%0]\n"                       \
        :                                            \
        : "r"(a), "r"(val)                           \
        : "q0","memory")

#define FILL_I16_SVE(a, val, count)                  \
    asm volatile(                                    \
        "mov x4, #0\n"                               \
        "1:\n"                                       \
        "whilelt p0.h, x4, %2\n"                     \
        "b.none p0, 2f\n"                            \
        "dup z0.h, %1\n"                             \
        "st1h z0.h, p0, [%0, x4, lsl #1]\n"          \
        "inch x4\n"                                  \
        "b 1b\n"                                     \
        "2:\n"                                       \
        :                                            \
        : "r"(a), "r"(val), "r"(count)               \
        : "x4","p0","z0","memory")

#define FILL_I16_SVE2(a, val, count)                 \
    asm volatile(                                    \
        "mov x4, #0\n"                               \
        "1:\n"                                       \
        "whilelt p0.h, x4, %2\n"                     \
        "b.none p0, 2f\n"                            \
        "dup z0.h, %1\n"                             \
        "st1h z0.h, p0, [%0, x4, lsl #1]\n"          \
        "inch x4\n"                                  \
        "b.any p0, 1b\n"                             \
        "2:\n"                                       \
        :                                            \
        : "r"(a), "r"(val), "r"(count)               \
        : "x4","p0","z0","memory")

#define FILL_I8x64_A512(a, val)                     \
    asm volatile(                                   \
        "movzx %w1, %%eax\n"                        \
        "vpbroadcastb %%al, %%zmm0\n"               \
        "vmovdqu8 %%zmm0, (%0)\n"                   \
        :                                           \
        : "r"(a), "r"(val)                          \
        : "eax","zmm0","memory")

#define FILL_I8x32_AVX2(a, val)                     \
    asm volatile(                                   \
        "movzx %w1, %%eax\n"                        \
        "vpbroadcastb %%al, %%ymm0\n"               \
        "vmovdqu %%ymm0, (%0)\n"                    \
        "vzeroupper\n"                              \
        :                                           \
        : "r"(a), "r"(val)                          \
        : "eax","ymm0","memory")

#define FILL_I8x16_SSE2(a, val)                     \
    asm volatile(                                   \
        "movzx %w1, %%eax\n"                        \
        "movd %%eax, %%xmm0\n"                      \
        "punpcklbw %%xmm0, %%xmm0\n"                \
        "punpcklwd %%xmm0, %%xmm0\n"                \
        "pshufd $0x00, %%xmm0, %%xmm0\n"            \
        "movdqu %%xmm0, (%0)\n"                     \
        :                                           \
        : "r"(a), "r"(val)                          \
        : "eax","xmm0","memory")

#define FILL_I8x16_ARM(a, val)                      \
    asm volatile(                                   \
        "dup v0.16b, %w1\n"                         \
        "st1 {v0.16b}, [%0]\n"                      \
        :                                           \
        : "r"(a), "r"(val)                          \
        : "v0","memory")

#define FILL_I8x16_ARMv7(a, val)                    \
    asm volatile(                                   \
        "vdup.8 q0, %1\n"                           \
        "vst1.8 {q0}, [%0]\n"                       \
        :                                           \
        : "r"(a), "r"(val)                          \
        : "q0","memory")

#define FILL_I8_SVE(a, val, count)                  \
    asm volatile(                                   \
        "mov x4, #0\n"                              \
        "1:\n"                                      \
        "whilelt p0.b, x4, %2\n"                    \
        "b.none p0, 2f\n"                           \
        "dup z0.b, %1\n"                            \
        "st1b z0.b, p0, [%0, x4]\n"                 \
        "incb x4\n"                                 \
        "b 1b\n"                                    \
        "2:\n"                                      \
        :                                           \
        : "r"(a), "r"(val), "r"(count)              \
        : "x4","p0","z0","memory")

#define FILL_I8_SVE2(a, val, count)                 \
    asm volatile(                                   \
        "mov x4, #0\n"                              \
        "1:\n"                                      \
        "whilelt p0.b, x4, %2\n"                    \
        "b.none p0, 2f\n"                           \
        "dup z0.b, %1\n"                            \
        "st1b z0.b, p0, [%0, x4]\n"                 \
        "incb x4\n"                                 \
        "b.any p0, 1b\n"                            \
        "2:\n"                                      \
        :                                           \
        : "r"(a), "r"(val), "r"(count)              \
        : "x4","p0","z0","memory")
        
