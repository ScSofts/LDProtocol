#pragma once
#include <string>
#include <vector>
#include <exception>

#include "../third_party/json/json.h"
namespace ld {
	using byte = unsigned char;
	using Json = nlohmann::json;
};
#include "utils/hexstring.h"
#include "utils/cast.h"
#include "utils/bin.h"
#include "utils/exceptions.h"