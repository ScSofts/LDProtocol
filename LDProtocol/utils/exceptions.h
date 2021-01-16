#pragma once
#include <cstddef>
#include <exception>
#include <stdint.h>
#include <string>

namespace ld{
    class TeaDecryptFailed:public std::exception{
    public:
        TeaDecryptFailed(const char* file ,const int32_t line);
        virtual const char * what() const noexcept override;
    protected:
        std::string message;
    };

    class ECDHGenKeyFailed:public std::exception{
    public:
        ECDHGenKeyFailed(const char* file ,const int32_t line);
        virtual const char * what() const noexcept override;
    protected:
        std::string message;
    
    };
};