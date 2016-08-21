
#include <bqutil/bqmath.hpp>

#include <random>
#include <time.h>

static std::mt19937 g_rand;     // global generator

void bq::random::init()
{
    g_rand.seed(time(NULL));
}

uint32_t bq::random::rand()
{
    return g_rand();
}

float bq::random::randf()
{
    auto const t = g_rand() / float(std::mt19937::max() - std::mt19937::min());
    return t;
}




