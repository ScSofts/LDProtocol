#include "tea.h"
#include <time.h>
#include <random>
#include <vector>
#include "../interface.h"

namespace ld {
        using std::exception;

        inline void DbgPrint(const char *what) {
            #ifdef DEBUG
                std::cerr << "ERROR: " << what << std::endl;
            #endif // DEBUG
        }

        inline int get_rand(int min, int max) {
            std::mt19937 rd;
            rd.seed((unsigned)time(0));
            return rd() % max + min;
        }

        template <class ArrayT>
        inline int getArrayLen(const ArrayT &array) {
            return (sizeof(array) / sizeof(array[0]));
        }

        Tea::Tea(){

        }

        Tea::~Tea(){
            
        }

        ld::Bin Tea::Encryption(const ld::Bin &binFrom, ld::Bin key) {
            ld::byte key_bin[16];
            if (key.size() < 16) return {};
            memcpy_s(key_bin, sizeof(key_bin), key.data(), sizeof(key_bin));
            return this->Encryption(binFrom, key_bin);
        }

        Bin Tea::UnEncryption(const Bin &binFrom, Bin key) {
            byte key_bin[16];
            if (key.size() < 16) return {};
            memcpy_s(key_bin, sizeof(key_bin), key.data(), sizeof(key_bin));
            return this->UnEncryption(binFrom, key_bin);
        }

        void Tea::Tobytes(int64_t a, int64_t b, byte out[8]) {
        try {
            out[0] = a >> 24 & 255;
            out[1] = a >> 16 & 255;
            out[2] = a >> 8 & 255;
            out[3] = a & 255;
            out[4] = b >> 24 & 255;
            out[5] = b >> 16 & 255;
            out[6] = b >> 8 & 255;
            out[7] = b & 255;
        } catch (exception &) {
        }
        }

        unsigned int Tea::GetUInt(const Bin &Input, int Ioffset, int intLen) {
        unsigned int ret = 0;
        try {
            int lend = intLen > 4 ? Ioffset + 4 : Ioffset + intLen;
            for (int i = 0; i < lend - 1; i++) {
            ret <<= 8;
            ret |= Input[i];
            }
        } catch (exception &e) {
            DbgPrint(e.what());
        }

        return ret;
        }

        unsigned int Tea::GetUInt(const byte *Input, int Ioffset, int intLen) {
        unsigned int ret = 0;
        try {
            int lend = intLen > 4 ? Ioffset + 4 : Ioffset + intLen;
            for (int i = 0; i < lend - 1; i++) {
            ret <<= 8;
            ret |= Input[i];
            }
        } catch (exception &e) {
            DbgPrint(e.what());
        }

        return ret;
        }

        void Tea::Encipher(const byte *BinInput, const byte *k, const bool Is16Rounds,
                        byte *out) {
        try {
            uint64_t y = GetUInt(BinInput, 1, 4);
            uint64_t z = GetUInt(BinInput, 5, 4);
            uint64_t a = GetUInt(k, 1, 4);
            uint64_t b = GetUInt(k, 5, 4);
            uint64_t c = GetUInt(k, 9, 4);
            uint64_t d = GetUInt(k, 13, 4);
            // cout << y << endl << z << endl << a << endl << b << endl << c << endl <<
            // d << endl;
            int rounds = Is16Rounds ? 16 : 32;
            unsigned int sum = 0;
            for (int i = 0; i < rounds; i++) {
            sum &= 4294967295;
            sum += 2654435769;
            z &= 4294967295;
            y = y + ((((z << 4) + a) ^ (z + sum)) ^ ((z >> 5) + b));
            y &= 4294967295;
            z = z + ((((y << 4) + c) ^ (y + sum)) ^ ((y >> 5) + d));
            }
            Tobytes(y, z, out);
        } catch (const std::exception &e) {
            DbgPrint(e.what());
        }
        }

        bool Tea::Decrypt8bytes(const Bin &input, int offset, int intLen) {
        try {
            for (int i = 0; i < 8; i++) {
            if (m_contextStart + i + 1 > intLen) {
                return true;
            }
            if (offset + m_Crypt + i > int(input.size())) {
                return false;
            }
            m_prePlain[i] ^= input[offset + m_Crypt + i - 1];
            }
            Decipher(m_prePlain, m_Key, true, m_prePlain);

            if (m_prePlain[0] == 0) {
            return false;
            }

            m_contextStart += 8;
            m_Crypt += 8;
            m_Pos = 0;
        } catch (const std::exception &e) {
            DbgPrint(e.what());
        }

        return true;
        }

