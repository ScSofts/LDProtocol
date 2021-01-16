#include <iostream>
#include <stdint.h>
#include "../interface.h"

//default eidan: BigEidan
#pragma pack(1)


int main(int argc, char *argv[]) {
	
	std::cout << 
		hex_cast(ld::MakeECDH(ld::ECDHVersion::_841).share_key)
	<< std::endl;
	
	return 0;
}
#pragma pack()
