#include "../interface.h"
#include "hexstring.h"
#include <exception>
#include <string.h>
#include <string>
#include "../crypto/md5.h"

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

	void HexString::tea_encrypt(const Bin &key){
		auto bin =  bin_cast(*this);
		bin.tea_encrypt(key);
		this->std::string::operator=(hex_cast(bin));
	}

	void HexString::tea_encrypt(const HexString &key){
		auto bin =  bin_cast(*this);
		bin.tea_encrypt(key);
		this->std::string::operator=(hex_cast(bin));
	}

	void HexString::tea_decrypt(const HexString &key){
		auto bin =  bin_cast(*this);
		try{
			bin.tea_decrypt(key);
		}catch(std::exception e){
			throw TeaDecryptFailed(__FILE__,__LINE__);
		}
		this->std::string::operator=(hex_cast(bin));
	}

	void HexString::tea_decrypt(const Bin &key){
		auto bin =  bin_cast(*this);
		try{
			bin.tea_decrypt(key);
		}catch(std::exception e){
			throw TeaDecryptFailed(__FILE__,__LINE__);
		}
		this->std::string::operator=(hex_cast(bin));
	}

	HexString HexString::sum_md5(){
		return hex_cast(MD5{}.sum(bin_cast(*this)));
	}
};

 ld::HexString operator ""_hex(const char* s,size_t ss){
	return ld::HexString(s);
}

 std::string operator ""_str(const char* s,size_t ss){
	return s;
}