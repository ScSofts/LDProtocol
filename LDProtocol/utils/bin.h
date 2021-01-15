#pragma once
#include "../interface.h"
namespace ld {
	class Bin :public std::vector<byte> {
	public:
		void tea_encrypt(const HexString & key);
		void tea_encrypt(const Bin & key);

		void tea_decrypt(const HexString &key);
		void tea_decrypt(const Bin &key);
	};
};