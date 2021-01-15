#pragma once
#include <stdint.h>
#include <string>

namespace ld {
	class HexString;
	class Bin;
}
template<class T>
ld::HexString hex_cast(const T &structure);

namespace ld{
	size_t ByteOffset(uint32_t bytes);

	class HexString :public std::string{
	public:
		HexString(const std::string &);
		HexString(const HexString &);
		HexString(HexString &&);
		~HexString();

		template<class T>
		inline void append(const T &structure){
			(*this) += " " + hex_cast(structure);
			this->trim_end();
		}

		template<>
		inline void append(const HexString &structure){
			(*this) += " " + structure;
			this->trim_end();
		}

		template<class T>
		inline void insert(size_t offset,const T &structure){
			const auto offset_ = (offset == length() + 1) ? length() : offset;
			
			const auto blank = (offset_ == this->length()) ? " " : "";
			const auto end = (offset_ == this->length()) ? "": " ";
			
			basic_string::insert(offset_,blank + hex_cast(structure) + end);
		}

		void trim_end();

		void tea_encrypt(const HexString & key);
		void tea_encrypt(const Bin & key);

		void tea_decrypt(const HexString &key);
		void tea_decrypt(const Bin &key);
	};
};

 ld::HexString operator ""_hex(const char* s,size_t ss);
 std::string operator ""_str(const char *s,size_t ss);