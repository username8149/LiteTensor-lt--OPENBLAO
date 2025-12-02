#include "OPENBLAO/openblao.h"

#include <vector>
#include <iostream>
#include <cstdlib> 
#include <iostream>
#include <chrono>
#if defined(_WIN32) || defined(_WIN64)
#include <malloc.h>
#endif

namespace lt {
 
template<typename T>
class tensor {
    private:
        T* data = nullptr;
        size_t total = 1;
        std::vector<size_t> shape;
        std::vector<size_t> stride;
    
        static constexpr size_t Bytes = sizeof(T);
        static constexpr size_t alignment = __openblao_getAlignment();
        size_t thread_use = 1;
    
    
        inline void compute_strides() {
            const size_t ndim = shape.size();
            stride.resize(ndim);   
            size_t s = Bytes;
            for (int i = ndim - 1; i >= 0; --i) {
                stride[i] = s;
                if (i == 0) break;
                s *= shape[i];
            }
        }
        
        inline void Allocation() {
            #if defined(__unix__) || defined(__APPLE__)
        if (posix_memalign(reinterpret_cast<void**>(&data), alignment, total * Bytes) != 0)
            throw std::runtime_error("Allocation Failed");           
    #elif defined(_WIN32) || defined(_WIN64)
        data = static_cast<T*>(_aligned_malloc(total * Bytes, alignment));
        if (!data)
            throw std::runtime_error("Allocation Failed");           
    #else
        data = static_cast<T*>(malloc(total * Bytes));
        if (!data)
            throw std::runtime_error("Allocation Failed");
        #endif
        }
    
    public:
    
        tensor(const std::vector<size_t>& shp, T& value) : shape(shp) {
            
       for (auto i : shape) total *= i;
       thread_use = __openblao_getUsableThread(total);
       Allocation();
        
        if (thread_use > 1) {
                __openblao_fills(data, value, total, thread_use);
        } else {
                __openblao_fills(data, value, total);
        }
        
        compute_strides();
        
        }
        
        tensor(const std::vector<size_t>& shp) : shape(shp) {
            
        for (auto i : shape) total *= i;
        thread_use = __openblao_getUsableThread(total);
        Allocation();        
        compute_strides();
        
        }
        
        ~tensor() {
            #if defined(__unix__) || defined(__APPLE__)
            free(data);
        #elif defined(_WIN32) || defined(_WIN64)
            _aligned_free(data);
        #else
            free(data);
        #endif
        }

};

}

#include <chrono>

int main() {
    size_t N = 15'000'000;
    double value = 100;
    
    
    for (size_t i = 0; i < 10; ++i) {
    
    auto t0 = std::chrono::high_resolution_clock::now();
    lt::tensor a({N}, value);
    auto t1 = std::chrono::high_resolution_clock::now();
    
    auto ms = std::chrono::duration<double, std::milli>(t1-t0).count();
    
    std::cout << "time: " << ms << " ms\n";
    }
    
}