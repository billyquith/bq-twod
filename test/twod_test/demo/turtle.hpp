#pragma once

#include "demo.hpp"

class TurtleDemo : public InteractiveDemo
{
public:
    typedef InteractiveDemo Parent;
    
    TurtleDemo();
    virtual ~TurtleDemo();
    
    void enter() override;
    void processEvent(const sf::Event &evt) override;
    void draw(sf::RenderTarget &rt) override;
    void exit() override;
    
private:

    DemoPoints dpts_;
};
