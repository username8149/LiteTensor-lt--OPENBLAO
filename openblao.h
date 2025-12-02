/*****************************
OPENBLAO
BASIC.LINEAR.ARRAY.OPERATION
******************************/

/*__LIBRARY OR FILES INCLUDE__*/
#include "openblao_platform.h"
#include "openblao_imple.h"
/**********************************/
#include <thread>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
/**********************************/

/*__FILLS ELEMENT ARRAY__*/
inline void __openblao_fills_int32(int32_t *a,
                                   const int32_t value,
                                   const size_t n,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                FILL_I32x16_A512(a + i, value);
#elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                FILL_I32x8_AVX2(a + i, value);
#elif PLATFORM == 128
            for (; i + 4 <= end; i += 4)
                FILL_I32x4_SSE2(a + i, value);
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                FILL_I32_SVE2(a + i, value, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                FILL_I32_SVE(a + i, value, 16);
#elif PLATFORM == 64
            for (; i + 4 <= end; i += 4)
                FILL_I32x4_ARM(a + i, value);
#elif PLATFORM == 32
            for (; i + 4 <= end; i += 4)
                FILL_I32x4_ARMv7(a + i, value);
#endif

            for (; i < end; ++i)
                a[i] = value;
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

void __openblao_fills_int32(int32_t *a,
                            const int32_t value,
                            const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 16 <= n; i += 16)
        FILL_I32x16_A512(a + i, value);
#elif PLATFORM == 256
    for (; i + 8 <= n; i += 8)
        FILL_I32x8_AVX2(a + i, value);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4)
        FILL_I32x4_SSE2(a + i, value);
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        FILL_I32_SVE2(a + i, value, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        FILL_I32_SVE(a + i, value, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4)
        FILL_I32x4_ARM(a + i, value);
#elif PLATFORM == 32
    for (; i + 4 <= n; i += 4)
        FILL_I32x4_ARMv7(a + i, value);
#endif

    for (; i < n; ++i)
        a[i] = value;
}

inline void __openblao_fills_int16(int16_t *a,
                                   const int16_t value,
                                   const size_t n,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
    for (; i + 32 <= end; i += 32)
        FILL_I16x32_A512(a + i, value);
#elif PLATFORM == 256
    for (; i + 16 <= end; i += 16)
        FILL_I16x16_AVX2(a + i, value);
#elif PLATFORM == 128
    for (; i + 8 <= end; i += 8)
        FILL_I16x8_SSE2(a + i, value);
#elif PLATFORM == 2048
    for (; i + 32 <= end; i += 32)
        FILL_I16_SVE2(a + i, value, 32);
#elif PLATFORM == 1024
    for (; i + 32 <= end; i += 32)
        FILL_I16_SVE(a + i, value, 32);
#elif PLATFORM == 64
    for (; i + 8 <= end; i += 8)
        FILL_I16x8_ARM(a + i, value);
#elif PLATFORM == 32
    for (; i + 8 <= end; i += 8)
        FILL_I16x8_ARMv7(a + i, value);
#endif

            for (; i < end; ++i)
                a[i] = value;
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

void __openblao_fills_int16(int16_t *a,
                            const int16_t value,
                            const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 32 <= n; i += 32)
        FILL_I16x32_A512(a + i, value);
#elif PLATFORM == 256
    for (; i + 16 <= n; i += 16)
        FILL_I16x16_AVX2(a + i, value);
#elif PLATFORM == 128
    for (; i + 8 <= n; i += 8)
        FILL_I16x8_SSE2(a + i, value);
#elif PLATFORM == 2048
    for (; i + 32 <= n; i += 32)
        FILL_I16_SVE2(a + i, value, 32);
#elif PLATFORM == 1024
    for (; i + 32 <= n; i += 32)
        FILL_I16_SVE(a + i, value, 32);
#elif PLATFORM == 64
    for (; i + 8 <= n; i += 8)
        FILL_I16x8_ARM(a + i, value);
#elif PLATFORM == 32
    for (; i + 8 <= n; i += 8)
        FILL_I16x8_ARMv7(a + i, value);
#endif

    for (; i < n; ++i)
        a[i] = value;
}

inline void __openblao_fills_int8(int8_t *a,
                                   const int8_t value,
                                   const size_t n,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
    for (; i + 64 <= end; i += 64)
        FILL_I8x64_A512(a + i, value);
#elif PLATFORM == 256
    for (; i + 32 <= end; i += 32)
        FILL_I8x32_AVX2(a + i, value);
#elif PLATFORM == 128
    for (; i + 16 <= end; i += 16);
        FILL_I8x16_SSE2(a + i, value);
#elif PLATFORM == 2048
    for (; i + 128 <= end; i += 128)
        FILL_I8_SVE2(a + i, value, 128);
#elif PLATFORM == 1024
    for (; i + 128 <= end; i += 128)
        FILL_I8_SVE(a + i, value, 128);
#elif PLATFORM == 64
    for (; i + 16 <= end; i += 16)
        FILL_I8x16_ARM(a + i, value);
#elif PLATFORM == 32
    for (; i + 16 <= end; i += 16)
        FILL_I8x16_ARMv7(a + i, value);
#endif

            for (; i < end; ++i)
                a[i] = value;
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

void __openblao_fills_int8(int8_t *a,
                            const int8_t value,
                            const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 64 <= n; i += 64)
        FILL_I8x64_A512(a + i, value);
#elif PLATFORM == 256
    for (; i + 32 <= n; i += 32)
        FILL_I8x32_AVX2(a + i, value);
#elif PLATFORM == 128
    for (; i + 16 <= n; i += 16)
        FILL_I8x16_SSE2(a + i, value);
#elif PLATFORM == 2048
    for (; i + 128 <= n; i += 128)
        FILL_I8_SVE2(a + i, value, 128);
#elif PLATFORM == 1024
    for (; i + 128 <= n; i += 128)
        FILL_I8_SVE(a + i, value, 128);
#elif PLATFORM == 64
    for (; i + 16 <= n; i += 16)
        FILL_I8x16_ARM(a + i, value);
#elif PLATFORM == 32
    for (; i + 16 <= n; i += 16)
        FILL_I8x16_ARMv7(a + i, value);
#endif

    for (; i < n; ++i)
        a[i] = value;
}

inline void __openblao_fills_float32(float *__restrict a,
                                     const float value,
                                     const size_t n,
                                     const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                FILL_F32x16_A512(a + i, value);
#elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                FILL_F32x8_AVX2(a + i, value);
#elif PLATFORM == 128
            for (; i + 4 <= end; i += 4)
                FILL_F32x4_SSE2(a + i, value);
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                FILL_F32_SVE2(a + i, value, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                FILL_F32_SVE(a + i, value, 16);
#elif PLATFORM == 64
            for (; i + 4 <= end; i += 4)
                FILL_F32x4_ARM(a + i, value);
#elif PLATFORM == 32
            for (; i + 4 <= end; i += 4)
                FILL_F32x4_ARMv7(a + i, value);
#endif

            for (; i < end; ++i)
                a[i] = value;
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_fills_float32(float *__restrict a,
                                     const float value,
                                     const size_t n)
{
    size_t i = 0;
#if PLATFORM == 512
    for (; i + 16 <= n; i += 16)
        FILL_F32x16_A512(a + i, value);
#elif PLATFORM == 256
    for (; i + 8 <= n; i += 8)
        FILL_F32x8_AVX2(a + i, value);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4)
        FILL_F32x4_SSE2(a + i, value);
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        FILL_F32_SVE2(a + i, value, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        FILL_F32_SVE(a + i, value, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4)
        FILL_F32x4_ARM(a + i, value);
#elif PLATFORM == 32
    for (; i + 4 <= n; i += 4)
        FILL_F32x4_ARMv7(a + i, value);
#endif

    for (; i < n; ++i)
        a[i] = value;
}

inline void __openblao_fills_float64(double *__restrict a,
                                     const double value,
                                     const size_t n,
                                     const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 8 <= end; i += 8)
                FILL_F64x8_A512(a + i, value);
#elif PLATFORM == 256
            for (; i + 4 <= end; i += 4)
                FILL_F64x4_AVX2(a + i, value);
#elif PLATFORM == 128
            for (; i + 2 <= end; i += 2)
                FILL_F64x2_SSE2(a + i, value);
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                FILL_F64_SVE2(a + i, value, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                FILL_F64_SVE(a + i, value, 16);
#elif PLATFORM == 64
            for (; i + 2 <= end; i += 2)
                FILL_F64x2_ARM(a + i, value);
#endif

            for (; i < end; ++i)
                a[i] = value;
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_fills_float64(double *__restrict a,
                                     const double value,
                                     const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 8 <= n; i += 8)
        FILL_F64x8_A512(a + i, value);
#elif PLATFORM == 256
    for (; i + 4 <= n; i += 4)
        FILL_F64x4_AVX2(a + i, value);
#elif PLATFORM == 128
    for (; i + 2 <= n; i += 2)
        FILL_F64x2_SSE2(a + i, value);
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        FILL_F64_SVE2(a + i, value, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        FILL_F64_SVE(a + i, value, 16);
#elif PLATFORM == 64
    for (; i + 2 <= n; i += 2)
        FILL_F64x2_ARM(a + i, value);
#endif

    for (; i < n; ++i)
        a[i] = value;
}

inline void __openblao_Add_float64(const double *a, const double *b, double *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 8 <= end; i += 8)
                ADD_F64x8_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 4 <= end; i += 4)
                ADD_F64x4_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 4 <= end; i += 4) {
                ADD_F64x2_SSE2(a + i, b + i, c + i);
                ADD_F64x2_SSE2(a + i + 2, b + i + 2, c + i + 2);
            }
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                ADD_F64_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                ADD_F64_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 4 <= end; i += 4) {
                ADD_F64x2_ARM(a + i, b + i, c + i);
                ADD_F64x2_ARM(a + i + 2, b + i + 2, c + i + 2);
            }
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] + b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Add_float64(const double *a, const double *b, double *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 8 <= n; i += 8)
        ADD_F64x8_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 4 <= n; i += 4)
        ADD_F64x4_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4) {
        ADD_F64x2_SSE2(a + i, b + i, c + i);
        ADD_F64x2_SSE2(a + i + 2, b + i + 2, c + i + 2);
    }
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        ADD_F64_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        ADD_F64_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4) {
        ADD_F64x2_ARM(a + i, b + i, c + i);
        ADD_F64x2_ARM(a + i + 2, b + i + 2, c + i + 2);
    }
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
}

