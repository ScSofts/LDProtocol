#include "../interface.h"
#include "ecdh.h"
#include <functional>
#include <openssl/ecdh.h>
namespace ld
{
    //RAII Resource Manager
    template<class T = std::function<void(void)>>
    class Guard{
    public:
        Guard(T function);
        ~Guard();
        void cancel();
    protected:
        T function;
        bool should_clean;
    };

    //Translated from EPL code
    static inline KeyGroup ecdh_839(){
        KeyGroup ret = {{},{},{}};
        const Bin tk = bin_cast(
            "04 92 8d 88 50 67 30 88 b3 43 26 4e 0c 6b ac b8 "
            "49 6d 69 77 99 f3 72 11 de b2 5b b7 39 06 cb 08 "
            "9f ea 96 39 b4 e0 26 04 98 b5 1a 99 2d 50 81 3d "
            "a8"_hex);
        auto ec_key = EC_KEY_new_by_curve_name(711);
        if(ec_key){
            //auto delete ec_key
            Guard<> ec_key_guard([&]{
                EC_KEY_free(ec_key);
            });
            auto key = EC_KEY_generate_key(ec_key);
            auto ec_point2 = EC_KEY_get0_public_key(ec_key);
            auto c_priv_key_BN = EC_KEY_get0_private_key(ec_key);
            if(ec_point2){
                auto ec_group = EC_KEY_get0_group(ec_key);
                Bin tmp_key = {};
                tmp_key.assign(40,0u);
                if(
                    EC_POINT_point2oct(
                        ec_group, 
                        ec_point2, 
                        point_conversion_form_t::POINT_CONVERSION_COMPRESSED, 
                        tmp_key.data(), 
                        67,
                        nullptr
                        )
                     > 0){
                    Bin v29 = {};v29.assign(255,0u);
                    auto len = BN_bn2mpi(c_priv_key_BN, v29.data());
                    ret.private_key = BinVec{v29.begin(),v29.begin()+len};//client private key
                    ret.public_key = BinVec{tmp_key.begin(),tmp_key.end()+25};// client public key

                    auto ec_group = EC_KEY_get0_group(ec_key);
                    auto ec_point = EC_POINT_new(ec_group);
                    if(ec_point){
                        Guard<> ec_point_guard([&]{
                            EC_POINT_free(ec_point);
                        });

                        if(
                            EC_POINT_oct2point(
                                ec_group,
                                ec_point,
                                tk.data(),
                                tk.size(),
                                nullptr)
                            >0
                        ){
                            tmp_key.assign(40,0u);
                            auto len = ECDH_compute_key(
                                tmp_key.data(),
                                tmp_key.size(), 
                                ec_point, 
                                ec_key, 
                                nullptr);
                            if(len > 0){
                                ret.share_key = BinVec{tmp_key.begin(),tmp_key.begin() + len};
                            }
                        }
                    }
                }
            }
        }
        return ret;
    }

    //Translated from EPL code
    static inline KeyGroup ecdh_841(){
         KeyGroup ret = {{},{},{}};
         const Bin tk = bin_cast(
            "04 EB CA 94 D7 33 E3 99 B2 DB 96 EA CD D3 F6 9A "
            "8B B0 F7 42 24 E2 B4 4E 33 57 81 22 11 D2 E6 2E "
            "FB C9 1B B5 53 09 8E 25 E3 3A 79 9A DC 7F 76 FE "
            "B2 08 DA 7C 65 22 CD B0 71 9A 30 51 80 CC 54 A8 "
            "2E"_hex);
        auto ec_key = EC_KEY_new_by_curve_name(415);
        if(ec_key){
            Guard<> ec_key_guard([&]{
                EC_KEY_free(ec_key);
            });
            auto key = EC_KEY_generate_key(ec_key);
            auto ec_group = EC_KEY_get0_group(ec_key);
            auto ec_point2 = EC_KEY_get0_public_key(ec_key);

            if(ec_point2){
                Bin tmp_key = {};
                tmp_key.assign(1024,0u);
                auto pk_length = EC_POINT_point2oct(
                            ec_group, 
                            ec_point2, 
                            point_conversion_form_t::POINT_CONVERSION_UNCOMPRESSED, 
                            tmp_key.data(), 
                            65, 
                            nullptr);
                if(pk_length > 0){
                    auto c_priv_key_BN = EC_KEY_get0_private_key(ec_key);
                    auto v29 = Bin{};
                    v29.assign(1024,0u);
                    
                    auto length = BN_bn2mpi(c_priv_key_BN,v29.data());
                    ret.private_key = BinVec{v29.begin(),v29.begin()+length};
                    ret.public_key  = BinVec{tmp_key.begin(),tmp_key.begin()+pk_length};
                    
                    auto ec_point = EC_POINT_new(ec_group);
                    if(
                        EC_POINT_oct2point(
                            ec_group, 
                            ec_point, 
                            tk.data(), 
                            tk.size(), 
                            nullptr
                        )> 0
                    ){
                        tmp_key.assign(16,0u);
                        auto length = ECDH_compute_key(tmp_key.data(), 16, ec_point,ec_key, nullptr);
                        if(length > 0){
                            ret.share_key = tmp_key.sum_md5(); 
                        }
                    }
                }
            }
        }
        return ret;
    }

    KeyGroup MakeECDH(ECDHVersion version){
        switch (version) {
            case ECDHVersion::_839:
                {
                    const auto &tmp = ecdh_839();
                    if(tmp.share_key.empty()){
                        throw ECDHGenKeyFailed(__FILE__,__LINE__);
                    }
                    return tmp;
                }
            break;
            case ECDHVersion::_841:
                {
                    const auto &tmp = ecdh_841();
                    if(tmp.share_key.empty()){
                        throw ECDHGenKeyFailed(__FILE__,__LINE__);
                    }
                    return tmp;
                }
            break;
        }
        return KeyGroup{
            .public_key = {},
            .private_key = {},
            .share_key = {}
        };
    }

    template<class T>
    Guard<T>::Guard(T function):function(function),should_clean(true){

    }

    template<class T>
    Guard<T>::~Guard(){
        if(should_clean && function){
            function();
        }
    }

    template<class T>
    void Guard<T>::cancel(){
        should_clean = false;
    }

    Bin RemakeECDH(
        const Bin & peer_raw_pub_key,
        const Bin & pub_key,
        const Bin & pri_key){
            auto ec_key = EC_KEY_new_by_curve_name(711);
            auto pri_key_bn = BN_mpi2bn (pri_key.data(),pri_key.size(), nullptr);
            auto ret = EC_KEY_set_private_key (ec_key, pri_key_bn);
            BN_free (pri_key_bn);

            auto ec_group = EC_KEY_get0_group(ec_key);
            
            auto share_key_bn = EC_POINT_new (ec_group);
            EC_POINT_oct2point(
                ec_group, 
                share_key_bn, 
                peer_raw_pub_key.data(), 
                peer_raw_pub_key.size(), 
                nullptr);
            
            auto _pub_key = pub_key;
            auto v33 = ECDH_compute_key(_pub_key.data(), 24, share_key_bn, ec_key, nullptr);
            
            Bin share_key{};
            share_key.assign(v33,0u);
            
            share_key = BinVec{_pub_key.begin(),_pub_key.begin() + v33};
            
            EC_KEY_free(ec_key);
            
            return share_key.sum_md5();
        }
 
};