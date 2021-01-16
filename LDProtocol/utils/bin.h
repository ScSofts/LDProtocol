#pragma once
namespace ld {
	using BinVec = std::vector<byte>;
	class HexString;
	class Bin;
	using byte = unsigned char;

	class Bin :public std::vector<byte> {
	public:
		const Bin& operator =(const BinVec&);
		void tea_encrypt(const HexString & key);
		void tea_encrypt(const Bin & key);

		void tea_decrypt(const HexString &key);
		void tea_decrypt(const Bin &key);
		Bin sum_md5();
		template<class ToType>
		const ToType &cast_to(){
			return *reinterpret_cast<const ToType*>(this->data());
		}
	};
};