#pragma once
#include "IUserInfo.h"
#include <functional>
#include <map>
#include <string>
#include <interface.h>
using TlvMap = std::map<
                        std::string,
                        std::function<
                            void(ld::HexString &)
                            >
                        >;

TlvMap MakeTLVMap(const IUserInfo &userInfo);