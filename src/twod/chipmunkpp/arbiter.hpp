#pragma once

#include "body.hpp"

#include <chipmunk/chipmunk.h>

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

}
