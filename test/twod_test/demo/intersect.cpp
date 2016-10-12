
#include "intersect.hpp"

#include "../imgui/imgui.h"

using namespace twod;

IntersectDemo::IntersectDemo()
{
    DemoPoints::Point pt1, pt2;
    pt1.pos = Vec2f(200,200);
    pt2.pos = Vec2f(500,400);
    dpts_.addPoint(pt1);
    dpts_.addPoint(pt2);
}

IntersectDemo::~IntersectDemo()
{
    
}

void IntersectDemo::enter()
{
    
}

void IntersectDemo::processEvent(const sf::Event &evt)
{
    dpts_.processEvent(evt);
    
    Parent::processEvent(evt);
}

void IntersectDemo::draw(sf::RenderTarget &rt)
{
    dpts_.drawLine(rt);
    dpts_.drawPoints(rt);
}

void IntersectDemo::exit()
{
    
}

    
