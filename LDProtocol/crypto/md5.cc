#include "../interface.h"
#include "md5.h"
#include <openssl/md5.h>

namespace ld{
  Bin MD5::sum(const Bin &data){
      auto md5_ctx = new MD5_CTX;
      MD5_Init(md5_ctx);
      MD5_Update(md5_ctx,data.data(), data.size());
      byte md5_result[MD5_DIGEST_LENGTH];
      MD5_Final(md5_result, md5_ctx);
      delete md5_ctx;
      Bin ret{};
      ret = BinVec{md5_result,md5_result+MD5_DIGEST_LENGTH};
      return ret;
  }
};