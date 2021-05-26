#pragma once
#include <random>
namespace ld {
    extern std::mt19937 *rander;
    class Bin;
    class Random {
        public:
        static void Init();

        static Bin RandBin(size_t length);

        template <class TNum = int>
        static TNum RandNum(TNum min, TNum max);
    };
};  // namespace ld

template <class TNum>
TNum ld::Random::RandNum(TNum min, TNum max) {
    std::uniform_int_distribution<TNum> dist(min, max);
    return dist(*rander);
}