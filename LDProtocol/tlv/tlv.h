#pragma once
namespace ld {
    class HexString;
    template<class StructureType>
    HexString MakeTLV(HexString name,const StructureType &data){
        HexString pack = ""_hex;
        #ifdef DEBUG
            if(bin_cast(name).size() != 2){
                throw MakeTLVFailed(__FILE__,__LINE__);
            }
        #endif // DEBUG
        pack.append(name);
        pack.append(NetInt.LittleEidan.u16(sizeof(data)));
        pack.append(data);
        return pack;
    }
};