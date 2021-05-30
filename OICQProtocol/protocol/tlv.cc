#include "index.h"
#include <string>
#include <time.h>

#pragma pack(push,1)

TlvMap MakeTLVMap(const IUserInfo &userInfo){
    using ld::HexString;
    using ld::BinVec;
    using ld::Random;
    using ld::Bin;

    static Random rand{};
    rand.Init();
    HexString tlvs = ""_hex;
#define TLVWriter(name) [&](HexString &name)

    TlvMap tlv_map{
        {"00 01",TLVWriter(pack){
            pack.append(BE.u16(1));
            pack.append(rand.RandBin(4));
            pack.append(BE.u32(time(nullptr)));
            pack.append(BinVec{0,0,0,0});
            pack.append(BE.u16(0));
        }},

        {"00 02",TLVWriter(pack){
//TODO:
        }},

        {"00 08",TLVWriter(pack){
            struct{
                uint16_t i1 = 0;
                uint32_t i2= BE.u32(2052);
                uint16_t i3 = 0;
            }value;
            pack.append(value);
        }},
        {"00 18",TLVWriter(pack){
            struct{
                u16 ping_ver = BE.u16(1);
                u32 i2 = BE.u32(1536);
                u32 i3 = 0;
                u32 uin;
                u32 i4 = 0;
            }value;
            value.uin = BE.u32(userInfo.uin);
            pack.append(value);
        }},
        {"01 00",TLVWriter(pack){
            struct{
                u16 db_buf_ver = BE.u16(1);
                u32 sso_ver = BE.u32(7);//≤7
                u32 appid;
                u32 subid;
                u32 app_client_ver = 0;
                u32 sigmap;
            }value;

            value.appid = userInfo.apk.appid;
            value.subid = userInfo.emp ? BE.u32(2) :userInfo.apk.subid;
            value.sigmap = userInfo.apk.sigmap;
        }},

        {"01 04",TLVWriter(pack){
            pack.append(userInfo.t0104);
        }},

        {"01 06",TLVWriter(pack){
            auto getBody = [&userInfo](){
                ld::HexString pack = ""_hex;
                pack.append(BE.u16(4)); // tgtgt ver
                pack.append(rand.RandBin(4));
                pack.append(BE.u32(7)); // sso ver
                pack.append(BE.u32(userInfo.apk.appid));
                pack.append(BE.u64(userInfo.uin));
                pack.append(BE.u32(time(nullptr)));
                pack.append(Bin{0,0,0,0});
                pack.append(BE.u8(1)); // save password
                pack.append(userInfo.password_md5);
                pack.append(userInfo.device.tgtgt);
                pack.append(BE.u32(0u));
                pack.append(BE.u8(1)); // guid available
                pack.append(BE.u32(1)); // login type password
                pack.appendLV(std::to_string(userInfo.uin));
                pack.append(BE.u16(0));
                return pack;
            };
            

            auto buf = ""_hex;
            buf.append(userInfo.password_md5);
            buf.append(Bin{0,0,0,0});
            buf.append(BE.u32(userInfo.uin));
            auto key = bin_cast(buf).sum_md5();
            auto body = getBody();
            body.tea_encrypt(key);
            pack.append(body);

        }},

        {"01 07",TLVWriter(pack){
            pack.append(BE.u16(0)); // pic type
            pack.append(BE.u8(0)); // captcha type
            pack.append(BE.u16(0)); // pic size
            pack.append(BE.u8(1)); // ret type
        }},

        {"01 08",TLVWriter(pack){
            pack.append(userInfo.ksid);
        }},

        {"01 09",TLVWriter(pack){
            pack.append(bin_cast(userInfo.device.imei).sum_md5());
        }},

        {"01 0A",TLVWriter(pack){
            pack.append(userInfo.sig.tgt);
        }},

        {"01 16",TLVWriter(pack){
            struct{
                u8 u1 = BE.u8(0);
                u32 bitmap;
                u32 sub_sigmap = BE.u32(0x10400);
                u8 app_id_list_size = BE.u8(1);
                u32 app_list[1]={BE.u32(1600000226)};
            }value;
            value.bitmap = userInfo.apk.bitmap;
            pack.append(value);
        }},

        {"01 28",TLVWriter(pack){
            struct {
                u16 i1 = BE.u16(0);
                u8 guid_new = BE.u8(0);
                u8 guid_available = BE.u8(1);
                u8 guid_change = BE.u8(0);
                u32 guid_flag = BE.u32(16777216);
            }value;
            pack.append(value);
            pack.appendLV(userInfo.device.model.substr(0,32));
            pack.appendLV(userInfo.device.guid.substr(0,16));
            pack.appendLV(userInfo.device.brand.substr(0,16));
        }},

        {"01 41",TLVWriter(pack){
            pack.append(BE.u16(1)); // ver
            pack.appendLV(userInfo.device.sim);
            pack.append(BE.u16(2)); // network type
            pack.append(userInfo.device.apn);
        }},

        {"01 42",TLVWriter(pack){
            pack.append(BE.u16(0));
            pack.append(userInfo.apk.id.substr(0,32));
        }},

        {"01 43",TLVWriter(pack){
            pack.append(userInfo.d2);
        }},

        {"01 44",TLVWriter(pack){
            auto body = ld::HexString("");
            body.append(BE.u16(5));
            body.write(tlv_map["01 09"]);
            body.write(tlv_map["05 2d"]);
            body.write(tlv_map["01 24"]);
            body.write(tlv_map["01 28"]);
            body.write(tlv_map["01 6e"]);
            body.tea_encrypt(userInfo.device.tgtgt);
            pack.append(body);
        }},

        {"01 45",TLVWriter(pack){
            pack.append(userInfo.device.guid);
        }},

        {"01 47",TLVWriter(pack){
            pack.append(BE.u32(userInfo.apk.appid));
            pack.appendLV(userInfo.apk.ver.substr(0,5));
            pack.appendLV(userInfo.apk.sign);
        }},

        {"01 54",TLVWriter(pack){
            pack.append(BE.u32(userInfo.seq_id));
        }},

        {"01 6A",TLVWriter(pack){
            pack.append(userInfo.sig.srm_token);
        }},

        {"01 6E",TLVWriter(pack){
            pack.append(userInfo.device.model);
        }},

        {"01 74",TLVWriter(pack){
            pack.append(userInfo.t0174);
        }},

        {"01 77",TLVWriter(pack){
            pack.append(BE.u8(0x01));
            pack.append(BE.u32(userInfo.apk.buildtime));
            pack.appendLV(userInfo.apk.sdkver);
        }},

        {"01 7A",TLVWriter(pack){
            pack.append(BE.u32(0));
        }},

        {"01 7C",TLVWriter(pack){
            pack.appendLV(userInfo.code);
        }},

        {"01 87",TLVWriter(pack){
            HexString mac_address = ""_hex;
            mac_address.append(userInfo.device.mac_address);
            pack.append(mac_address.sum_md5());
        }},

        {"01 88",TLVWriter(pack){
            HexString android_id = ""_hex;
            android_id.append(userInfo.device.android_id);
            pack.append(android_id.sum_md5());
        }},

        {"01 91",TLVWriter(pack){
            pack.append(BE.u8(0x82));
        }},

        {"01 93",TLVWriter(pack){
            pack.append(userInfo.ticket);
        }},

        {"01 94",TLVWriter(pack){
            pack.append(userInfo.device.imei);
        }},

        {"01 97",TLVWriter(pack){
            pack.appendLV(Bin({0x00}));
        }},

        {"01 98",TLVWriter(pack){
            pack.appendLV(Bin({0x00}));
        }},

        {"02 02",TLVWriter(pack){
            pack.appendLV(userInfo.device.wifi_bssid.substr(0,16));
            pack.appendLV(userInfo.device.wifi_ssid.substr(0,32));
        }},

        {"04 01",TLVWriter(pack){
            pack.append(rand.RandBin(16));
        }},

        {"05 11",TLVWriter(pack){
            std::string domains[] = {
                "tenpay.com", "openmobile.qq.com", "docs.qq.com", "connect.qq.com",
                "qzone.qq.com", "vip.qq.com", "qun.qq.com", "game.qq.com", "qqweb.qq.com",
                "office.qq.com", "ti.qq.com", "mail.qq.com", "gamecenter.qq.com", "mma.qq.com",
            };

            constexpr u32 length = sizeof(domains)/sizeof(domains[0]);
            pack.append(BE.u32(length));
            for(auto i : domains){
                pack.append(BE.u8(0x01));
                pack.append(i);
            }
        }},

        {"05 16",TLVWriter(pack){
            pack.append(BE.u32(0));
        }},

        {"05 21",TLVWriter(pack){
            pack.append(BE.u32(0)); // product type
            pack.append(BE.u16(0)); // const
        }},

        {"05 25",TLVWriter(pack){
            pack.append(BE.u16(0)); // tlv cnt
            pack.append(BE.u16(0x536));
            pack.appendLV(Bin{0x1,0x0});
        }},

        {"05 2d",TLVWriter(pack){
            //TODO: protobuf
        }}



    };

    #undef TLVWriter
    return tlv_map;
}
#pragma pack(pop)
