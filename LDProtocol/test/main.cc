#include <iostream>
#include <stdint.h>
#include "../interface.h"

//default eidan: BigEidan
#pragma pack(1)


int main(int argc, char *argv[]) {
	
	struct{
		uint32_t num;
	}LoginPackTest = 
	{
		.num = NetInt.LittleEidan.u32(3416616002u)
	};
	ld::HexString hex = hex_cast(LoginPackTest);
	hex.insert(hex.length(),"00 FF 00 FF 00 FF"_hex);

	hex.tea_encrypt("00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"_hex);
	std::cout << "Tea Encrypted:" << hex << std::endl;
	
	hex.tea_decrypt("00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00"_hex);
	std::cout << "Tea Decrypted:" << hex << std::endl;
	
	return 0;
}
#pragma pack()
