#include "utils/hexstring.h"
#include <stdint.h>
#include <string>
#pragma once
#include <interface.h>


namespace ld
{
    struct DeviceInfo{
        std::string imei;
    };
    
};

ld::HexString BuildLoginPack(uint32_t uin, ld::HexString passwordMD5,
							 const ld::Bin &shareKey, const ld::Bin &pubKey,
							 const ld::Bin &privKey,
                             ld::DeviceInfo device);