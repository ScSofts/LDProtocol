#pragma once
#include "../interface.h"

namespace ld {
    class Tea {
    public:
        Tea();
        ~Tea();
        Bin Encryption(const Bin &binFrom, Bin key);

        Bin UnEncryption(const Bin &binFrom, Bin key);

        Bin Encryption(const Bin &binFrom,
                            byte (&binTkye)[16]);  //Encode
        Bin UnEncryption(const Bin &binFrom,
                            byte (&binTkye)[16]);  //Encode
    protected:
        void Tobytes(int64_t a, int64_t b, byte out[8]);

        unsigned int GetUInt(const Bin &Input, int Ioffset, int intLen);

        unsigned int GetUInt(const byte *Input, int Ioffset, int intLen);

        void Encipher(const byte *BinInput, const byte *k,
                        const bool Is16Rounds, byte *out);

        bool Decrypt8bytes(const Bin &input, int offset, int intLen);

        void Encrypt8bytes(const bool Is16Rounds);

        void Decipher(byte *BinInput, byte (&binTkye)[16], bool Is16Rounds,
                        byte *out);

        void Decipher(const Bin &BinInput, byte (&binTkye)[16],
                        bool Is16Rounds, byte *out);

        bool UnhashTea(const Bin &binFrom, byte (&binTkye)[16], int offset,
                        bool Is16Rounds, Bin &out);

        void hashTea(const Bin &binFrom, byte (&binTkye)[16], int offset,
                    bool Is16Rounds, Bin &out);

        byte m_Plain[8] = {0};     //指向当前的明文块
        byte m_prePlain[8] = {0};  //指向前面一个明文块
        int m_Crypt = 0;
        int m_preCrypt = 0;  //当前加密的密文位置和上一次加密的密文块位置，他们相差8
        int m_Pos = 0;       //当前处理的加密解密块的位置
        int64_t m_padding = 0;     //填充数
        byte m_Key[16] = {0};  //秘钥
        bool m_Header =
            false;  //用于加密时，表示当前是否是第一个8字节块，因为加密算法是反馈的
        int64_t m_contextStart = 0;
        Bin m_out;
    };
};  // namespace ld