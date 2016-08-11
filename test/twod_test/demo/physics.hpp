
#pragma once
#include "demo.hpp"

#include <twod/physics/physics.hpp>

class PhysicsDemo : public Demo
{
public:
    PhysicsDemo();
    virtual ~PhysicsDemo();
    
    void enter() override;
    void processEvent(const sf::Event &evt) override;
    void update(float dt) override;
    void draw(sf::RenderTarget &rt) override;
    void exit() override;
    
private:
    cpSpace *space_;
    cpBody *fixedBody_;
};
