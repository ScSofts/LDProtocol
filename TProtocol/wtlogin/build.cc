#include <interface.h>
#include <stdint.h>
#include <string>
#include <time.h>

#include "./tlvs.hpp"
#include "index.h"
#include "utils/bin.h"
#include "utils/hexstring.h"
#include "utils/random.h"

#ifndef LE
#define LE NetInt.LittleEidan
#define BE NetInt.BigEidan
#endif

#ifndef FunctionShortCut
#define FunctionShortCut static constexpr auto
#endif

namespace tlv {
	class TLVs {
	  public:
		TLVs(uint32_t uin, ld::HexString passwordMD5, const ld::Bin &shareKey,
			 const ld::Bin &pubKey, const ld::Bin &privKey,
			 ld::DeviceInfo device);
		~TLVs();

		ld::HexString GetAll();

		ld::HexString Tlv001() {
			return this->makeTLV("00 01", [this](ld::HexString &pack) {
				pack.append(ld::Random::RandBin(4));
				pack.append(LE.u32(uin));
				pack.append(_time32(nullptr));
				pack.append(ld::BinVec{0, 0, 0, 0, 0, 0});
			});
		}

		ld::HexString Tlv008() {
			return this->makeTLV("00 08", [this](ld::HexString &pack) {
				pack.append("00 00 00 00 08 04 00 00"_hex);
			});
		}

		ld::HexString Tlv0116() {
			return this->makeTLV("01 16", [this](ld::HexString &pack) {
				pack.append("00 08 F7 FF 7C 00 01 04 00 01 5F 5E 10 E2"_hex);
			});
		}
		ld::HexString Tlv0116_1() {
			return this->makeTLV("01 16", [this](ld::HexString &pack) {
				pack.append("00 08 F7 FF 7C 00 01 04 00 00"_hex);
			});
		}

		ld::HexString Tlv016a(ld::HexString _016A) {
			return this->makeTLV(
				"01 6A", [_016A](ld::HexString &pack) { pack.append(_016A); });
		}

		ld::HexString Tlv0144(ld::HexString tgtKey, ld::HexString tlv109,
							  ld::HexString tlv124, ld::HexString tlv128,
							  ld::HexString tlv16e) {
			auto raw = this->makeTLV("01 44", [&](ld::HexString &pack) {
				pack.append(LE.u16(5));
				pack.appendBatch({tlv109, Tlv52D(), tlv124, tlv128, tlv16e});
			});
			raw.tea_encrypt(tgtKey);
			return raw;
		}

		ld::HexString Tlv52D() {
			return this->makeTLV("05 2D", [](ld::HexString &pack) {
				pack.append("0A 16 38 39 39 36 2D 30 31 32 30 30 31 2D 31 37"
							"31 30 30 34 30 31 32 30 12 00 1A 03 52 45 4C 22"
							"07 34 34 34 38 30 38 35 2A 48 67 6F 6F 67 6C 65"
							"2F 73 61 69 6C 66 69 73 68 2F 73 61 69 6C 66 69"
							"73 68 3A 38 2E 31 2E 30 2F 4F 50 4D 31 2E 31 37"
							"31 30 31 39 2E 30 31 31 2F 34 34 34 38 30 38 35"
							"3A 75 73 65 72 2F 72 65 6C 65 61 73 65 2D 6B 65"
							"79 73 32 00 3A 10 64 64 39 31 35 66 64 38 34 30"
							"34 65 31 37 63 65 42 16 38 39 39 36 2D 31 33 30"
							"30 39 31 2D 31 37 31 30 32 30 31 37 34 37 4A 07"
							"34 34 34 38 30 38 35 "_hex);
			});
		}

		ld::HexString Tlv109(std::string imei) {
			auto IMEI = hex_cast(imei);
			IMEI = IMEI.sum_md5();
			return makeTLV("01 09", [&IMEI](ld::HexString &writer) {
				writer.append(IMEI);
			});
		}

		ld::HexString Tlv104(ld::HexString CodeToken1) {
			return makeTLV("01 04", [&CodeToken1](ld::HexString &writer) {
				writer.append(CodeToken1);
			});
		}

	  protected:
		ld::HexString packHeader(ld::HexString &hex);

	  protected:
		uint32_t uin;
		ld::HexString passwordMD5;
		ld::Bin shareKey;
		ld::Bin pubKey;
		ld::Bin privKey;
		std::string imei;

		ld::HexString _016A;
		FunctionShortCut makeTLV = ::tlv::MakeTLV;
	};
}; // namespace tlv

ld::HexString BuildLoginPack(uint32_t uin, ld::HexString passwordMD5,
							 const ld::Bin &shareKey, const ld::Bin &pubKey,
							 const ld::Bin &privKey, ld::DeviceInfo device) {
	tlv::TLVs tlvs{uin, passwordMD5, shareKey, pubKey, privKey, device};
	return tlvs.GetAll();
}

namespace tlv {
	TLVs::TLVs(uint32_t uin, ld::HexString passwordMD5, const ld::Bin &shareKey,
			   const ld::Bin &pubKey, const ld::Bin &privKey,
			   ld::DeviceInfo device)
		: uin(uin), passwordMD5(passwordMD5), shareKey(shareKey),
		  pubKey(pubKey), privKey(privKey), _016A(""), imei(device.imei) {}

	ld::HexString TLVs::GetAll() {
		ld::HexString hex = ""_hex;

		hex.appendBatch({});
		packHeader(hex);
		return hex;
	}

	ld::HexString TLVs::packHeader(ld::HexString &hex) { return hex; }

	TLVs::~TLVs() {}
} // namespace tlv