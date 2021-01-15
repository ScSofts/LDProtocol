#include "exceptions.h"
#include <exception>
#include <string>
namespace ld
{
    TeaDecryptFailed::TeaDecryptFailed(const char* file ,const int32_t line):std::exception()
    {
        message = ("Decrypt Failed in" + std::string(file) + "," + std::to_string(line) + "!");
    }

    const char * TeaDecryptFailed::what()const noexcept{
        return message.data();
    }
}