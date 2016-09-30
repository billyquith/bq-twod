#pragma once

#include <chipmunk.h>
#include <twod/types/vector.hpp>

namespace twod {

    inline cpVect conv(const Vec2f v) { return cpv(v.x, v.y); };
    inline Vec2f  conv(const cpVect v) { return Vec2f(v.x, v.y); };
    
    // Help manage a Chipmunk space.
    class Physics
    {
        cpSpace *space_;
    public:
        
        Physics() : space_(NULL) {}
        ~Physics();
        
        bool init();
        void update(float dt);

        cpSpace* space() { return space_; }
    };
    
} // twod
