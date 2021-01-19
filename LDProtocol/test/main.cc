#include <iostream>
#include <stdint.h>
#include "../interface.h"

//default eidan: BigEidan
#pragma pack(1)


int main(int argc, char *argv[]) {
	using ld::byte;

	struct{
		uint32_t size;
		char name[256];
	}head={
		.name = "Hello World!"
	};
	head.size = NetInt.LittleEidan.u32(sizeof(head));
	auto hex_head = hex_cast(head);
	auto bin = bin_cast(hex_head);
	// std::cout << hex_head << std::endl;
	std::cout << 
		bin.fetch<decltype(head)>().name 
		<< std::endl << bin.size();
	return 0;
}
#pragma pack()
