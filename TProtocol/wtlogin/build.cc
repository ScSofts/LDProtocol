#include "index.h"
#include <interface.h>
#define LE NetInt.LittleEidan
#define BE NetInt.BigEidan

namespace tlv {

};

static inline ld::HexString BuildLoginPackOutside(uint32_t uin, ld::HexString passwordMD5, const ld::Bin &shareKey, const ld::Bin &cPubKey);

ld::HexString BuildLoginPack(uint32_t uin,ld::HexString passwordMD5, const ld::Bin &shareKey, const ld::Bin &cPubKey){
    ld::HexString pack{""};
    using namespace tlv;
    ld::HexString packInside{""};
    struct{
        uint32_t bodyType = LE.u32(0xA);
        uint8_t cryptoType = LE.u8(0x2);
        uint32_t bufferLength = LE.u32(0x4);
        uint8_t unknown = 0;
    }wtloginHead={

    };
    
    packInside.append(wtloginHead);

    auto uinHex = hex_cast(std::to_string(uin));
    packInside.appendLV(uinHex);

    packInside.append(BuildLoginPackOutside(uin, passwordMD5, shareKey, cPubKey));

    pack.appendLLV(packInside);
    return pack;
}


static inline ld::HexString BuildLoginPackInside(uint32_t uin, ld::HexString passwordMD5, const ld::Bin &shareKey);

static inline ld::HexString BuildLoginPackOutside(uint32_t uin, ld::HexString passwordMD5, const ld::Bin &shareKey, const ld::Bin &cPubKey){
    ld::HexString pack{""};
    struct{
        uint32_t RquestBodyLength;
        uint32_t SsoSeq = LE.u32(77923);
        uint32_t AppID1;
        uint32_t AppID2;
        ld::byte Unknown[12] = {0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        uint32_t Len1 = LE.u32(0x4);
        uint32_t Len2;
        char CmdName[13];//"wtlogin.login"
        uint32_t Len3;
        uint32_t MsgCookie;
        uint_fast32_t Len4;
        ld::byte UnknownTicket[15] = {38, 36, 33, 32, 35, 34, 38, 32, 38, 31, 32, 30, 36, 31, 37};
        ld::byte Fixed[42] = {0x0,  0x0, 0x0, 0x4, 
                              0x0,  0x22, 
                              
                              0x7C, 0x34, 0x36, 0x30, 0x30, 0x37,
                               0x37, 0x34, 0x31, 0x39, 0x32, 0x30, 
                               0x36, 0x31, 0x35, 0x35, 0x7C, 0x41,
                               0x32, 0x2E, 0x35, 0x2E, 0x34, 0x2E, 
                               0x65, 0x35, 0x61, 0x64, 0x30, 0x65,
                              0x38, 0x37,
                              
                              0x00, 0x00, 0x00, 0x04};
        /**
         * fixed
         * 00 00 00 04 //Length:4
         * 00 22 //Length:34
         * 7C 34 36 30 30 37 37 34 31 39 32 30 36 31 35 35 7C 41 32 2E 35 2E 34 2E 65 35 61 64 30 65 38 37 //|460077419206155|A2.5.4.e5ad0e87
         * 00 00 00 04
         */
    }requestBodyHead = {
        .RquestBodyLength = sizeof(requestBodyHead),
        .AppID1 = 537063883,
        .AppID2 = requestBodyHead.AppID1,
        //Length of Next Data + Length of "Len*" self
        .Len2 = LE.u32(13 + 4 ),
        .Len3 = LE.u32(4 + 4),
        .Len4 = LE.u32(15 + 4)
    };
    memcpy(requestBodyHead.CmdName, "wtlogin.login" , sizeof("wtlogin.login") - 1);
    
    pack.append(requestBodyHead);
    pack.append(BuildLoginPackInside(uin, passwordMD5, shareKey));

    ld::Bin outsideKey = ld::BinVec{0,0,0,0 ,0,0,0,0 ,0,0,0,0 ,0,0,0,0};
    pack.tea_encrypt(outsideKey);
    return pack;
}

static inline ld::HexString BuildLoginPackInside(uint32_t uin, ld::HexString passwordMD5, const ld::Bin &shareKey){
    ld::HexString pack = ""_hex;

    pack.tea_encrypt(shareKey);
    return pack;
}