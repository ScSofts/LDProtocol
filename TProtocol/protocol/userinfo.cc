#include "IUserInfo.h"

void IUserInfo::d2key2tgtgt(){
    this->device.tgtgt.clear();
    this->device.tgtgt.append( bin_cast(this->sig.d2key).sum_md5() );
}