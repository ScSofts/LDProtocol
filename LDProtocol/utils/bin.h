#pragma once
#include <vector>
namespace ld {
	using BinVec = std::vector<byte>;
	class HexString;
	class Bin;
	using byte = unsigned char;

	class Bin :public std::vector<byte> {
	public:
		Bin(const BinVec &vec):std::vector<byte>(vec){}
		Bin():std::vector<byte>(){}
		
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

		template<class ToType>
		const ToType fetch(){
			ToType tmp;
			tmp = this->cast_to<ToType>();
			this->erase(this->begin(),this->begin() + sizeof(ToType));
			return tmp;
		}

		Bin fetch(size_t size){
			Bin tmp = {};
			tmp = BinVec{this->begin(),this->begin() + size};
			this->erase(this->begin(),this->begin() + size);
			return tmp;
		}
	};
};