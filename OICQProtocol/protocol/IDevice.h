#pragma once
#include <interface.h>
#include <string.h>
#pragma pack(push,1)
struct IDevice{
    using string  = std::string;
    string display;
    string product;
    string device;
    string board;
    string brand;
    string model;
    string bootloader;
    string fingerprint;
    string boot_id;
    string proc_version;
    string baseband{""};
    string sim{"T-Mobile"};
    string os_type{"android"};
    string mac_address;
    string ip_address;
    string wifi_bssid;
    string wifi_ssid;
    string imei;
    string android_id;
    string apn{"wifi"};
    ld::HexString tgtgt;
    ld::HexString imsi;
    ld::HexString guid;
    struct{
        string incremental;
        string release{"10"};
        string codename{"REL"};
        u32 sdk{29};
    }version;
    struct{
        string product = "MRS4S";
        string device = "HIM188MOE";
        string board = "MIRAI-YYDS";
        string brand = "OICQX";
        string model = "Konata 2020";
        string wifi_ssid = "MERCURY-";
        string bootloader = "u-boot";
        string android_id = "OICQX.";
        string boot_id = "";
        string proc_version = "Linux version 4.20.60-";
        string mac_address = "00:50:";
        string ip_address = "10.0.";
        string imei = "";
        string incremental = "";
    }deviceInfo;
};

struct IUserInfo;
void MakeIMEI(IUserInfo &info);
void MakeUserDeviceInfo(IUserInfo &info,IDevice &device);
#pragma pack(pop)