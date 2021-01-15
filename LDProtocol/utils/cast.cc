#include "cast.h"
#include <cstdint>

uint8_t uint_cast::to_le::u8(uint8_t original){
    //only one byte, just return it
    return original;
}

uint16_t uint_cast::to_le::u16(uint16_t original){
    constexpr uint16_t mask_1 = 0xFF00u;
    constexpr uint16_t mask_2 = 0x00FFu;
    return (
        ( (original &  mask_1) >> 8  ) |
        ( (original &  mask_2) << 8  ) 
    );
}

uint32_t uint_cast::to_le::u32(uint32_t original){
    constexpr uint32_t mask_1 = 0xFF000000u;
    constexpr uint32_t mask_2 = 0x00FF0000u;
    constexpr uint32_t mask_3 = 0x0000FF00u;
    constexpr uint32_t mask_4 = 0x000000FFu;
    //[x] => 8 bit
    //[1] [2] [3] [4]
    //[4] [3] [2] [1]
    return (
        (original & mask_1) >> (8*3) |
        (original & mask_2) >> (8*1) |
        (original & mask_3) << (8*1) |
        (original & mask_4) << (8*3)
    );
}

uint64_t uint_cast::to_le::u64(uint64_t original){
    constexpr uint64_t mask_1 = 0xFF00000000000000u;
    constexpr uint64_t mask_2 = 0x00FF000000000000u;
    constexpr uint64_t mask_3 = 0x0000FF0000000000u;
    constexpr uint64_t mask_4 = 0x000000FF00000000u;
    constexpr uint64_t mask_5 = 0x00000000FF000000u;
    constexpr uint64_t mask_6 = 0x0000000000FF0000u;
    constexpr uint64_t mask_7 = 0x000000000000FF00u;
    constexpr uint64_t mask_8 = 0x00000000000000FFu;
    return (
        ( (original & mask_1) >> (8*7) )|
        ( (original & mask_2) >> (8*5) )|
        ( (original & mask_3) >> (8*3) )|
        ( (original & mask_4) >> (8*1) )|
        
        ( (original & mask_5) << (8*1) )|
        ( (original & mask_6) << (8*3) )|
        ( (original & mask_7) << (8*5) )|
        ( (original & mask_8) << (8*7) )
    );
}


uint8_t uint_cast::to_be::u8(uint8_t original){
    //only one byte, just return it
    return original;
}

uint16_t uint_cast::to_be::u16(uint16_t original){
    constexpr uint16_t mask_1 = 0xFF00u;
    constexpr uint16_t mask_2 = 0x00FFu;
    return (
        ( (original &  mask_1) >> 8  ) |
        ( (original &  mask_2) << 8  ) 
    );
}

uint32_t uint_cast::to_be::u32(uint32_t original){
    constexpr uint32_t mask_1 = 0xFF000000u;
    constexpr uint32_t mask_2 = 0x00FF0000u;
    constexpr uint32_t mask_3 = 0x0000FF00u;
    constexpr uint32_t mask_4 = 0x000000FFu;
    //[x] => 8 bit
    //[4] [3] [2] [1]
    //[1] [2] [3] [4]
    return (
        (original & mask_1) >> (8*3) |
        (original & mask_2) >> (8*1) |
        (original & mask_3) << (8*1) |
        (original & mask_4) << (8*3)
    );
}

uint64_t uint_cast::to_be::u64(uint64_t original){
    constexpr uint64_t mask_1 = 0xFF00000000000000u;
    constexpr uint64_t mask_2 = 0x00FF000000000000u;
    constexpr uint64_t mask_3 = 0x0000FF0000000000u;
    constexpr uint64_t mask_4 = 0x000000FF00000000u;
    constexpr uint64_t mask_5 = 0x00000000FF000000u;
    constexpr uint64_t mask_6 = 0x0000000000FF0000u;
    constexpr uint64_t mask_7 = 0x000000000000FF00u;
    constexpr uint64_t mask_8 = 0x00000000000000FFu;
    return (
        ( (original & mask_1) >> (8*7) )|
        ( (original & mask_2) >> (8*5) )|
        ( (original & mask_3) >> (8*3) )|
        ( (original & mask_4) >> (8*1) )|
        
        ( (original & mask_5) << (8*1) )|
        ( (original & mask_6) << (8*3) )|
        ( (original & mask_7) << (8*5) )|
        ( (original & mask_8) << (8*7) )
    );
}

ld::Bin bin_cast(const ld::HexString &hex){
    ld::Bin ret;
    
    std::string tmp = "";
    std::string hex_copy = hex.data();
    
    hex_copy += " ";//fill in the missing space.

    unsigned int tmp_byte;//unsigned int required,or warning for sscanf_s

    for (auto current : hex_copy) {
        if (!isblank(current) && current != '\r') {
            tmp += current;
        }
        else
            tmp = "";

        if (tmp.size() == 2) {
            sscanf_s(tmp.data(), "%02X", &tmp_byte);
            ret.push_back((ld::byte)tmp_byte);
        }
    }
    return ret;
}

template<>
 ld::HexString hex_cast(const ld::HexString &strings)
{	
	return strings;
}

template<>
 ld::HexString hex_cast(const ld::Bin &binary_set){
	using ld::byte;
	using ld::HexString;

	auto size = binary_set.size();//sizeof binary set to cast

	size_t tmp_length = size * 3 + 1;

	char* buf = new char[tmp_length];
	memset(buf, 0, tmp_length);
	byte *t = (byte*)(binary_set.data());

	for (auto i = 0u; i < size; i++)
	{
		sprintf_s(buf, tmp_length, "%s%02X ", buf, *(t + i));
	}

	buf[tmp_length - 1] = '\0';
	HexString str = HexString(buf);
	str.trim_end();
	delete[] buf;
	return str;
}

template<>
 ld::HexString hex_cast(const std::string &strings) {
	using ld::byte;
	using ld::HexString;

	auto size = strings.size();//sizeof string to cast

	size_t tmp_length = size * 3 + 1;

	char* buf = new char[tmp_length];
	memset(buf, 0, tmp_length);
	byte *t = (byte*)(strings.data());

	for (auto i = 0u; i < size; i++)
	{
		sprintf_s(buf, tmp_length, "%s%02X ", buf, *(t + i));
	}

	buf[tmp_length - 1] = '\0';
	HexString str = HexString(buf);
	str.trim_end();
	delete[] buf;
	return str;
}