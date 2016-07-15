#include "arbiter.hpp"

namespace twod {
namespace cp {
    
Arbiter::Arbiter(cpArbiter* a) : arbiter(a)
{
}

Body Arbiter::getBodyA()
{
    cpBody *a, *b;
    cpArbiterGetBodies(arbiter, &a, &b);
    return Body(a);
}

Body Arbiter::getBodyB()
{
    cpBody *a, *b;
    cpArbiterGetBodies(arbiter, &a, &b);
    return Body(b);
}

}}