inline void __openblao_Sub_float64(const double *a, const double *b, double *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 8 <= end; i += 8)
                SUB_F64x8_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 4 <= end; i += 4)
                SUB_F64x4_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 4 <= end; i += 4) {
                SUB_F64x2_SSE2(a + i, b + i, c + i);
                SUB_F64x2_SSE2(a + i + 2, b + i + 2, c + i + 2);
            }
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                SUB_F64_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                SUB_F64_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 4 <= end; i += 4) {
                SUB_F64x2_ARM(a + i, b + i, c + i);
                SUB_F64x2_ARM(a + i + 2, b + i + 2, c + i + 2);
            }
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] - b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Sub_float64(const double *a, const double *b, double *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 8 <= n; i += 8)
        SUB_F64x8_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 4 <= n; i += 4)
        SUB_F64x4_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4) {
        SUB_F64x2_SSE2(a + i, b + i, c + i);
        SUB_F64x2_SSE2(a + i + 2, b + i + 2, c + i + 2);
    }
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        SUB_F64_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        SUB_F64_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4) {
        SUB_F64x2_ARM(a + i, b + i, c + i);
        SUB_F64x2_ARM(a + i + 2, b + i + 2, c + i + 2);
    }
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] - b[i];
    }
}

inline void __openblao_Mul_float64(const double *a, const double *b, double *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 8 <= end; i += 8)
                MUL_F64x8_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 4 <= end; i += 4)
                MUL_F64x4_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 4 <= end; i += 4) {
                MUL_F64x2_SSE2(a + i, b + i, c + i);
                MUL_F64x2_SSE2(a + i + 2, b + i + 2, c + i + 2);
            }
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                MUL_F64_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                MUL_F64_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 4 <= end; i += 4) {
                MUL_F64x2_ARM(a + i, b + i, c + i);
                MUL_F64x2_ARM(a + i + 2, b + i + 2, c + i + 2);
            }
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] * b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Mul_float64(const double *a, const double *b, double *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 8 <= n; i += 8)
        MUL_F64x8_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 4 <= n; i += 4)
        MUL_F64x4_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4) {
        MUL_F64x2_SSE2(a + i, b + i, c + i);
        MUL_F64x2_SSE2(a + i + 2, b + i + 2, c + i + 2);
    }
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        MUL_F64_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        MUL_F64_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4) {
        MUL_F64x2_ARM(a + i, b + i, c + i);
        MUL_F64x2_ARM(a + i + 2, b + i + 2, c + i + 2);
    }
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] * b[i];
    }
}

inline void __openblao_Div_float64(const double *a, const double *b, double *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 8 <= end; i += 8)
                DIV_F64x8_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 4 <= end; i += 4)
                DIV_F64x4_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 4 <= end; i += 4) {
                DIV_F64x2_SSE2(a + i, b + i, c + i);
                DIV_F64x2_SSE2(a + i + 2, b + i + 2, c + i + 2);
            }
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                DIV_F64_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                DIV_F64_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 4 <= end; i += 4) {
                DIV_F64x2_ARM(a + i, b + i, c + i);
                DIV_F64x2_ARM(a + i + 2, b + i + 2, c + i + 2);
        }
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] / b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Div_float64(const double *a, const double *b, double *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 8 <= n; i += 8)
        DIV_F64x8_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 4 <= n; i += 4)
        DIV_F64x4_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4) {
        DIV_F64x2_SSE2(a + i, b + i, c + i);
        DIV_F64x2_SSE2(a + i + 2, b + i + 2, c + i + 2);
    }
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        DIV_F64_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        DIV_F64_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4) {
        DIV_F64x2_ARM(a + i, b + i, c + i);
        DIV_F64x2_ARM(a + i + 2, b + i + 2, c + i + 2);
    }
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] / b[i];
    }
}

inline void __openblao_Add_float32(const float *a, const float *b, float *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                ADD_F32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                ADD_F32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 8 <= end; i += 8) {
                ADD_F32x4_SSE2(a + i, b + i, c + i);
                ADD_F32x4_SSE2(a + i + 4, b + i + 4, c + i + 4);
            }
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                ADD_F32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                ADD_F32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 8 <= end; i += 8) {
                ADD_F32x4_ARM(a + i, b + i, c + i);
                ADD_F32x4_ARM(a + i + 4, b + i + 4, c + i + 4);
            }
#elif PLATFORM == 32
            for (; i + 8 <= end; i += 8) {
                ADD_F32x4_ARMv7(a + i, b + i, c + i);
                ADD_F32x4_ARMv7(a + i + 4, b + i + 4, c + i + 4);
            }
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] + b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Add_float32(const float *a, const float *b, float *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 16 <= n; i += 16)
        ADD_F32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 8 <= n; i += 8)
        ADD_F32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 8 <= n; i += 8) {
        ADD_F32x4_SSE2(a + i, b + i, c + i);
        ADD_F32x4_SSE2(a + i + 4, b + i + 4, c + i + 4);
    }
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        ADD_F32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        ADD_F32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 8 <= n; i += 8) {
        ADD_F32x4_ARM(a + i, b + i, c + i);
        ADD_F32x4_ARM(a + i + 4, b + i + 4, c + i + 4);
    }
#elif PLATFORM == 32
            for (; i + 8 <= n; i += 8) {
                ADD_F32x4_ARMv7(a + i, b + i, c + i);
                ADD_F32x4_ARMv7(a + i + 4, b + i + 4, c + i + 4);
            }
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
}

inline void __openblao_Sub_float32(const float *a, const float *b, float *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                SUB_F32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                SUB_F32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 8 <= end; i += 8) {
                SUB_F32x4_SSE2(a + i, b + i, c + i);
                SUB_F32x4_SSE2(a + i + 4, b + i + 4, c + i + 4);
            }
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                SUB_F32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                SUB_F32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 8 <= end; i += 8) {
                SUB_F32x4_ARM(a + i, b + i, c + i);
                SUB_F32x4_ARM(a + i + 4, b + i + 4, c + i + 4);
            }
#elif PLATFORM == 32
            for (; i + 8 <= end; i += 8) {
                SUB_F32x4_ARMv7(a + i, b + i, c + i);
                SUB_F32x4_ARMv7(a + i + 4, b + i + 4, c + i + 4);
            }
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] - b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Sub_float32(const float *a, const float *b, float *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 16 <= n; i += 16)
        SUB_F32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 8 <= n; i += 8)
        SUB_F32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4)
        SUB_F32x4_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        SUB_F32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        SUB_F32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4)
        SUB_F32x4_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
            for (; i + 4 <= n; i += 4)
                SUB_F32x4_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] - b[i];
    }
}

inline void __openblao_Mul_float32(const float *a, const float *b, float *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                MUL_F32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                MUL_F32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 8 <= end; i += 8) {
                MUL_F32x4_SSE2(a + i, b + i, c + i);
                MUL_F32x4_SSE2(a + i + 4, b + i + 4, c + i + 4);
            }
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                MUL_F32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                MUL_F32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 8 <= end; i += 8) {
                MUL_F32x4_ARM(a + i, b + i, c + i);
                MUL_F32x4_ARM(a + i + 4, b + i + 4, c + i + 4);
            }
