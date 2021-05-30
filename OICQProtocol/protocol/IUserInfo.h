#pragma once
#include <functional>
#include <interface.h>
#include <string>
#include "IDevice.h"
#pragma pack(push,1)

struct IUserInfo{
    using string = std::string;
    using Bin = ld::Bin;
    using BinVec = ld::BinVec;
    using HexString = ld::HexString;

    uint32_t uin;
    const struct Apk{
        string id;
        string name;
        string version;
        string ver;
        Bin sign;
        u32 buildtime;
        u32 appid;
        u32 subid;
        u32 bitmap;
        u32 sigmap;
        string sdkver;
    }apks[5]={
        //android phone
        {
            .id =  "com.tencent.mobileqq",
            .name =  "A8.4.1.2703aac4",
            .version =  "8.4.1.2703",
            .ver =  "8.4.1",
            .sign = BinVec{166, 183, 69, 191, 36, 162, 194, 119, 82, 119, 22, 246, 243, 110, 182, 141},
            .buildtime = 1591690260,
            .appid =  16,
            .subid =  537064989,
            .bitmap = 184024956,
            .sigmap = 34869472,
            .sdkver = "6.0.0.2428",
        },
        //apad
        {
            .id =  "com.tencent.minihd.qq",
            .name =  "A5.8.9.3460",
            .version =  "5.8.9.3460",
            .ver =  "5.8.9",
            .sign = BinVec{170, 57, 120, 244, 31, 217, 111, 249, 145, 74, 102, 158, 24, 100, 116, 199},
            .buildtime = 1595836208,
            .appid =  16,
            .subid =  537065549,
            .bitmap = 150470524,
            .sigmap = 1970400,
            .sdkver = "6.0.0.2428",
        },
        //watch
        {
            .id =  "com.tencent.mobileqq",
            .name =  "A8.4.1.2703aac4",
            .version =  "8.4.1.2703",
            .ver =  "8.4.1",
            .sign = BinVec{166, 183, 69, 191, 36, 162, 194, 119, 82, 119, 22, 246, 243, 110, 182, 141},
            .buildtime = 1591690260,
            .appid =  16,
            .subid =  537061176,
            .bitmap = 184024956,
            .sigmap = 34869472,
            .sdkver = "6.0.0.2428",
        },
        //mac (experimental)
        {
            .id =  "com.tencent.minihd.qq",
            .name =  "A5.8.9.3460",
            .version =  "5.8.9.3460",
            .ver =  "5.8.9",
            .sign = BinVec{170, 57, 120, 244, 31, 217, 111, 249, 145, 74, 102, 158, 24, 100, 116, 199},
            .buildtime = 1595836208,
            .appid =  16,
            .subid =  537064315,
            .bitmap = 150470524,
            .sigmap = 1970400,
            .sdkver = "6.0.0.2428",
        },
        //ipad (experimental)
        {
             .id =  "com.tencent.minihd.qq",
            .name =  "A5.8.9.3460",
            .version =  "5.8.9.3460",
            .ver =  "5.8.9",
            .sign = BinVec{170, 57, 120, 244, 31, 217, 111, 249, 145, 74, 102, 158, 24, 100, 116, 199},
            .buildtime = 1595836208,
            .appid =  16,
            .subid =  537065739,
            .bitmap = 150470524,
            .sigmap = 1970400,
            .sdkver = "6.0.0.2428",
        }
    };

    struct{
        ld::HexString ticket_key;
        ld::HexString sig_key;
        ld::HexString srm_token;
        ld::HexString tgt;
        ld::HexString d2key;
        
    }sig;

    void d2key2tgtgt();
    
    IDevice device;

    u8 emp = 1;
    Apk apk = apks[0];

    Bin t0104 = {};
    Bin t0174 = {};
    HexString code;

    Bin d2 = {};
    u32 seq_id = 0;
    Bin ticket = {};

    HexString password_md5 = ""_hex;
    string imei = "";
    Bin ksid = {};
};

#pragma pack(pop)