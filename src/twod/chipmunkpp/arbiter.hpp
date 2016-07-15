#pragma once

#include "body.hpp"

#include <chipmunk/chipmunk.h>

namespace twod {
namespace cp {
    
    class Arbiter
    {
    public:

        Arbiter(cpArbiter*);
        Body getBodyA();
        Body getBodyB();

    private:

        cpArbiter* arbiter;
    };

}}
