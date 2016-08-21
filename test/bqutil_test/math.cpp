
#include <bqutil/bqmath.hpp>
#include "catch.hpp"


TEST_CASE("random")
{
    SECTION("seed")
    {
        bq::random::init();
    }
    
    SECTION("rand uint")
    {
        auto n = bq::random::rand();
        n = bq::random::rand();
        n = bq::random::rand();
        n = bq::random::rand();
    }

    SECTION("randf")
    {
        for (int i=0; i < 1000; ++i)
        {
            auto n = bq::random::randf();
            REQUIRE( 0.f <= n);
            REQUIRE( n <= 1.f );
        }
    }

    SECTION("randf range")
    {
        for (int i=0; i < 1000; ++i)
        {
            auto n = bq::random::randf(10.f, 100.f);
            REQUIRE( 10.f <= n );
            REQUIRE( n <= 100.f );
        }
    }
}