        void Tea::Encrypt8bytes(const bool Is16Rounds) {
        try {
            m_Header = false;
            m_Pos = 1;

            for (int i = 0; i < 8; i++) {
            if (m_Header) {
                m_Plain[i] ^= m_prePlain[1];
            } else {
                if (m_preCrypt + i + 1 > int(m_out.size()))  // 0+0+1 0+1  0+1+1  0+2
                {
                return;
                }
                m_Plain[i] ^= m_out[m_preCrypt + i];
            }
            }

            byte Crypted[8] = {0};
            Encipher(m_Plain, m_Key, Is16Rounds, Crypted);
            for (int i = 0; i < getArrayLen(Crypted); i++) {
            if (m_Crypt + i + 1 > int(m_out.size())) {
                return;
            }
            m_out[m_Crypt + i] = Crypted[i];
            }

            for (int i = 0; i < 8; i++) {
            if (m_Crypt + i + 1 > int(m_out.size())) {
                return;
            }
            m_out[m_Crypt + i] ^= m_prePlain[i];
            }

            for (int i = 0; i < getArrayLen(m_Plain); i++) {
            if (i + 1 > getArrayLen(m_prePlain)) {
                return;
            }
            m_prePlain[i] = m_Plain[i];
            }

            m_preCrypt = m_Crypt;
            m_Crypt += 8;
            m_Pos = 0;
            m_Header = false;
        } catch (const std::exception &e) {
            DbgPrint(e.what());
        }
        }

        Bin Tea::Encryption(const Bin &binFrom, byte (&binTkye)[16]) {
            Bin ret;
            hashTea(binFrom, binTkye, 1, true, ret);
            return ret;
        }

        Bin Tea::UnEncryption(const Bin &binFrom, byte (&binTkye)[16]) {
            m_preCrypt = 0;
            m_Crypt = 0;
            m_Pos = 0;
            m_padding = 0;
            Bin _;
            m_out.swap(_);
            Bin ret;
            if(!UnhashTea(binFrom, binTkye, 1, true, ret)){
                throw TeaDecryptFailed(__FILE__,__LINE__);
            }

            return ret;
        }
        void Tea::Decipher(byte *BinInput, byte (&binTkye)[16], bool Is16Rounds,
                        byte *out) {
            try {
                int64_t sum = 3816266640;
                int64_t y = GetUInt(BinInput, 1, 4);
                int64_t z = GetUInt(BinInput, 5, 4);
                int64_t a = GetUInt(binTkye, 1, 4);
                int64_t b = GetUInt(binTkye, 5, 4);
                int64_t c = GetUInt(binTkye, 9, 4);
                int64_t d = GetUInt(binTkye, 13, 4);
                int rounds = 0;
                int64_t test = 0;
                if (Is16Rounds) {
                rounds = 16;
                } else {
                rounds = 32;
                }

                for (int i = 0; i < rounds; i++) {
                test = (((y << 4) + c) ^ (y + sum)) ^ ((y >> 5) + d);
                z -= test;
                z &= 4294967295;
                test = (((z << 4) + a) ^ (z + sum)) ^ ((z >> 5) + b);
                y -= test;
                y &= 4294967295;
                sum -= 2654435769;
                sum &= 4294967295;
                }
                Tobytes(y, z, out);
            } catch (const std::exception &e) {
                DbgPrint(e.what());
            }
            }
            void Tea::Decipher(const Bin &BinInput, byte (&binTkye)[16], bool Is16Rounds,
                            byte *out) {
            try {
                int64_t sum = 3816266640;
                int64_t y = GetUInt(BinInput, 1, 4);
                int64_t z = GetUInt(BinInput, 5, 4);
                int64_t a = GetUInt(binTkye, 1, 4);
                int64_t b = GetUInt(binTkye, 5, 4);
                int64_t c = GetUInt(binTkye, 9, 4);
                int64_t d = GetUInt(binTkye, 13, 4);
                int rounds = 0;
                int64_t test = 0;
                if (Is16Rounds) {
                rounds = 16;
                } else {
                rounds = 32;
                }

                for (int i = 0; i < rounds; i++) {
                test = (((y << 4) + c) ^ (y + sum)) ^ ((y >> 5) + d);
                z -= test;
                z &= 4294967295;
                test = (((z << 4) + a) ^ (z + sum)) ^ ((z >> 5) + b);
                y -= test;
                y &= 4294967295;
                sum -= 2654435769;
                sum &= 4294967295;
                }
                Tobytes(y, z, out);
            } catch (const std::exception &e) {
                DbgPrint(e.what());
            }
        }

