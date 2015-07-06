#ifndef LIBDHT_CONSTANTS_H_
#define LIBDHT_CONSTANTS_H_

#include <string>

namespace libdht
{
    constexpr char kAddress[] = "0.0.0.0";
    constexpr int kPort = 1337;
    constexpr int kIDSize = 160;
    constexpr int kK = 20;
    constexpr int ka = 3;
    constexpr int kb = 5;
}

#endif // LIBDHT_CONSTANTS_H_
