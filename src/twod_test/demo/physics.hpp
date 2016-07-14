
#pragma once
#include "demo.hpp"

class PhysicsDemo : public Demo
{
public:
    virtual ~PhysicsDemo() {}
    
    void init() override;
    void update() override;
    void cleanUp() override;
};
