#pragma once
#include <vector>
#include "../interface.h"
namespace ld {
	class Bin :public std::vector<byte> {
	public:
		friend inline ld::HexString hex_cast(Bin &Struct);
	};
};