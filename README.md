# LiteTensor-lt--OPENBLAO
I wrote a small tensor library with an ARM64-optimized kernel.  It works on my device, but I'm unsure about portability to x86_64  because I only have ARM64 hardware.  How should I structure my code to provide an architecture-safe fallback,  and avoid undefined behavior or segfaults when the SIMD path is not available?
