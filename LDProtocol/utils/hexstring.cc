#include "../interface.h"
#include "hexstring.h"
#include <exception>
#include <stdint.h>
#include <string.h>
#include <string>
#include "../crypto/md5.h"

namespace ld {
	HexString::HexString(const std::string & str):std::string(str) {
		this->trim_start();
		this->trim_end();
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
	void HexString::trim_start(){
		auto i = this->begin();
		while ( isblank(*(i = this->begin()) )) {
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

	size_t HexString::cout(){
		return (*this + " ").length() / 3;
	}

	uint16_t HexString::toBigEidan(uint16_t u){
		return NetInt.BigEidan.u16(u);
	}

	uint32_t HexString::toBigEidan32(uint32_t u){
		return NetInt.BigEidan.u32(u);
	}

	void HexString::write(std::function<void(HexString &pack)> writer){
		writer(*this);
	}

	void HexString::appendBatch(std::initializer_list<HexString> batch){
		for(auto i:batch){
			this->append(i);
		}
	}
};

 ld::HexString operator ""_hex(const char* s,size_t ss){
	return ld::HexString(s);
}

 std::string operator ""_str(const char* s,size_t ss){
	return s;
}