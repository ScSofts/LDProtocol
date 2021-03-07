#pragma once
#include "utils/hexstring.h"
#include <interface.h>
#include <functional>
#ifndef LE
    #define LE NetInt.LittleEidan
    #define BE NetInt.BigEidan
#endif

namespace tlv {
   ld::HexString MakeTLV(std::string name, std::function<void(ld::HexString &pack)> writer);
};
