
#pragma once

#include <cstdlib>

//#define BQ_ABORT(FMT, ...) \
//    do{ fpr(FMT, ##__VA_ARGS__); ::abort(); } while(0)
#define BQ_ABORT(FMT) do{ fprintf(stderr, FMT); std::abort(); } while(0)

// TODO - which format type? %s {}
// TODO - include format.h?

//#define BQ_ASSERT(TEST, FMT, ...) \
//    if (!(TEST)) BQ_ABORT(#TEST " failed. " FMT, ##__VA_ARGS__)
#define BQ_ASSERT(TEST) \
    if (!(TEST)) BQ_ABORT(#TEST " failed. ")

