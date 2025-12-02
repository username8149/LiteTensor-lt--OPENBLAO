LiteTensor (lt) – OPENBLAO Accelerated Tensor Library

LiteTensor is a lightweight C++ tensor library designed for small devices and embedded environments.
It includes OPENBLAO, a custom ARM64-optimized kernel providing fast elementwise and broadcast operations.

Features

Lightweight tensor operations (add, multiply, broadcast add, etc.)

ARM64-optimized kernel (NEON / AArch64)

Automatic fallback to generic C++ when SIMD is not supported (planned)

Threaded operations with CPU parallelism

Easy-to-extend architecture

lt::tensor<float> a({2, 3});
lt::tensor<float> b({2, 3});

auto c = a + b;     // deep copy result
auto d = c.view();  // shallow copy
auto e = c.copy();  // deep copy

Architecture Question / Request for Feedback

I currently only have ARM64 hardware, and OPENBLAO is optimized for NEON.
I need contributors/testers to help verify behavior on:

x86_64 (AVX / SSE)

ARM (Armv7, Sve, Sve2)

Windows (MSVC)

macOS (x86_64 Intel Mac)

Linux desktop


Specifically:

> How should I structure architecture detection and fallback logic to avoid undefined behavior or segfault when SIMD paths are unavailable?
