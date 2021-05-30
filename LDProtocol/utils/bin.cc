#include "../interface.h"
#include "bin.h"
#include "../crypto/tea.h"
#include "../crypto/md5.h"
#include <exception>
namespace ld{

    const Bin& Bin::operator=(const BinVec &vec){
        this->std::vector<byte>::operator=(vec);
        return *this;
    }

    void Bin::tea_encrypt(const HexString & key){
        (*this) = Tea{}.Encryption(*this,bin_cast(key));
    }

    void Bin::tea_encrypt(const Bin &key){
        (*this) = Tea{}.Encryption(*this,key);
    }

    void Bin::tea_decrypt(const HexString & key){
        try{
            (*this) = Tea{}.UnEncryption(*this,bin_cast(key));
        }catch(std::exception e){
            throw TeaDecryptFailed(__FILE__,__LINE__);
        }
    }

    void Bin::tea_decrypt(const Bin &key){
        try{
            (*this) = Tea{}.UnEncryption(*this,key);
        }catch(std::exception e){
            throw TeaDecryptFailed(__FILE__,__LINE__);
        }
    }

    Bin Bin::sum_md5()const{
        return MD5{}.sum(*this);
    }
};