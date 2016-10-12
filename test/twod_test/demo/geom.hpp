#pragma once

#include "demo.hpp"

class GeometryDemo : public InteractiveDemo
{
public:
    typedef InteractiveDemo Parent;
    
    GeometryDemo();
    virtual ~GeometryDemo();
    
    void enter() override;
    void processEvent(const sf::Event &evt) override;
    void draw(sf::RenderTarget &rt) override;
    void exit() override;
    
private:

    DemoPoints dpts_;
};
