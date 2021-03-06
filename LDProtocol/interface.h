#pragma once
#include <stdint.h>
#include <string>
#include <vector>
#include <exception>

#include "../third_party/json/json.h"
namespace ld {
	using byte = unsigned char;
	using Json = nlohmann::json;
};
#include "utils/bin.h"
#include "utils/hexstring.h"
#include "utils/cast.h"
#include "utils/exceptions.h"
#include "utils/random.h"
#include "crypto/ecdh.h"
#include "tlv/tlv.h"

namespace  {
	using u8 = uint8_t;
	using u16 = uint16_t;
	using u32 = uint32_t;
	using u64 = uint64_t;
};