#elif PLATFORM == 32
            for (; i + 8 <= end; i += 8) {
                MUL_F32x4_ARMv7(a + i, b + i, c + i);
                MUL_F32x4_ARMv7(a + i + 4, b + i + 4, c + i + 4);
            }
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] * b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Mul_float32(const float *a, const float *b, float *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 16 <= n; i += 16)
        MUL_F32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 8 <= n; i += 8)
        MUL_F32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4)
        MUL_F32x4_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        MUL_F32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        MUL_F32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4)
        MUL_F32x4_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
            for (; i + 4 <= n; i += 4)
                MUL_F32x4_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] * b[i];
    }
}

inline void __openblao_Div_float32(const float *a, const float *b, float *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                DIV_F32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                DIV_F32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 8 <= end; i += 8)
                DIV_F32x4_SSE2(a + i, b + i, c + i);
                DIV_F32x4_SSE2(a + i + 4, b + i + 4, c + i + 4);
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                DIV_F32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                DIV_F32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 8 <= end; i += 8)
                DIV_F32x4_ARM(a + i, b + i, c + i);
                DIV_F32x4_ARM(a + i + 4, b + i + 4, c + i + 4);
#elif PLATFORM == 32
            for (; i + 8 <= end; i += 8)
                DIV_F32x4_ARMv7(a + i, b + i, c + i);
                DIV_F32x4_ARMv7(a + i + 4, b + i + 4, c + i + 4);
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] / b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Div_float32(const float *a, const float *b, float *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 16 <= n; i += 16)
        DIV_F32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 8 <= n; i += 8)
        DIV_F32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4)
        DIV_F32x4_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        DIV_F32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        DIV_F32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4)
        DIV_F32x4_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
            for (; i + 4 <= n; i += 4)
                DIV_F32x4_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] / b[i];
    }
}

inline void __openblao_Add_int32(const int32_t *a, const int32_t *b, int32_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                ADD_I32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                ADD_I32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 4 <= end; i += 4)
                ADD_I32x4_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                ADD_I32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                ADD_I32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
            for (; i + 4 <= end; i += 4)
                ADD_I32x4_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
            for (; i + 4 <= end; i += 4)
                ADD_I32x4_ARMv7(a + i, b + i, c + i);
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] + b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Add_int32(const int32_t *a, const int32_t *b, int32_t *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 16 <= n; i += 16)
        ADD_I32x16_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 8 <= n; i += 8)
        ADD_I32x8_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 4 <= n; i += 4)
        ADD_I32x4_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 16 <= n; i += 16)
        ADD_I32_SVE2(a + i, b + i, c + i, 16);
#elif PLATFORM == 1024
    for (; i + 16 <= n; i += 16)
        ADD_I32_SVE(a + i, b + i, c + i, 16);
#elif PLATFORM == 64
    for (; i + 4 <= n; i += 4)
        ADD_I32x4_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
            for (; i + 4 <= n; i += 4)
                ADD_I32x4_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
}

inline void __openblao_Sub_int32(const int32_t* a, const int32_t* b, int32_t* c, const size_t n, const size_t thread_use) {
    
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread* threads = new std::thread[real_threads];
            
    for (size_t t = 0; t < real_threads; ++t) {
        size_t start = t * chunk;
        if (start >= n) {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n) end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;
            
            #if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                    SUB_I32x16_A512(a + i, b + i, c + i);
            #elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                    SUB_I32x8_AVX2(a + i, b + i, c + i);
            #elif PLATFORM == 128
            for (; i + 4 <= end; i += 4)
                    SUB_I32x4_SSE2(a + i, b + i, c + i);
            #elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                    SUB_I32_SVE2(a + i, b + i, c + i, 16);
            #elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                    SUB_I32_SVE(a + i, b + i, c + i, 16);
            #elif PLATFORM == 64
            for (; i + 4 <= end; i += 4)
                    SUB_I32x4_ARM(a + i, b + i, c + i);
            #elif PLATFORM == 32
            for (; i + 4 <= end; i += 4)
                    SUB_I32x4_ARMv7(a + i, b + i, c + i);
            #endif
                     
            for (; i < end; ++i) {
                c[i] = a[i] - b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Sub_int32(const int32_t* a, const int32_t* b, int32_t* c, const size_t n) {
                       
            size_t i = 0;
   
            #if PLATFORM == 512
            for (; i + 16 <= n; i += 16)
                    SUB_I32x16_A512(a + i, b + i, c + i);
            #elif PLATFORM == 256
            for (; i + 8 <= n; i += 8)
                    SUB_I32x8_AVX2(a + i, b + i, c + i);
            #elif PLATFORM == 128
            for (; i + 4 <= n; i += 4)
                    SUB_I32x4_SSE2(a + i, b + i, c + i);
            #elif PLATFORM == 2048
            for (; i + 16 <= n; i += 16)
                    SUB_I32_SVE2(a + i, b + i, c + i, 16);
            #elif PLATFORM == 1024
            for (; i + 16 <= n; i += 16)
                    SUB_I32_SVE(a + i, b + i, c + i, 16);
            #elif PLATFORM == 64
            for (; i + 4 <= n; i += 4)
                    SUB_I32x4_ARM(a + i, b + i, c + i);
              #elif PLATFORM == 32
            for (; i + 4 <= n; i += 4)
                SUB_I32x4_ARMv7(a + i, b + i, c + i);
            #endif
                     
            for (; i < n; ++i) {
                c[i] = a[i] - b[i];
            }
}

inline void __openblao_Mul_int32(const int32_t* a, const int32_t* b, int32_t* c, const size_t n, const size_t thread_use) {
    
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread* threads = new std::thread[real_threads];
            
    for (size_t t = 0; t < real_threads; ++t) {
        size_t start = t * chunk;
        if (start >= n) {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n) end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;
            
            #if PLATFORM == 512
            for (; i + 16 <= end; i += 16)
                    MUL_I32x16_A512(a + i, b + i, c + i);
            #elif PLATFORM == 256
            for (; i + 8 <= end; i += 8)
                    MUL_I32x8_AVX2(a + i, b + i, c + i);
            #elif PLATFORM == 128
            for (; i + 4 <= end; i += 4)
                    MUL_I32x4_SSE2(a + i, b + i, c + i);
            #elif PLATFORM == 2048
            for (; i + 16 <= end; i += 16)
                    MUL_I32_SVE2(a + i, b + i, c + i, 16);
            #elif PLATFORM == 1024
            for (; i + 16 <= end; i += 16)
                    MUL_I32_SVE(a + i, b + i, c + i, 16);
            #elif PLATFORM == 64
            for (; i + 4 <= end; i += 4)
                    MUL_I32x4_ARM(a + i, b + i, c + i);
            #elif PLATFORM == 32
            for (; i + 4 <= end; i += 4)
                    MUL_I32x4_ARMv7(a + i, b + i, c + i);
            #endif
                     
            for (; i < end; ++i) {
                c[i] = a[i] * b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Mul_int32(const int32_t* a, const int32_t* b, int32_t* c, const size_t n) {
                       
            size_t i = 0;
   
            #if PLATFORM == 512
            for (; i + 16 <= n; i += 16)
                    MUL_I32x16_A512(a + i, b + i, c + i);
            #elif PLATFORM == 256
            for (; i + 8 <= n; i += 8)
                    MUL_I32x8_AVX2(a + i, b + i, c + i);
            #elif PLATFORM == 128
            for (; i + 4 <= n; i += 4)
                    MUL_I32x4_SSE2(a + i, b + i, c + i);
            #elif PLATFORM == 2048
            for (; i + 16 <= n; i += 16)
                    MUL_I32_SVE2(a + i, b + i, c + i, 16);
            #elif PLATFORM == 1024
            for (; i + 16 <= n; i += 16)
                    MUL_I32_SVE(a + i, b + i, c + i, 16);
            #elif PLATFORM == 64
            for (; i + 4 <= n; i += 4)
                    MUL_I32x4_ARM(a + i, b + i, c + i);
            #elif PLATFORM == 32
            for (; i + 4 <= n; i += 4)
                    MUL_I32x4_ARMv7(a + i, b + i, c + i);
            #endif
                     
            for (; i < n; ++i) {
                c[i] = a[i] * b[i];
            }
}

inline void __openblao_Div_int32(const int32_t* a, const int32_t* b, int32_t* c, const size_t n, const size_t thread_use) {
    
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread* threads = new std::thread[real_threads];
            
    for (size_t t = 0; t < real_threads; ++t) {
        size_t start = t * chunk;
        if (start >= n) {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n) end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;
            
            #if ARCT == 8664
            for (; i + 8 <= end; i += 8)
                    DIV_I32x8_x86_64(a + i, b + i, c + i);
            #elif ARCT == 8633
            for (; i + 8 <= end; i += 8)
                    DIV_I32x8_Ax86_32(a + i, b + i, c + i);
            #elif ARCT == 6464
            for (; i + 8 <= end; i += 8)
                    DIV_I32x8_ARM(a + i, b + i, c + i);
            #elif ARCT == 6432
            for (; i + 8 <= end; i += 8)
                    DIV_I32x8_ARMv7(a + i, b + i, c + i);
            #endif
                     
            for (; i < end; ++i) {
                c[i] = a[i] / b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Div_int32(const int32_t* a, const int32_t* b, int32_t* c, const size_t n) {
                       
            size_t i = 0;
   
            #if ARCT == 8664
            for (; i + 8 <= n; i += 8)
                    DIV_I32x8_x86_64(a + i, b + i, c + i);
            #elif ARCT == 8633
            for (; i + 8 <= n; i += 8)
                    DIV_I32x8_Ax86_32(a + i, b + i, c + i);
            #elif ARCT == 6464
            for (; i + 8 <= n; i += 8)
                    DIV_I32x8_ARM(a + i, b + i, c + i);
            #elif ARCT == 6432
            for (; i + 8 <= n; i += 8)
                    DIV_I32x8_ARMv7(a + i, b + i, c + i);
            #endif
                     
            for (; i < n; ++i) {
                c[i] = a[i] / b[i];
            }
}

/*__INTERGER 16__*/

inline void __openblao_Add_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 32 <= end; i += 32)
                ADD_I16x32_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 16 <= end; i += 16)
                ADD_I16x16_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 8 <= end; i += 8)
                ADD_I16x8_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
            for (; i + 32 <= end; i += 32)
                ADD_I16_SVE2(a + i, b + i, c + i, 32);
#elif PLATFORM == 1024
            for (; i + 32 <= end; i += 32)
                ADD_I16_SVE(a + i, b + i, c + i, 32);
#elif PLATFORM == 64
            for (; i + 8 <= end; i += 8)
                ADD_I16x8_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
            for (; i + 8 <= end; i += 8)
                ADD_I16x8_ARMv7(a + i, b + i, c + i);
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] + b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Add_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 32 <= n; i += 32)
        ADD_I16x32_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 16 <= n; i += 16)
        ADD_I16x16_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 8 <= n; i += 8)
        ADD_I16x8_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 32 <= n; i += 32)
        ADD_I16_SVE2(a + i, b + i, c + i, 32);
#elif PLATFORM == 1024
    for (; i + 32 <= n; i += 32)
        ADD_I16_SVE(a + i, b + i, c + i, 32);
#elif PLATFORM == 64
    for (; i + 8 <= n; i += 8)
        ADD_I16x8_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 8 <= n; i += 8)
        ADD_I16x8_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
}

