#include <iostream>
#include <stdint.h>
#include "../interface.h"

//default eidan: BigEidan

#pragma pack(1)
struct Pack {
	uint8_t c;
};
#pragma pack()

int main(int argc, char *argv[]) {
	
	Pack p = {NetInt.LittleEidan.u8(1)};
	ld::HexString hex("00 ff");
	std::cout << hex << std::endl;
	system("pause");
	return 0;
}
