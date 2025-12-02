/**************************
DEFINE PLATFORM VERSION
***************************/

#if defined(__AVX512F__)
    #define PLATFORM 512
    
#elif defined(__AVX2__)
    #define PLATFORM 256
    
#elif defined(__SSE2__)
    #define PLATFORM 128
    
#elif defined(__ARM_FEATURE_SVE2)
    #define PLATFORM 2048
    
#elif defined(__ARM_FEATURE_SVE)
    #define PLATFORM 1024
    
#elif defined(__aarch64__)
    #define PLATFORM 64
    
#elif defined(__ARM_NEON)
    #define PLATFORM 32
    
#else
    #define PLATFORM 1
    
#endif

#if defined(__x86_64__) || defined(_M_X64)
    #define ARCT 8664

#elif defined(__i386__) || defined(_M_IX86)
    #define ARCT 8632

#elif defined(__aarch64__)
    #define ARCT 6464  

#elif defined(__arm__)
    #define ARCT 6432   

#else
    #define ARCT 1
#endif

/*__PLATFORM INFO__*/
#if defined(_WIN32) || defined(_WIN64)

    #include <windows.h>
    #define __openblao_TotalLogicalCoreInfo() ([]() -> uint32_t {           \
        unsigned int hc = std::thread::hardware_concurrency();\
        if (hc > 0) return hc;\
        SYSTEM_INFO sysinfo;\
        GetSystemInfo(&sysinfo);\
        return sysinfo.dwNumberOfProcessors;\
    })()

#elif defined(__APPLE__)

    #include <sys/sysctl.h>
    #define __openblao_TotalLogicalCoreInfo() ([]() -> uint32_t {           \
        unsigned int hc = std::thread::hardware_concurrency();\
        if (hc > 0) return hc;\
        uint32_t count;\
        size_t size = sizeof(count);\
        sysctlbyname("hw.logicalcpu", &count, &size, nullptr, 0); \
        return count;\
    })()

#elif defined(__linux__) || defined(__ANDROID__)

    #include <unistd.h>
    #define __openblao_TotalLogicalCoreInfo() ([]() -> uint32_t {           \
        unsigned int hc = std::thread::hardware_concurrency();\
        if (hc > 0) return hc;                                 \
                                                                \
        long n = sysconf(_SC_NPROCESSORS_ONLN);                \
        return n > 0 ? (uint32_t)n : 1;                        \
    })()

#else

    #define __openblao_TotalLogicalCoreInfo() ([]() -> uint32_t {           \
        unsigned int hc = std::thread::hardware_concurrency();\
        return hc > 0 ? hc : 1;                                \
    })()

#endif

#if PLATFORM >= 512
    #define __openblao_getAlignment() 256
#elif PLATFORM >= 256
    #define __openblao_getAlignment() 128
#elif PLATFORM >= 64
    #define __openblao_getAlignment() 64
#elif PLATFORM >= 1
    #define __openblao_getAlignment() 16
#else
    #error "Device Not Compatible"
#endif