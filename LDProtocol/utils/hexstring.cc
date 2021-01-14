#include "hexstring.h"
#include <string.h>
namespace ld {
	HexString::HexString(const std::string & str):std::string(str) {
		}

	HexString::HexString(const HexString &str) : std::string(str) {
	}
	HexString::HexString(HexString &&str) : std::string(str) {
	}
	HexString::~HexString() {
	}

	void HexString::trim_end(){
		auto i = this->end() - 1;
		while ( isblank(*(i = this->end() - 1) )) {
			erase(i);
		}
	}
	size_t ByteOffset(uint32_t bytes){
		//aa bb cc dd ee
		//      ↑
		// 2 byte -> 6 offset
		return (3 * bytes);
	}
};