inline void __openblao_Sub_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 32 <= end; i += 32)
                SUB_I16x32_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 16 <= end; i += 16)
                SUB_I16x16_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 8 <= end; i += 8)
                SUB_I16x8_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
            for (; i + 32 <= end; i += 32)
                SUB_I16_SVE2(a + i, b + i, c + i, 32);
#elif PLATFORM == 1024
            for (; i + 32 <= end; i += 32)
                SUB_I16_SVE(a + i, b + i, c + i, 32);
#elif PLATFORM == 64
            for (; i + 8 <= end; i += 8)
                SUB_I16x8_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
            for (; i + 8 <= end; i += 8)
                SUB_I16x8_ARMv7(a + i, b + i, c + i);
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] - b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Sub_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 32 <= n; i += 32)
        SUB_I16x32_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 16 <= n; i += 16)
        SUB_I16x16_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 8 <= n; i += 8)
        SUB_I16x8_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 32 <= n; i += 32)
        SUB_I16_SVE2(a + i, b + i, c + i, 32);
#elif PLATFORM == 1024
    for (; i + 32 <= n; i += 32)
        SUB_I16_SVE(a + i, b + i, c + i, 32);
#elif PLATFORM == 64
    for (; i + 8 <= n; i += 8)
        SUB_I16x8_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 8 <= n; i += 8)
        SUB_I16x8_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] - b[i];
    }
}

inline void __openblao_Mul_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
            for (; i + 32 <= end; i += 32)
                MUL_I16x32_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
            for (; i + 16 <= end; i += 16)
                MUL_I16x16_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
            for (; i + 8 <= end; i += 8)
                MUL_I16x8_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
            for (; i + 32 <= end; i += 32)
                MUL_I16_SVE2(a + i, b + i, c + i, 32);
#elif PLATFORM == 1024
            for (; i + 32 <= end; i += 32)
                MUL_I16_SVE(a + i, b + i, c + i, 32);
#elif PLATFORM == 64
            for (; i + 8 <= end; i += 8)
                MUL_I16x8_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
            for (; i + 8 <= end; i += 8)
                MUL_I16x8_ARMv7(a + i, b + i, c + i);
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] * b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Mul_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 32 <= n; i += 32)
        MUL_I16x32_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 16 <= n; i += 16)
        MUL_I16x16_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 8 <= n; i += 8)
        MUL_I16x8_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 32 <= n; i += 32)
        MUL_I16_SVE2(a + i, b + i, c + i, 32);
#elif PLATFORM == 1024
    for (; i + 32 <= n; i += 32)
        MUL_I16_SVE(a + i, b + i, c + i, 32);
#elif PLATFORM == 64
    for (; i + 8 <= n; i += 8)
        MUL_I16x8_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 8 <= n; i += 8)
        MUL_I16x8_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] * b[i];
    }
}

inline void __openblao_Div_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

            #if ARCT == 8664
            for (; i + 8 <= end; i += 8)
                    DIV_I16x8_x86_64(a + i, b + i, c + i);
            #elif ARCT == 8633
            for (; i + 8 <= end; i += 8)
                    DIV_I16x8_Ax86_32(a + i, b + i, c + i);
            #elif ARCT == 6464
            for (; i + 8 <= end; i += 8)
                    DIV_I16x8_ARM(a + i, b + i, c + i);
            #elif ARCT == 6432
            for (; i + 8 <= end; i += 8)
                    DIV_I16x8_ARMv7(a + i, b + i, c + i);
            #endif

            for (; i < end; ++i)
            {
                c[i] = a[i] / b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Div_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n)
{
    size_t i = 0;

            #if ARCT == 8664
            for (; i + 8 <= n; i += 8)
                    DIV_I16x8_x86_64(a + i, b + i, c + i);
            #elif ARCT == 8633
            for (; i + 8 <= n; i += 8)
                    DIV_I16x8_Ax86_32(a + i, b + i, c + i);
            #elif ARCT == 6464
            for (; i + 8 <= n; i += 8)
                    DIV_I16x8_ARM(a + i, b + i, c + i);
            #elif ARCT == 6432
            for (; i + 8 <= n; i += 8)
                    DIV_I16x8_ARMv7(a + i, b + i, c + i);
            #endif

    for (; i < n; ++i)
    {
        c[i] = a[i] / b[i];
    }
}

inline void __openblao_Add_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
    for (; i + 64 <= end; i += 64)
        ADD_I8x64_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 32 <= end; i += 32)
        ADD_I8x32_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 16 <= end; i += 16)
        ADD_I8x16_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 128 <= end; i += 128)
        ADD_I8_SVE2(a + i, b + i, c + i, 128);
#elif PLATFORM == 1024
    for (; i + 128 <= end; i += 128)
        ADD_I8_SVE(a + i, b + i, c + i, 128);
#elif PLATFORM == 64
    for (; i + 16 <= end; i += 16)
        ADD_I8x16_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 16 <= end; i += 16)
        ADD_I8x16_ARMv7(a + i, b + i, c + i);
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] + b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Add_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 64 <= n; i += 64)
        ADD_I8x64_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 32 <= n; i += 32)
        ADD_I8x32_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 16 <= n; i += 16)
        ADD_I8x16_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 128 <= n; i += 128)
        ADD_I8_SVE2(a + i, b + i, c + i, 128);
#elif PLATFORM == 1024
    for (; i + 128 <= n; i += 128)
        ADD_I8_SVE(a + i, b + i, c + i, 128);
#elif PLATFORM == 64
    for (; i + 16 <= n; i += 16)
        ADD_I8x16_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 16 <= n; i += 16)
        ADD_I8x16_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] + b[i];
    }
}

inline void __openblao_Sub_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
    for (; i + 64 <= end; i += 64)
        SUB_I8x64_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 32 <= end; i += 32)
        SUB_I8x32_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 16 <= end; i += 16)
        SUB_I8x16_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 128 <= end; i += 128)
        SUB_I8_SVE2(a + i, b + i, c + i, 128);
#elif PLATFORM == 1024
    for (; i + 128 <= end; i += 128)
        SUB_I8_SVE(a + i, b + i, c + i, 128);
