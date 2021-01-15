#pragma once
#include "../interface.h"
#include <cstdio>
#include <cstdint>
#include <string>
#include <type_traits>
#include <memory.h>

#pragma pack(1)
namespace ld {
	class Bin;
	class HexString;
}

//cast struct to hex
template<class T>
ld::HexString hex_cast(const T &structure){
	using ld::byte;
	using ld::HexString;
	
	static_assert(
		std::is_class<T>::value == true
		|| (
			std::is_literal_type<T>::value == true 
				&& std::is_array<T>::value != true
		),
		"hex_cast cannot cast T to byte*!"
		  );
	
	auto size = sizeof(structure);//sizeof structure to cast

	size_t tmp_length = size * 3 + 1;
	
	char* buf = new char[tmp_length];
	memset(buf, 0, tmp_length);
	const byte *t = (const byte*)(&structure);

	for (auto i = 0u; i < size; i++)
	{
		sprintf_s(buf, tmp_length, "%s%02X ", buf, *( t + i) );
	}
	
	HexString str((std::string(buf)));
	str.trim_end();
	delete[] buf;
	return str;
}

//HexString donot need to encode  ( defined in cast.cc )
template<>  ld::HexString hex_cast(const ld::HexString &strings);

//string to hex
template<>  ld::HexString hex_cast(const std::string &strings);


//cast to binary set ( defined in cast.cc )
ld::Bin bin_cast(const ld::HexString & hex);

//cast binary set to hex ( defined in cast.cc )
template<>  ld::HexString hex_cast(const ld::Bin &binary_set);


static class uint_cast{
public:
	static class to_le{
	public:
	
		static uint64_t u64(uint64_t original);
		static uint32_t u32(uint32_t original);
		static uint16_t u16(uint16_t original);
		static uint8_t u8(uint8_t original);
	}LittleEidan;

	static class to_be{
	public:
	
		static uint64_t u64(uint64_t original);
		static uint32_t u32(uint32_t original);
		static uint16_t u16(uint16_t original);
		static uint8_t u8(uint8_t original);
	}BigEidan;
}NetInt;

#pragma pack()