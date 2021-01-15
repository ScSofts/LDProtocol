#pragma once
#include "../interface.h"
#include <cstddef>
#include <exception>
#include <stdint.h>
#include <string>

namespace ld{
    class TeaDecryptFailed:public std::exception{
    public:
        TeaDecryptFailed(const char* file ,const int32_t line);
        TeaDecryptFailed(std::nullptr_t);
        virtual const char * what() const noexcept override;
    protected:
        std::string message;
    };
};