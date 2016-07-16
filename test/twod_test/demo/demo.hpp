
#pragma once

#include <twod/types/vector.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

class Demo
{
public:
    virtual ~Demo() {}
    
    virtual void enter() {}
    virtual void processEvent(const sf::Event &evt) {}
    virtual void draw(sf::RenderTarget &rt) {}
    virtual void exit() {}
};


class InteractiveDemo : public Demo
{
public:
    void processEvent(const sf::Event &evt) override;
    void draw(sf::RenderTarget &rt) override;
};


class DemoPoints
{
public:
    
    struct Point
    {
        enum State {
            STATE_NONE = 0,
            STATE_MOUSE_OVER = 1<<0,
            STATE_MOUSE_DRAGGING = 1<<1,
        };
        
        Point()
        :   colNormal(100,40,40)
        ,   colOnOver(200,40,40)
        ,   colOnDrag(250,40,40)
        ,   radius(10.f)
        ,   state(STATE_NONE)
        ,   data(nullptr)
        {}
        
        twod::Vec2f pos;
        sf::Color colNormal, colOnOver, colOnDrag;
        float radius;
        State state;
        void *data;
        
        std::function<void(Point&)> onDrag;
        
        sf::Vector2f sfVec() const { return sf::Vector2f(pos.x, pos.y); }
        sf::Color sfCol() const
        {
            if (state & STATE_MOUSE_DRAGGING)
                return colOnDrag;
            if (state & STATE_MOUSE_OVER)
                return colOnOver;
            return colNormal;
        }
        
        void setState(State flag, bool on)
        {
            state = Point::State((state & ~flag) | (on ? flag : 0));
        }
    };
    
    void addPoint(const Point &p) { points_.push_back(p); }
    void clearPoints() { points_.clear(); }
    
    void processEvent(const sf::Event &evt);
    
    void drawLine(sf::RenderTarget &rt);
    void drawPoints(sf::RenderTarget &rt);
    
private:
    
    typedef std::vector<Point> points_t;
    points_t points_;
    
    Point *selectedPt_ = nullptr;
    bool dragging_ = false;
};

/*
class PhysicsDemo : public Demo
{
public:
    virtual ~PhysicsDemo() {}
    
    void init() override;
    void update() override;
    void exit() override;
};
*/

/*
#include "demo/demo.hpp"

void Demo::enter()
{    
}

void Demo::cleanUp()
{   
}

void Demo::exit()
{   
}
*/