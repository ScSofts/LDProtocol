#include "./wtlogin/index.h"
#include "utils/hexstring.h"
#include <interface.h>
#include <iostream>

#ifndef LE
#define LE NetInt.LittleEidan
#define BE NetInt.BigEidan
#endif

int main(int argc, char *argv[]) {
	auto keyGroup = ld::MakeECDH(ld::ECDHVersion::_839);

	ld::DeviceInfo device{""};
	ld::HexString hex = BuildLoginPack(
		LE.u32(3416616002),
		"C3 2A 36 A8 2F 80 6C 6F 76 06 A0 DF 60 71 98 CF"_hex,
		keyGroup.share_key, keyGroup.public_key, keyGroup.private_key, device);

	std::cout << hex << std::endl;
	return 0;
}