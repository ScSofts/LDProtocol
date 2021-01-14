#include "cast.h"
#include <stdint.h>

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