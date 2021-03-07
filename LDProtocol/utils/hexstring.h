#pragma once
#include <initializer_list>
#include <stdint.h>
#include <string>
#include <functional>

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

		size_t cout();

		template<class T>
		inline void append(const T &structure){
			(*this) += (this->size() == 0 ? "" :" ") + hex_cast(structure);
			this->trim_end();
		}

		template<>
		inline void append(const HexString &structure){
			(*this) += (this->size() == 0 ? "" :" ") + structure;
			this->trim_end();
		}

		template<class T>
		inline void appendLV(const T & any){
			HexString hex = hex_cast(any);
			const auto length = toBigEidan((uint16_t)hex.cout());
			this->append((uint16_t)length);
			this->append(hex);
		}

		template<class T>
		inline void appendLLV(const T & any){
			HexString hex = hex_cast(any);
			const auto length = toBigEidan32((uint32_t)hex.cout());
			this->append((uint32_t)length);
			this->append(hex);
		}

		void appendBatch(std::initializer_list<HexString> batch);

		void write(std::function<void(HexString &pack)> writer);


		template<class T>
		inline void insert(size_t offset,const T &structure){
			const auto offset_ = (offset == length() + 1) ? length() : offset;
			
			const auto blank = (offset_ == this->length()) ? " " : "";
			const auto end = (offset_ == this->length()) ? "": " ";
			
			basic_string::insert(offset_,blank + hex_cast(structure) + end);
		}

		void trim_end();
		void trim_start();

		void tea_encrypt(const HexString & key);
		void tea_encrypt(const Bin & key);

		void tea_decrypt(const HexString &key);
		void tea_decrypt(const Bin &key);

		HexString sum_md5();
	private:
		uint16_t toBigEidan(uint16_t);
		uint32_t toBigEidan32(uint32_t);
	};
};

 ld::HexString operator ""_hex(const char* s,size_t ss);
 std::string operator ""_str(const char *s,size_t ss);