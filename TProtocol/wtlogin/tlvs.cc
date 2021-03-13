#include "tlvs.hpp"
#include "utils/hexstring.h"
#include <stdint.h>


ld::HexString tlv::MakeTLV(std::string name, std::function<void (ld::HexString &)> writer){
    ld::HexString ret = ""_hex;
    writer(ret);
    ret.insert<uint16_t>(0, (uint16_t)ret.length());
    ret.insert(0, ld::HexString(name));
    return ret;
}