
#include "turtle.hpp"

#include "../imgui/imgui-SFML.h"
#include "../imgui/imgui.h"

using namespace twod;

TurtleDemo::TurtleDemo()
{
    DemoPoints::Point pt1, pt2;
    pt1.pos = Vec2f(500,200);
    pt2.pos = Vec2f(500,400);
    dpts_.addPoint(pt1);
    dpts_.addPoint(pt2);
}

TurtleDemo::~TurtleDemo()
{
    
}

void TurtleDemo::enter()
{
    
}

void TurtleDemo::processEvent(const sf::Event &evt)
{
    dpts_.processEvent(evt);
    
    Parent::processEvent(evt);
}

void TurtleDemo::draw(sf::RenderTarget &rt)
{
    dpts_.drawLine(rt);
    dpts_.drawPoints(rt);
}

void TurtleDemo::exit()
{
    
}

    
