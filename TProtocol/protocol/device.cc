#include "index.h"
#include "IDevice.h"
#include "utils/hexstring.h"
#include "utils/random.h"
#include <string>

void MakeIMEI(IUserInfo &info){
    const auto uin = info.uin;
    std::string imei_str = uin % 2 ? "86" : "35";
    auto buf = ld::HexString{""};
    buf.append(BE.u32(uin));
    auto tmpb = bin_cast(buf);
    tmpb[0] = 0;
    auto a = LE.u16(bin_cast(buf).fetch<uint16_t>());
    auto b = LE.u32(tmpb.fetch<uint32_t>());

    if(a > 9999){
        a = u16(a / 10);
    }else if(a < 1000){
        auto a_str = std::to_string(uin).substr(0,4);
        a = u16(atoi(a_str.data()));
    }

    while(b >= 9999999)
        b = b >> 1;

    if(b < 1000000){
        auto b_str = std::to_string(uin).substr(0,4) + std::to_string(uin).substr(0,3);
        b = u16(atoi(b_str.data()));
    }

    imei_str += std::to_string(a) + "0" + std::to_string(b);
    auto calcSP = [&](){
        u64 sum = 0;
        for(int i = 0; i< imei_str.size(); i ++){
            if(i % 2){
                auto j = imei_str[i] * 2;
                sum += j % 10 + floor((double)j / 10);
            }else{
                sum += atoi(&imei_str[i]);
            }
        }
        return (100 - sum) % 10;
    };
    imei_str += std::to_string(calcSP());
    auto imei = u64(atol(imei_str.data()));
    info.imei = imei_str;
    return;
}

void MakeUserDeviceInfo(IUserInfo &info,IDevice &device){
    device.deviceInfo.imei = info.imei;
    const auto hash = bin_cast(std::to_string(info.uin)).sum_md5();
    const auto hex = hex_cast(hash);
    const auto uuid = 
          hex.substr(0,8) + "-" 
        + hex.substr(12,4) + "-" 
        + hex.substr(16,4) + "-" 
        + hex.substr(20);
    auto toString16 = [](u32 u){
        std::string data;
        data.reserve(20);
        sprintf(data.data(),"%x",u);
        return data;
    };

    auto toString16Upper = [](u32 u){
        std::string data;
        data.reserve(20);
        sprintf(data.data(),"%X",u);
        return data;
    };
    if(device.deviceInfo.wifi_ssid == "MERCURY-"){
        device.deviceInfo.wifi_ssid += toString16(info.uin);
    }

    if(device.deviceInfo.android_id == "OICQX."){
        device.deviceInfo.android_id += std::to_string(LE.u16(hash.cast_to<u16>())) + std::to_string(hash[2]) + std::to_string(hash[3]) + std::to_string(info.uin)[0];
    }

    if(device.deviceInfo.boot_id == ""){
        device.deviceInfo.boot_id = uuid;
    }

    if(device.deviceInfo.proc_version == "Linux version 4.20.60-"){
        device.deviceInfo.proc_version += std::to_string(LE.u16(hash.cast_to<u16>())) +
                                            " (https://github.com/scsofts)"; 
    }

    if(device.deviceInfo.mac_address == "00:50:"){
        device.deviceInfo.mac_address += 
            toString16Upper(hash[6]) + ":" +
            toString16Upper(hash[7]) + ":" +
            toString16Upper(hash[8]) + ":" +
            toString16Upper(hash[9]);
    }

    if(device.deviceInfo.ip_address == "10.0."){
        device.deviceInfo.ip_address = "192.168.0." + 
        ( (hash[1] <= 1) ? "2":std::to_string(hash[1]) );
    }

    if(device.deviceInfo.imei == ""){
        MakeIMEI(info);
        device.deviceInfo.imei = info.imei;
    }

    if(device.deviceInfo.incremental == ""){
        device.deviceInfo.incremental = LE.u32(hash.cast_to<u32>());
    }

    auto getDeviceInfo = [&info,&device](){
        const auto & d = device.deviceInfo;
        device.display = d.android_id;
        device.product = d.product;
        device.device = d.device;
        device.board = d.board;
        device.model = d.model;
        device.bootloader = d.bootloader;
        device.fingerprint = d.brand + '/' + d.product + '/' + d.device + ":10/" + d.android_id + '/' + d.incremental + ":user/release-keys";
        device.boot_id = d.boot_id;
        device.proc_version = d.proc_version;
        device.baseband = "";
        device.sim = "T-Mobile";
        device.os_type = "android";
        device.mac_address = d.mac_address;
        device.ip_address = d.ip_address;
        device.wifi_bssid = d.mac_address;
        device.wifi_ssid = d.wifi_ssid;
        device.imei = d.imei;
        device.android_id = d.android_id;
        device.apn = "wifi";
        device.version.incremental = d.incremental;
        device.version.release = "10";
        device.version.codename = "REL";
        device.version.sdk = 29;
        static ld::Random rand;
        rand.Init();
        device.imsi = hex_cast(rand.RandBin(16));
        device.tgtgt = hex_cast(rand.RandBin(16));
        auto guidBuff = ""_hex;
        guidBuff.append(device.imei);
        guidBuff.append(device.mac_address);
        device.guid =  hex_cast(bin_cast(guidBuff).sum_md5());
    };

    getDeviceInfo();
    if(info.ksid.empty()){
        ld::HexString ksid = ""_hex;
        ksid.append("|"_str);
        ksid.append(device.imei);
        ksid.append("|"_str);
        ksid.append(info.apk.name);
        info.ksid = bin_cast(ksid);
    }
    info.device = device;
}