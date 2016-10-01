
#include "physics.hpp"

bool twod::Physics::init()
{
    space_ = cpSpaceNew();
    
    cpVect gravity = cpv(0, 100);
    cpSpaceSetGravity(space_, gravity);
    
    return true;
}

twod::Physics::~Physics()
{
    cpSpaceFree(space_);
}

void twod::Physics::update(float dt)
{
    cpSpaceStep(space_, dt);
}
