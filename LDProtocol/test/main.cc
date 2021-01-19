#include <iostream>
#include <stdint.h>
#include "../interface.h"

//default eidan: BigEidan
#pragma pack(1)


int main(int argc, char *argv[]) {
	using ld::byte;
	using ld::MakeTLV;
	using ld::HexString;
	struct{
		uint32_t size;
		char name[256];
	}head={
		.name = "Hello World!"
	};
	head.size = NetInt.LittleEidan.u32(sizeof(head));
	HexString tlv_101 = MakeTLV("01 01"_hex, head);
	std::cout << tlv_101 << std::endl;
	return 0;
}
#pragma pack()
