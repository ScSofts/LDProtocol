#include "utils/hexstring.h"
#include <stdint.h>
#pragma once
#include <interface.h>

ld::HexString BuildLoginPack(uint32_t uin,ld::HexString passwordMD5, const ld::Bin &shareKey, const ld::Bin &cPubKey);