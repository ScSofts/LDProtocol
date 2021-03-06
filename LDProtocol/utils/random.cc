#include "../interface.h"
#include "random.h"
#include <random>

namespace ld {
    std::mt19937 *rander = nullptr;
    void Random::Init(){
        if(!rander)
            rander = new std::mt19937();
        rander->seed();
    }

    Bin Random::RandBin(size_t length){
        BinVec vec{};
        for(size_t i = 0; i < length; i++){
            vec.push_back(Random::RandNum<byte>(0, 255));
        }
        return Bin{vec};
    }

   
}