#elif PLATFORM == 64
    for (; i + 16 <= end; i += 16)
        SUB_I8x16_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 16 <= end; i += 16)
        SUB_I8x16_ARMv7(a + i, b + i, c + i);
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] - b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Sub_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 64 <= n; i += 64)
        SUB_I8x64_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 32 <= n; i += 32)
        SUB_I8x32_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 16 <= n; i += 16)
        SUB_I8x16_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 128 <= n; i += 128)
        SUB_I8_SVE2(a + i, b + i, c + i, 128);
#elif PLATFORM == 1024
    for (; i + 128 <= n; i += 128)
        SUB_I8_SVE(a + i, b + i, c + i, 128);
#elif PLATFORM == 64
    for (; i + 16 <= n; i += 16)
        SUB_I8x16_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 16 <= n; i += 16)
        SUB_I8x16_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] - b[i];
    }
}

inline void __openblao_Mul_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

#if PLATFORM == 512
    for (; i + 64 <= end; i += 64)
        MUL_I8x64_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 32 <= end; i += 32)
        MUL_I8x32_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 16 <= end; i += 16)
        MUL_I8x16_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 128 <= end; i += 128)
        MUL_I8_SVE2(a + i, b + i, c + i, 128);
#elif PLATFORM == 1024
    for (; i + 128 <= end; i += 128)
        MUL_I8_SVE(a + i, b + i, c + i, 128);
#elif PLATFORM == 64
    for (; i + 16 <= end; i += 16)
        MUL_I8x16_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 16 <= end; i += 16)
        MUL_I8x16_ARMv7(a + i, b + i, c + i);
#endif

            for (; i < end; ++i)
            {
                c[i] = a[i] * b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Mul_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n)
{
    size_t i = 0;

#if PLATFORM == 512
    for (; i + 64 <= n; i += 64)
        MUL_I8x64_A512(a + i, b + i, c + i);
#elif PLATFORM == 256
    for (; i + 32 <= n; i += 32)
        MUL_I8x32_AVX2(a + i, b + i, c + i);
#elif PLATFORM == 128
    for (; i + 16 <= n; i += 16)
        MUL_I8x16_SSE2(a + i, b + i, c + i);
#elif PLATFORM == 2048
    for (; i + 128 <= n; i += 128)
        MUL_I8_SVE2(a + i, b + i, c + i, 128);
#elif PLATFORM == 1024
    for (; i + 128 <= n; i += 128)
        MUL_I8_SVE(a + i, b + i, c + i, 128);
#elif PLATFORM == 64
    for (; i + 16 <= n; i += 16)
        MUL_I8x16_ARM(a + i, b + i, c + i);
#elif PLATFORM == 32
    for (; i + 16 <= n; i += 16)
        MUL_I8x16_ARMv7(a + i, b + i, c + i);
#endif

    for (; i < n; ++i)
    {
        c[i] = a[i] * b[i];
    }
}

inline void __openblao_Div_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n, const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            size_t i = start;

            #if ARCT == 8664
            for (; i + 8 <= end; i += 8)
                    DIV_I8x16_x86_64(a + i, b + i, c + i);
            #elif ARCT == 8633
            for (; i + 16 <= end; i += 16)
                    DIV_I8x16_Ax86_32(a + i, b + i, c + i);
            #elif ARCT == 6464
            for (; i + 16 <= end; i += 16)
                    DIV_I8x16_ARM(a + i, b + i, c + i);
            #elif ARCT == 6432
            for (; i + 16 <= end; i += 16)
                    DIV_I8x16_ARMv7(a + i, b + i, c + i);
            #endif

            for (; i < end; ++i)
            {
                c[i] = a[i] / b[i];
            }
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_Div_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n)
{
    size_t i = 0;

            #if ARCT == 8664
            for (; i + 8 <= n; i += 8)
                    DIV_I8x16_x86_64(a + i, b + i, c + i);
            #elif ARCT == 8633
            for (; i + 16 <= n; i += 16)
                    DIV_I8x16_Ax86_32(a + i, b + i, c + i);
            #elif ARCT == 6464
            for (; i + 16 <= n; i += 16)
                    DIV_I8x16_ARM(a + i, b + i, c + i);
            #elif ARCT == 6432
            for (; i + 16 <= n; i += 16)
                    DIV_I8x16_ARMv7(a + i, b + i, c + i);
            #endif

    for (; i < n; ++i)
    {
        c[i] = a[i] / b[i];
    }
}

