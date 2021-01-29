#pragma once
namespace ld{
    struct KeyGroup{
        Bin public_key;
        Bin private_key;
        Bin share_key;
    };
    enum class ECDHVersion{
        _839,
        _841
    };
    KeyGroup MakeECDH(ECDHVersion version);
    Bin RemakeECDH(ECDHVersion version,
        const Bin & peer_raw_pub_key,
        const Bin & pub_key,
        const Bin & pri_key);
};