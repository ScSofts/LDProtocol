#include <interface.h>
#include <iostream>
#include "./wtlogin/index.h"

int main(int argc, char *argv[]){
    auto keyGroup = ld::MakeECDH(ld::ECDHVersion::_839);
    ld::HexString hex = BuildLoginPack(
        NetInt.LittleEidan.u32(3416616002),
        "C3 2A 36 A8 2F 80 6C 6F 76 06 A0 DF 60 71 98 CF"_hex,
        keyGroup.share_key);
    std::cout << hex << std::endl;
    return 0;
}