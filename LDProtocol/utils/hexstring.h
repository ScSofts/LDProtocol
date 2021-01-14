#pragma once
#include <stdint.h>
#include <string>
#include <vcruntime.h>


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

		template<class T>
		inline void insert(size_t offset,const T &structure){
			basic_string::insert(offset,hex_cast(structure));
		}

		void trim_end();
	};
};