inline void __openblao_BroadcastAdd_float64(const double *a, const double *b, double *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    ADD_F64_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    ADD_F64_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 8 <= end; i += 8) {
    ADD_F64x8_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 256
for (; i + 4 <= end; i += 4) {
    ADD_F64x4_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 128
for (; i + 4 <= end; i += 4) {
    ADD_F64x2_SSE2(a + a_idx,     b + b_idx,     c + i);
    ADD_F64x2_SSE2(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 64
for (; i + 4 <= end; i += 4) {
    ADD_F64x2_ARM(a + a_idx,     b + b_idx,     c + i);
    ADD_F64x2_ARM(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastAdd_float64(const double *a, const double *b, double *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    ADD_F64_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    ADD_F64_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 8 <= n_c; i += 8) {
    ADD_F64x8_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 256
for (; i + 4 <= n_c; i += 4) {
    ADD_F64x4_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 128
for (; i + 4 <= n_c; i += 4) {
    ADD_F64x2_SSE2(a + a_idx,     b + b_idx,     c + i);
    ADD_F64x2_SSE2(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 64
for (; i + 4 <= n_c; i += 4) {
    ADD_F64x2_ARM(a + a_idx,     b + b_idx,     c + i);
    ADD_F64x2_ARM(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastSub_float64(const double *a, const double *b, double *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    SUB_F64_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    SUB_F64_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 8 <= end; i += 8) {
    SUB_F64x8_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 256
for (; i + 4 <= end; i += 4) {
    SUB_F64x4_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 128
for (; i + 4 <= end; i += 4) {
    SUB_F64x2_SSE2(a + a_idx,     b + b_idx,     c + i);
    SUB_F64x2_SSE2(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 64
for (; i + 4 <= end; i += 4) {
    SUB_F64x2_ARM(a + a_idx,     b + b_idx,     c + i);
    SUB_F64x2_ARM(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastSub_float64(const double *a, const double *b, double *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    SUB_F64_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    SUB_F64_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 8 <= n_c; i += 8) {
    SUB_F64x8_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 256
for (; i + 4 <= n_c; i += 4) {
    SUB_F64x4_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 128
for (; i + 4 <= n_c; i += 4) {
    SUB_F64x2_SSE2(a + a_idx,     b + b_idx,     c + i);
    SUB_F64x2_SSE2(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 64
for (; i + 4 <= n_c; i += 4) {
    SUB_F64x2_ARM(a + a_idx,     b + b_idx,     c + i);
    SUB_F64x2_ARM(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastMul_float64(const double *a, const double *b, double *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    MUL_F64_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    MUL_F64_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 8 <= end; i += 8) {
    MUL_F64x8_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 256
for (; i + 4 <= end; i += 4) {
    MUL_F64x4_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 128
for (; i + 4 <= end; i += 4) {
    MUL_F64x2_SSE2(a + a_idx,     b + b_idx,     c + i);
    MUL_F64x2_SSE2(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 64
for (; i + 4 <= end; i += 4) {
    MUL_F64x2_ARM(a + a_idx,     b + b_idx,     c + i);
    MUL_F64x2_ARM(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastMul_float64(const double *a, const double *b, double *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    MUL_F64_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    MUL_F64_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 8 <= n_c; i += 8) {
    MUL_F64x8_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 256
for (; i + 4 <= n_c; i += 4) {
    MUL_F64x4_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 128
for (; i + 4 <= n_c; i += 4) {
    MUL_F64x2_SSE2(a + a_idx,     b + b_idx,     c + i);
    MUL_F64x2_SSE2(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 64
for (; i + 4 <= n_c; i += 4) {
    MUL_F64x2_ARM(a + a_idx,     b + b_idx,     c + i);
    MUL_F64x2_ARM(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastDiv_float64(const double *a, const double *b, double *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    DIV_F64_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    DIV_F64_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 8 <= end; i += 8) {
    DIV_F64x8_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 256
for (; i + 4 <= end; i += 4) {
    DIV_F64x4_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 128
for (; i + 4 <= end; i += 4) {
    DIV_F64x2_SSE2(a + a_idx,     b + b_idx,     c + i);
    DIV_F64x2_SSE2(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 64
for (; i + 4 <= end; i += 4) {
    DIV_F64x2_ARM(a + a_idx,     b + b_idx,     c + i);
    DIV_F64x2_ARM(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastDiv_float64(const double *a, const double *b, double *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    DIV_F64_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    DIV_F64_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 8 <= n_c; i += 8) {
    DIV_F64x8_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 256
for (; i + 4 <= n_c; i += 4) {
    DIV_F64x4_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 128
for (; i + 4 <= n_c; i += 4) {
    DIV_F64x2_SSE2(a + a_idx,     b + b_idx,     c + i);
    DIV_F64x2_SSE2(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}

#elif PLATFORM == 64
for (; i + 4 <= n_c; i += 4) {
    DIV_F64x2_ARM(a + a_idx,     b + b_idx,     c + i);
    DIV_F64x2_ARM(a + a_idx + 2, b + b_idx + 2, c + i + 2);

    a_idx = (a_idx + 4 < n_a ? a_idx + 4 : (a_idx + 4) % n_a);
    b_idx = (b_idx + 4 < n_b ? b_idx + 4 : (b_idx + 4) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}



inline void __openblao_BroadcastAdd_float32(const float *a, const float *b, float *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    ADD_F32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    ADD_F32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    ADD_F32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= end; i += 8) {
    ADD_F32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= end; i += 8) {
    ADD_F32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    ADD_F32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= end; i += 8) {
    ADD_F32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    ADD_F32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#elif PLATFORM == 32
for (; i + 8 <= end; i += 8) {
    ADD_F32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    ADD_F32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastAdd_float32(const float *a, const float *b, float *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    ADD_F32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    ADD_F32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    ADD_F32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= n_c; i += 8) {
    ADD_F32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= n_c; i += 8) {
    ADD_F32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    ADD_F32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= n_c; i += 8) {
    ADD_F32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    ADD_F32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#elif PLATFORM == 32
for (; i + 8 <= n_c; i += 8) {
    ADD_F32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    ADD_F32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastSub_float32(const float *a, const float *b, float *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    SUB_F32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    SUB_F32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    SUB_F32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= end; i += 8) {
    SUB_F32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= end; i += 8) {
    SUB_F32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    SUB_F32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= end; i += 8) {
    SUB_F32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    SUB_F32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#elif PLATFORM == 32
for (; i + 8 <= end; i += 8) {
    SUB_F32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    SUB_F32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastSub_float32(const float *a, const float *b, float *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    SUB_F32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    SUB_F32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    SUB_F32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= n_c; i += 8) {
    SUB_F32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= n_c; i += 8) {
    SUB_F32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    SUB_F32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= n_c; i += 8) {
    SUB_F32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    SUB_F32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#elif PLATFORM == 32
for (; i + 8 <= n_c; i += 8) {
    SUB_F32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    SUB_F32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastMul_float32(const float *a, const float *b, float *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    MUL_F32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    MUL_F32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    MUL_F32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= end; i += 8) {
    MUL_F32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= end; i += 8) {
    MUL_F32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    MUL_F32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= end; i += 8) {
    MUL_F32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    MUL_F32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#elif PLATFORM == 32
for (; i + 8 <= end; i += 8) {
    MUL_F32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    MUL_F32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastMul_float32(const float *a, const float *b, float *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    MUL_F32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    MUL_F32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    MUL_F32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= n_c; i += 8) {
    MUL_F32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= n_c; i += 8) {
    MUL_F32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    MUL_F32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= n_c; i += 8) {
    MUL_F32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    MUL_F32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#elif PLATFORM == 32
for (; i + 8 <= n_c; i += 8) {
    MUL_F32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    MUL_F32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastDiv_float32(const float *a, const float *b, float *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    DIV_F32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    DIV_F32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    DIV_F32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= end; i += 8) {
    DIV_F32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= end; i += 8) {
    DIV_F32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    DIV_F32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= end; i += 8) {
    DIV_F32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    DIV_F32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#elif PLATFORM == 32
for (; i + 8 <= end; i += 8) {
    DIV_F32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    DIV_F32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastDiv_float32(const float *a, const float *b, float *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    DIV_F32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    DIV_F32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    DIV_F32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= n_c; i += 8) {
    DIV_F32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= n_c; i += 8) {
    DIV_F32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    DIV_F32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= n_c; i += 8) {
    DIV_F32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    DIV_F32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#elif PLATFORM == 32
for (; i + 8 <= n_c; i += 8) {
    DIV_F32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    DIV_F32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastAdd_int32(const int32_t *a, const int32_t *b, int32_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    ADD_I32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    ADD_I32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    ADD_I32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= end; i += 8) {
    ADD_I32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= end; i += 8) {
    ADD_I32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    ADD_I32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= end; i += 8) {
    ADD_I32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    ADD_I32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 32
for (; i + 8 <= end; i += 8) {
    ADD_I32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    ADD_I32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastAdd_int32(const int32_t *a, const int32_t *b, int32_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    ADD_I32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    ADD_I32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    ADD_I32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= n_c; i += 8) {
    ADD_I32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= n_c; i += 8) {
    ADD_I32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    ADD_I32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= n_c; i += 8) {
    ADD_I32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    ADD_I32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 32
for (; i + 8 <= n_c; i += 8) {
    ADD_I32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    ADD_I32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastSub_int32(const int32_t *a, const int32_t *b, int32_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    SUB_I32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    SUB_I32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    SUB_I32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= end; i += 8) {
    SUB_I32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= end; i += 8) {
    SUB_I32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    SUB_I32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= end; i += 8) {
    SUB_I32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    SUB_I32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 32
for (; i + 8 <= end; i += 8) {
    SUB_I32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    SUB_I32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastSub_int32(const int32_t *a, const int32_t *b, int32_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    SUB_I32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    SUB_I32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    SUB_I32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= n_c; i += 8) {
    SUB_I32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= n_c; i += 8) {
    SUB_I32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    SUB_I32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= n_c; i += 8) {
    SUB_I32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    SUB_I32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 32
for (; i + 8 <= n_c; i += 8) {
    SUB_I32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    SUB_I32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastMul_int32(const int32_t *a, const int32_t *b, int32_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    MUL_I32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    MUL_I32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    MUL_I32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= end; i += 8) {
    MUL_I32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= end; i += 8) {
    MUL_I32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    MUL_I32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= end; i += 8) {
    MUL_I32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    MUL_I32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 32
for (; i + 8 <= end; i += 8) {
    MUL_I32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    MUL_I32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastMul_int32(const int32_t *a, const int32_t *b, int32_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    MUL_I32_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    MUL_I32_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    MUL_I32x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 8 <= n_c; i += 8) {
    MUL_I32x8_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 128
for (; i + 8 <= n_c; i += 8) {
    MUL_I32x4_SSE2(a + a_idx,     b + b_idx,     c + i);
    MUL_I32x4_SSE2(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 64
for (; i + 8 <= n_c; i += 8) {
    MUL_I32x4_ARM(a + a_idx,     b + b_idx,     c + i);
    MUL_I32x4_ARM(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif PLATFORM == 32
for (; i + 8 <= n_c; i += 8) {
    MUL_I32x4_ARMv7(a + a_idx,     b + b_idx,     c + i);
    MUL_I32x4_ARMv7(a + a_idx + 4, b + b_idx + 4, c + i + 4);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastDiv_int32(const int32_t *a, const int32_t *b, int32_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if ARCT == 8664
for (; i + 8 <= end; i += 8) {
    DIV_I32x8_x86_64(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 8633
for (; i + 8 <= end; i += 8) {
    DIV_I32x8_Ax86_32(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 6464
for (; i + 8 <= end; i += 8) {
    DIV_I32x8_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 6432
for (; i + 8 <= end; i += 8) {
    DIV_I32x8_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastDiv_int32(const int32_t *a, const int32_t *b, int32_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if ARCT == 8664
for (; i + 8 <= n_c; i += 8) {
    DIV_I32x8_x86_64(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 8633
for (; i + 8 <= n_c; i += 8) {
    DIV_I32x8_Ax86_32(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 6464
for (; i + 8 <= n_c; i += 8) {
    DIV_I32x8_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 6432
for (; i + 8 <= n_c; i += 8) {
    DIV_I32x8_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastAdd_int16(const int16_t *a, const int16_t *b, int16_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    ADD_I16_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    ADD_I16_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    ADD_I16x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= end; i += 16) {
    ADD_I16x8_AVX2(a + a_idx,     b + b_idx,     c + i);
    ADD_I16x8_AVX2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= end; i += 16) {
    ADD_I16x8_SSE2(a + a_idx,     b + b_idx,     c + i);
    ADD_I16x8_SSE2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= end; i += 16) {
    ADD_I16x8_ARM(a + a_idx,     b + b_idx,     c + i);
    ADD_I16x8_ARM(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= end; i += 16) {
    ADD_I16x8_ARMv7(a + a_idx,     b + b_idx,     c + i);
    ADD_I16x8_ARMv7(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastAdd_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    ADD_I16_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    ADD_I16_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    ADD_I16x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= n_c; i += 16) {
    ADD_I16x8_AVX2(a + a_idx,     b + b_idx,     c + i);
    ADD_I16x8_AVX2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= n_c; i += 16) {
    ADD_I16x8_SSE2(a + a_idx,     b + b_idx,     c + i);
    ADD_I16x8_SSE2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= n_c; i += 16) {
    ADD_I16x8_ARM(a + a_idx,     b + b_idx,     c + i);
    ADD_I16x8_ARM(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= n_c; i += 16) {
    ADD_I16x8_ARMv7(a + a_idx,     b + b_idx,     c + i);
    ADD_I16x8_ARMv7(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastSub_int16(const int16_t *a, const int16_t *b, int16_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    SUB_I16_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    SUB_I16_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    SUB_I16x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= end; i += 16) {
    SUB_I16x8_AVX2(a + a_idx,     b + b_idx,     c + i);
    SUB_I16x8_AVX2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= end; i += 16) {
    SUB_I16x8_SSE2(a + a_idx,     b + b_idx,     c + i);
    SUB_I16x8_SSE2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= end; i += 16) {
    SUB_I16x8_ARM(a + a_idx,     b + b_idx,     c + i);
    SUB_I16x8_ARM(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= end; i += 16) {
    SUB_I16x8_ARMv7(a + a_idx,     b + b_idx,     c + i);
    SUB_I16x8_ARMv7(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastSub_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    SUB_I16_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    SUB_I16_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    SUB_I16x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= n_c; i += 16) {
    SUB_I16x8_AVX2(a + a_idx,     b + b_idx,     c + i);
    SUB_I16x8_AVX2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= n_c; i += 16) {
    SUB_I16x8_SSE2(a + a_idx,     b + b_idx,     c + i);
    SUB_I16x8_SSE2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= n_c; i += 16) {
    SUB_I16x8_ARM(a + a_idx,     b + b_idx,     c + i);
    SUB_I16x8_ARM(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= n_c; i += 16) {
    SUB_I16x8_ARMv7(a + a_idx,     b + b_idx,     c + i);
    SUB_I16x8_ARMv7(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}
inline void __openblao_BroadcastMul_int16(const int16_t *a, const int16_t *b, int16_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    MUL_I16_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    MUL_I16_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    MUL_I16x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= end; i += 16) {
    MUL_I16x8_AVX2(a + a_idx,     b + b_idx,     c + i);
    MUL_I16x8_AVX2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= end; i += 16) {
    MUL_I16x8_SSE2(a + a_idx,     b + b_idx,     c + i);
    MUL_I16x8_SSE2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= end; i += 16) {
    MUL_I16x8_ARM(a + a_idx,     b + b_idx,     c + i);
    MUL_I16x8_ARM(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= end; i += 16) {
    MUL_I16x8_ARMv7(a + a_idx,     b + b_idx,     c + i);
    MUL_I16x8_ARMv7(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastMul_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    MUL_I16_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    MUL_I16_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    MUL_I16x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= n_c; i += 16) {
    MUL_I16x8_AVX2(a + a_idx,     b + b_idx,     c + i);
    MUL_I16x8_AVX2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= n_c; i += 16) {
    MUL_I16x8_SSE2(a + a_idx,     b + b_idx,     c + i);
    MUL_I16x8_SSE2(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= n_c; i += 16) {
    MUL_I16x8_ARM(a + a_idx,     b + b_idx,     c + i);
    MUL_I16x8_ARM(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= n_c; i += 16) {
    MUL_I16x8_ARMv7(a + a_idx,     b + b_idx,     c + i);
    MUL_I16x8_ARMv7(a + a_idx + 8, b + b_idx + 8, c + i + 8);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastDiv_int16(const int16_t *a, const int16_t *b, int16_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if ARCT == 8664
for (; i + 8 <= n_c; i += 8) {
    DIV_I16x8_X86_64(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 8633
for (; i + 8 <= n_c; i += 8) {
    DIV_I16x8_X86_32(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 6464
for (; i + 8 <= n_c; i += 8) {
    DIV_I16x8_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 6432
for (; i + 8 <= n_c; i += 8) {
    DIV_I16x8_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastDiv_int16(const int16_t *a, const int16_t *b, int16_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if ARCT == 8664
for (; i + 8 <= n_c; i += 8) {
    DIV_I16x8_X86_64(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 8633
for (; i + 8 <= n_c; i += 8) {
    DIV_I16x8_X86_32(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 6464
for (; i + 8 <= n_c; i += 8) {
    DIV_I16x8_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}

#elif ARCT == 6432
for (; i + 8 <= n_c; i += 8) {
    DIV_I16x8_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 8 < n_a ? a_idx + 8 : (a_idx + 8) % n_a);
    b_idx = (b_idx + 8 < n_b ? b_idx + 8 : (b_idx + 8) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastAdd_int8(const int8_t *a, const int8_t *b, int8_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    ADD_I8_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    ADD_I8_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    ADD_I8x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= end; i += 16) {
    ADD_I8x16_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= end; i += 16) {
    ADD_I8x16_SSE2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= end; i += 16) {
    ADD_I8x16_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= end; i += 16) {
    ADD_I8x16_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastAdd_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    ADD_I8_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    ADD_I8_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    ADD_I8x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= n_c; i += 16) {
    ADD_I8x16_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= n_c; i += 16) {
    ADD_I8x16_SSE2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= n_c; i += 16) {
    ADD_I8x16_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= n_c; i += 16) {
    ADD_I8x16_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] + b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastSub_int8(const int8_t *a, const int8_t *b, int8_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    SUB_I8_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    SUB_I8_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    SUB_I8x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= end; i += 16) {
    SUB_I8x16_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= end; i += 16) {
    SUB_I8x16_SSE2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= end; i += 16) {
    SUB_I8x16_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= end; i += 16) {
    SUB_I8x16_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastSub_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    SUB_I8_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    SUB_I8_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    SUB_I8x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= n_c; i += 16) {
    SUB_I8x16_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= n_c; i += 16) {
    SUB_I8x16_SSE2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= n_c; i += 16) {
    SUB_I8x16_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= n_c; i += 16) {
    SUB_I8x16_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] - b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastMul_int8(const int8_t *a, const int8_t *b, int8_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= end; i += 16) {
    MUL_I8_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= end; i += 16) {
    MUL_I8_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= end; i += 16) {
    MUL_I8x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= end; i += 16) {
    MUL_I8x16_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= end; i += 16) {
    MUL_I8x16_SSE2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= end; i += 16) {
    MUL_I8x16_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= end; i += 16) {
    MUL_I8x16_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastMul_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if PLATFORM == 2048
for (; i + 16 <= n_c; i += 16) {
    MUL_I8_SVE2(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 1024
for (; i + 16 <= n_c; i += 16) {
    MUL_I8_SVE(a + a_idx, b + b_idx, c + i, 16);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 512
for (; i + 16 <= n_c; i += 16) {
    MUL_I8x16_A512(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 256
for (; i + 16 <= n_c; i += 16) {
    MUL_I8x16_AVX2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 128
for (; i + 16 <= n_c; i += 16) {
    MUL_I8x16_SSE2(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 64
for (; i + 16 <= n_c; i += 16) {
    MUL_I8x16_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif PLATFORM == 32
for (; i + 16 <= n_c; i += 16) {
    MUL_I8x16_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] * b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}

inline void __openblao_BroadcastDiv_int8(const int8_t *a, const int8_t *b, int8_t *c,
                                   const size_t n_a, const size_t n_b, const size_t n_c,
                                   const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n_c + real_threads - 1) / real_threads;
    std::thread *threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n_c) {
            real_threads = t;
            break;
        }

        size_t end = start + chunk;
        if (end > n_c) end = n_c;

        threads[t] = std::thread([=]() {

            size_t i = start;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if ARCT == 8664
for (; i + 16 <= end; i += 16) {
    DIV_I8x16_X86_64(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif ARCT == 8633
for (; i + 16 <= end; i += 16) {
    DIV_I8x16_X86_32(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif ARCT == 6464
for (; i + 16 <= end; i += 16) {
    DIV_I8x16_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif ARCT == 6432
for (; i + 16 <= end; i += 16) {
    DIV_I8x16_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < end; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}

        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

inline void __openblao_BroadcastDiv_int8(const int8_t *a, const int8_t *b, int8_t *c, const size_t n_a, const size_t n_b, const size_t n_c)
{
    size_t i = 0;

size_t a_idx = (i < n_a ? i : i % n_a);
size_t b_idx = (i < n_b ? i : i % n_b);

#if ARCT == 8664
for (; i + 16 <= n_c; i += 16) {
    DIV_I8x16_X86_64(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif ARCT == 8633
for (; i + 16 <= n_c; i += 16) {
    DIV_I8x16_X86_32(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif ARCT == 6464
for (; i + 16 <= n_c; i += 16) {
    DIV_I8x16_ARM(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}

#elif ARCT == 6432
for (; i + 16 <= n_c; i += 16) {
    DIV_I8x16_ARMv7(a + a_idx, b + b_idx, c + i);

    a_idx = (a_idx + 16 < n_a ? a_idx + 16 : (a_idx + 16) % n_a);
    b_idx = (b_idx + 16 < n_b ? b_idx + 16 : (b_idx + 16) % n_b);
}
#endif

for (; i < n_c; ++i) {
    c[i] = a[a_idx] / b[b_idx];
    a_idx = (a_idx + 1 < n_a ? a_idx + 1 : 0);
    b_idx = (b_idx + 1 < n_b ? b_idx + 1 : 0);
}


}


/*__COPYING__*/
template<typename T>
inline void __openblao_copy(
const T* __restrict a, 
T* __restrict b, 
const size_t n, 
const size_t thread_use)
{
    size_t real_threads = thread_use;
    size_t chunk = (n + real_threads - 1) / real_threads;
    std::thread* threads = new std::thread[real_threads];

    for (size_t t = 0; t < real_threads; ++t)
    {
        size_t start = t * chunk;
        if (start >= n)
        {
            real_threads = t;
            break;
        }
        size_t end = start + chunk;
        if (end > n)
            end = n;

        threads[t] = std::thread([=]() {
            std::memcpy(b + start, a + start, (end - start) * sizeof(T));
        });
    }

    for (size_t t = 0; t < real_threads; ++t)
        threads[t].join();

    delete[] threads;
}

template<typename T>
inline void __openblao_copy(
const T* __restrict a, 
T* __restrict b, 
const size_t N) { std::memcpy(b, a, N * sizeof(T)); }



 template<typename T>
 inline void __openblao_fills(T *data,
                                   const T value,
                                   const size_t total,
                                   const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_fills_float32(data, value, total, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_fills_float64(data, value, total, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_fills_int32(data, value, total, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_fills_int16(data, value, total, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_fills_int8(data, value, total, thread_use);
}

 template<typename T>
 inline void __openblao_fills(T *data,
                                   const T value,
                                   const size_t total) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_fills_float32(data, value, total);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_fills_float64(data, value, total);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_fills_int32(data, value, total);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_fills_int16(data, value, total);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_fills_int8(data, value, total);
}

 template<typename T>
 inline void __openblao_Add(const T* a, const T* b, T* c,
                                   const size_t total,
                                   const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_Add_float32(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_Add_float64(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_Add_int32(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_Add_int16(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_Add_int8(a, b, c, total, thread_use);
}

 template<typename T>
 inline void __openblao_Add(const T* a, const T* b, T* c,
                                   const size_t total) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_Add_float32(a, b, c, total);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_Add_float64(a, b, c, total);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_Add_int32(a, b, c, total);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_Add_int16(a, b, c, total);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_Add_int8(a, b, c, total);
}

 template<typename T>
 inline void __openblao_Sub(const T* a, const T* b, T* c,
                                   const size_t total,
                                   const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_Sub_float32(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_Sub_float64(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_Sub_int32(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_Sub_int16(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_Sub_int8(a, b, c, total, thread_use);
}

 template<typename T>
 inline void __openblao_Sub(const T* a, const T* b, T* c,
                                   const size_t total) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_Sub_float32(a, b, c, total);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_Sub_float64(a, b, c, total);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_Sub_int32(a, b, c, total);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_Sub_int16(a, b, c, total);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_Sub_int8(a, b, c, total);
}

 template<typename T>
 inline void __openblao_Mul(const T* a, const T* b, T* c,
                                   const size_t total,
                                   const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_Mul_float32(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_Mul_float64(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_Mul_int32(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_Mul_int16(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_Mul_int8(a, b, c, total, thread_use);
}

 template<typename T>
 inline void __openblao_Mul(const T* a, const T* b, T* c,
                                   const size_t total) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_Mul_float32(a, b, c, total);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_Mul_float64(a, b, c, total);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_Mul_int32(a, b, c, total);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_Mul_int16(a, b, c, total);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_Mul_int8(a, b, c, total);
}

 template<typename T>
 inline void __openblao_Div(const T* a, const T* b, T* c,
                                   const size_t total,
                                   const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_Div_float32(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_Div_float64(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_Div_int32(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_Div_int16(a, b, c, total, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_Div_int8(a, b, c, total, thread_use);
}

 template<typename T>
 inline void __openblao_Div(const T* a, const T* b, T* c,
                                   const size_t total) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_Div_float32(a, b, c, total);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_Div_float64(a, b, c, total);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_Div_int32(a, b, c, total);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_Div_int16(a, b, c, total);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_Div_int8(a, b, c, total);
}

 template<typename T>
 inline void __openblao_BroadcastAdd(const T* a, const T* b, T* c, const size_t n_a, const size_t n_b, const size_t n_c, const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_BroadcastAdd_float32(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_BroadcastAdd_float64(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_BroadcastAdd_int32(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_BroadcastAdd_int16(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_BroadcastAdd_int8(a, b, c, n_a, n_b, n_c, thread_use);
}

 template<typename T>
 inline void __openblao_BroadcastAdd(const T* a, const T* b, T* c,const size_t n_a, const size_t n_b, const size_t n_c) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_BroadcastAdd_float32(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_BroadcastAdd_float64(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_BroadcastAdd_int32(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_BroadcastAdd_int16(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_BroadcastAdd_int8(a, b, c, n_a, n_b, n_c);
}

 template<typename T>
 inline void __openblao_BroadcastSub(const T* a, const T* b, T* c, const size_t n_a, const size_t n_b, const size_t n_c, const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_BroadcastSub_float32(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_BroadcastSub_float64(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_BroadcastSub_int32(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_BroadcastSub_int16(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_BroadcastSub_int8(a, b, c, n_a, n_b, n_c, thread_use);
}

 template<typename T>
 inline void __openblao_BroadcastSub(const T* a, const T* b, T* c,const size_t n_a, const size_t n_b, const size_t n_c) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_BroadcastSub_float32(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_BroadcastSub_float64(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_BroadcastSub_int32(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_BroadcastSub_int16(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_BroadcastSub_int8(a, b, c, n_a, n_b, n_c);
}

 template<typename T>
 inline void __openblao_BroadcastMul(const T* a, const T* b, T* c, const size_t n_a, const size_t n_b, const size_t n_c, const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_BroadcastMul_float32(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_BroadcastMul_float64(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_BroadcastMul_int32(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_BroadcastMul_int16(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_BroadcastMul_int8(a, b, c, n_a, n_b, n_c, thread_use);
}

 template<typename T>
 inline void __openblao_BroadcastMul(const T* a, const T* b, T* c,const size_t n_a, const size_t n_b, const size_t n_c) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_BroadcastMul_float32(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_BroadcastMul_float64(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_BroadcastMul_int32(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_BroadcastMul_int16(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_BroadcastMul_int8(a, b, c, n_a, n_b, n_c);
}

 template<typename T>
 inline void __openblao_BroadcastDiv(const T* a, const T* b, T* c, const size_t n_a, const size_t n_b, const size_t n_c, const size_t thread_use) {
    
    if constexpr (std::is_same_v<T, float>)
                __openblao_BroadcastDiv_float32(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_BroadcastDiv_float64(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_BroadcastDiv_int32(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_BroadcastDiv_int16(a, b, c, n_a, n_b, n_c, thread_use);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_BroadcastDiv_int8(a, b, c, n_a, n_b, n_c, thread_use);
}

 template<typename T>
 inline void __openblao_BroadcastDiv(const T* a, const T* b, T* c,const size_t n_a, const size_t n_b, const size_t n_c) {
    if constexpr (std::is_same_v<T, float>)
                __openblao_BroadcastDiv_float32(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, double>)
                __openblao_BroadcastDiv_float64(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int32_t>)
                __openblao_BroadcastDiv_int32(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int16_t>)
                __openblao_BroadcastDiv_int16(a, b, c, n_a, n_b, n_c);

            else if constexpr (std::is_same_v<T, int8_t>)
                __openblao_BroadcastDiv_int8(a, b, c, n_a, n_b, n_c);
}

inline size_t __openblao_getUsableThread(const size_t total) {
    size_t cores = __openblao_TotalLogicalCoreInfo();
    constexpr size_t min_per_thread = 3'750'000; 

    size_t t = (total + min_per_thread - 1) / min_per_thread; 
    
    if (t < 1) t = 1;
    if (t > cores) t = cores;
    
    return t;
}



/*__INFORMATION__*/

// __openblao_headers
// __Do not modify unless you understand device specifics
// __This file contains headers and thread declarations only
// __Implementation is in openblao_imple.h

// __About the Library:
// -- Designed for high-performance use; not intended for frontend development
// -- Highly optimized and cross-platform
// -- Supports multiple SIMD instruction sets
// -- Supports large architectures, including:
//    --- ARM
//    --- x86 32-bit
//    --- x86 64-bit

// __Usage Notes:
// -- You can query the maximum threads supported on your device:
//       __openblao_TotalLogicalCoreInfo();
// -- Do not set thread_use to zero

// -- Approximately 67% of the library uses inline ASM
// -- Include this library via #include "openblao_headers"

// __Warning: Not a professional-grade library
// __Created by "myname", 2025/11/25
// __END__
