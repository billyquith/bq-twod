
#pragma once
#include "demo.hpp"

class PhysicsDemo : public Demo
{
public:
    virtual ~PhysicsDemo() {}
    
    void enter() override;
    void draw(sf::RenderTarget &rt) override;
    void exit() override;
};
