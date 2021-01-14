#pragma once
#include <stdint.h>
#include <string>


namespace ld {
	class HexString;
}
template<class T>
inline ld::HexString hex_cast(const T &structure);

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
			(*this) += hex_cast(structure);
		}

		template<>
		inline void append(const HexString &structure){
			(*this) += " " + structure;
		}

		template<class T>
		inline void insert(size_t offset,const T &structure){
			const auto offset_ = (offset == length() + 1) ? length() : offset;
			
			const auto blank = (offset_ == this->length()) ? " " : "";
			const auto end = (offset_ == this->length()) ? "": " ";
			
			basic_string::insert(offset_,blank + hex_cast(structure) + end);
		}

		void trim_end();
	};
};