        bool Tea::UnhashTea(const Bin &binFrom, byte (&binTkye)[16], int offset, bool Is16Rounds, Bin &out)
        {
            Bin o_m;
            o_m.resize(offset + 7);
            int o_intLen = binFrom.size();
            Decipher(binFrom, binTkye, true, m_prePlain);
            m_Pos = m_prePlain[0] & 7;
            int o_count = o_intLen - m_Pos - 10;
            m_out.resize(o_count);

            m_preCrypt = 0;
            m_Crypt = 8;
            m_contextStart = 8;
            m_Pos++;
            m_padding = 1;

            while (m_padding <= 2) {
                if (m_Pos < 8) {
                m_Pos++;
                m_padding++;
                }
                if (m_Pos == 8) {
                o_m = binFrom;
                Decrypt8bytes(binFrom, offset, o_intLen);
                }
            }

            int i2 = 0;
            while (o_count != 0) {
                if (m_Pos < 8) {
                if (i2 <= int(m_out.size())) {
                    if (m_Pos <= getArrayLen(m_prePlain)) {
                    if (offset + m_preCrypt + m_Pos <= int(o_m.size())) {
                        m_out[i2] =
                            o_m[offset - 1 + m_preCrypt + m_Pos] ^ m_prePlain[m_Pos];
                    } else {
                        return false;
                    }
                    } else {
                    return false;
                    }
                } else {
                    return false;
                }
                i2++;
                o_count--;
                m_Pos++;
                }

                if (m_Pos == 8) {
                o_m = binFrom;
                m_preCrypt = m_Crypt - 8;
                Decrypt8bytes(binFrom, offset, o_intLen);
                }
            }

            for (int i = 0; i < 7; i++) {
                if (m_Pos < 8) {
                m_Pos++;
                if (m_Pos == 8) {
                    o_m = binFrom;
                    Decrypt8bytes(binFrom, offset, o_intLen);
                }
                }
            }
            out.swap(m_out);
            return true;
            }
            void Tea::hashTea(const Bin &binFrom, byte (&binTkye)[16], int offset,
                            bool Is16Rounds, Bin &out) {
            m_Header = true;
            _memccpy(m_Key, binTkye, 0, getArrayLen(m_Key));
            m_Pos = 1;
            m_padding = 0;
            m_Crypt = 0;
            m_preCrypt = 0;

            int intlen = binFrom.size();
            m_Pos = (intlen + 10) % 8;
            m_Pos = m_Pos ? 8 - m_Pos : m_Pos;

            m_out.resize(intlen + m_Pos + 9 + 1);
            m_Plain[0] = (get_rand(1000, 5000) & 248) ^ m_Pos;
            for (int i = 0; i < m_Pos; i++) {
                m_Plain[i + 1] = get_rand(1000, 5000) & 255;
            }
            memset(m_prePlain, 0, getArrayLen(m_prePlain));
            m_Pos += 1;
            m_padding = 1;
            do {
                if (m_Pos < 8) {
                m_Plain[m_Pos] = get_rand(1000, 5000) & 255;
                m_Pos++;
                m_padding++;
                } else {
                Encrypt8bytes(Is16Rounds);
                }
            } while (m_padding < 3);

            int i2 = offset - 1;
            while (intlen > 0) {
                if (m_Pos < 8) {
                m_Plain[m_Pos] = binFrom[i2];
                m_Pos++;
                intlen--;
                i2++;
                } else {
                Encrypt8bytes(Is16Rounds);
                }
            }

            m_padding = 1;
            while (m_padding < 8) {
                if (m_Pos < 8) {
                m_Plain[m_Pos] = 0;
                m_padding++;
                m_Pos++;
                }
                if (8 == m_Pos) {
                Encrypt8bytes(Is16Rounds);
                }
            }
            out.swap(m_out);
        }
};  // namespace ld