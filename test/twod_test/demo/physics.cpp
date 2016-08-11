
#include "physics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace twod;


static inline sf::Color sfCol(const cpSpaceDebugColor& c)
{
    return sf::Color(c.r * 255, c.g * 255, c.b * 255, c.a * 255);
}

static inline cpSpaceDebugColor RGBAColor(float r, float g, float b, float a){
    cpSpaceDebugColor color = {r, g, b, a};
    return color;
}

static inline cpSpaceDebugColor LAColor(float l, float a){
    cpSpaceDebugColor color = {l, l, l, a};
    return color;
}

static inline sf::Vector2f v2f(cpVect v) { return sf::Vector2f(v.x, v.y); }

struct DrawData
{
    sf::RenderTarget *rt;
};

static void drawCircle(cpVect pos, cpFloat angle, cpFloat radius,
                       cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor,
                       cpDataPointer data)
{
    auto dd = (DrawData*)data;
    sf::CircleShape circ;
    circ.setPosition(pos.x - radius, pos.y - radius);
    circ.setRadius(radius);
    circ.setFillColor(sfCol(fillColor));
    circ.setOutlineColor(sfCol(outlineColor));
    dd->rt->draw(circ);
}

static void drawSeg(cpVect a, cpVect b, cpSpaceDebugColor color, cpDataPointer data)
{
    auto dd = (DrawData*)data;
    sf::VertexArray va(sf::PrimitiveType::LinesStrip, 2);
    va[0].position = sf::Vector2f(a.x, a.y);
    va[1].position = sf::Vector2f(b.x, b.y);
    dd->rt->draw(va);
}

static void drawFatSeg(cpVect a, cpVect b, cpFloat radius,
                       cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor,
                       cpDataPointer data)
{
    cpVect n = cpvnormalize(cpvrperp(cpvsub(b, a)));
    cpVect t = cpvrperp(n);
    
    const float lineScale = 1.f;
    cpFloat half = 1.0f/lineScale;
    cpFloat r = radius + half;
    if(r <= half)
    {
        r = half;
        fillColor = outlineColor;
    }
    
    cpVect nw = (cpvmult(n, r));
    cpVect tw = (cpvmult(t, r));

    auto dd = (DrawData*)data;
    
    // fill
    sf::VertexArray va(sf::PrimitiveType::TrianglesStrip, 4);
    va[0].position = v2f(cpvsub(b, cpvadd(nw, tw))); // { 1.0, -1.0}
    va[1].position = v2f(cpvadd(b, cpvsub(nw, tw))); // { 1.0,  1.0}
    va[2].position = v2f(cpvsub(a, cpvsub(nw, tw))); // {-1.0, -1.0}
    va[3].position = v2f(cpvadd(a, cpvadd(nw, tw))); // {-1.0,  1.0}
    for (int i=0; i<4; ++i) va[i].color = sfCol(fillColor);
    dd->rt->draw(va);
    
    // outline
    va.setPrimitiveType(sf::LinesStrip);
    va.resize(5);
    for (int i=0; i<5; ++i) va[i].color = sfCol(outlineColor);
    va[3].position = v2f(cpvsub(a, cpvsub(nw, tw))); // {-1.0, -1.0}
    va[2].position = v2f(cpvadd(a, cpvadd(nw, tw))); // {-1.0,  1.0}
    va[4].position = v2f(cpvsub(b, cpvadd(nw, tw))); // { 1.0, -1.0} - back to start
    dd->rt->draw(va);
}

static void drawPoly(int count, const cpVect *verts,
                     cpFloat radius, cpSpaceDebugColor outlineColor, cpSpaceDebugColor fillColor,
                     cpDataPointer data)
{
    auto dd = (DrawData*)data;
    sf::VertexArray va(sf::PrimitiveType::TrianglesFan, count);
    for (int i=0; i < count; ++i)
    {
        va[i].position = sf::Vector2f(verts[i].x, verts[i].y);
    }
    dd->rt->draw(va);
}

static void drawDot(cpFloat size, cpVect pos, cpSpaceDebugColor color, cpDataPointer data)
{
    auto dd = (DrawData*)data;
    sf::RectangleShape rect;
    rect.setPosition(pos.x, pos.y);
    rect.setSize(sf::Vector2f(size, size));
    rect.setOutlineColor(sfCol(color));
    dd->rt->draw(rect);
}

static cpSpaceDebugColor colForShape(cpShape *shape, cpDataPointer data)
{
    if(cpShapeGetSensor(shape)){
        return LAColor(1.0f, 0.1f);
    } else {
        cpBody *body = cpShapeGetBody(shape);
        
        if(cpBodyIsSleeping(body)){
            return LAColor(0.2f, 1.0f);
//        } else if(body->sleeping.idleTime > shape->space->sleepTimeThreshold) {
//            return LAColor(0.66f, 1.0f);
        } else {
            uint32_t val = (uint32_t)(ptrdiff_t)shape;
            
            // scramble the bits up using Robert Jenkins' 32 bit integer hash function
            val = (val+0x7ed55d16) + (val<<12);
            val = (val^0xc761c23c) ^ (val>>19);
            val = (val+0x165667b1) + (val<<5);
            val = (val+0xd3a2646c) ^ (val<<9);
            val = (val+0xfd7046c5) + (val<<3);
            val = (val^0xb55a4f09) ^ (val>>16);
            
            float r = (float)((val>>0) & 0xFF);
            float g = (float)((val>>8) & 0xFF);
            float b = (float)((val>>16) & 0xFF);
            
            float max = (float)cpfmax(cpfmax(r, g), b);
            float min = (float)cpfmin(cpfmin(r, g), b);
            float intensity = (cpBodyGetType(body) == CP_BODY_TYPE_STATIC ? 0.15f : 0.75f);
            
            // Saturate and scale the color
            if(min == max){
                return RGBAColor(intensity, 0.0f, 0.0f, 1.0f);
            } else {
                float coef = (float)intensity/(max - min);
                return RGBAColor((r - min)*coef, (g - min)*coef, (b - min)*coef, 1.0f);
            }
        }
    }
}

static cpSpaceDebugDrawOptions g_ddOpt;

PhysicsDemo::PhysicsDemo()
:   space_(nullptr)
,   fixedBody_(nullptr)
{
    space_ = cpSpaceNew();
    cpSpaceSetIterations(space_, 30);
    cpSpaceSetGravity(space_, cpv(0, 300));
    cpSpaceSetSleepTimeThreshold(space_, 0.5f);
    cpSpaceSetCollisionSlop(space_, 0.5f);
 
    
    fixedBody_ = cpBodyNewStatic();
    auto sh = cpSegmentShapeNew(fixedBody_, cpv(10.f,1000.f), cpv(1000.f,1000.f), 3.f); // bottom
    cpSpaceAddShape(space_, sh);
    cpShapeSetElasticity(sh, 0.3f);
    sh = cpSegmentShapeNew(fixedBody_, cpv(10.f,1000.f), cpv(10.f,10.f), 3.f); // left
    cpSpaceAddShape(space_, sh);
    cpShapeSetElasticity(sh, 0.3f);
    sh = cpSegmentShapeNew(fixedBody_, cpv(1000.f,1000.f), cpv(1000.f,10.f), 3.f); // right
    cpSpaceAddShape(space_, sh);
    cpShapeSetElasticity(sh, 0.3f);

    // debug draw config
    memset(&g_ddOpt, 0, sizeof(g_ddOpt));
    g_ddOpt.drawCircle = &drawCircle;
    g_ddOpt.drawSegment = &drawSeg;
    g_ddOpt.drawFatSegment = &drawFatSeg;
    g_ddOpt.drawPolygon = &drawPoly;
    g_ddOpt.drawDot = &drawDot;
    g_ddOpt.flags = (cpSpaceDebugDrawFlags)(CP_SPACE_DEBUG_DRAW_SHAPES
                    | CP_SPACE_DEBUG_DRAW_CONSTRAINTS
                    | CP_SPACE_DEBUG_DRAW_COLLISION_POINTS);
    g_ddOpt.shapeOutlineColor =     {1.f,0,0,1.f};
    g_ddOpt.constraintColor =       {0.f,1,0,1.f};
    g_ddOpt.collisionPointColor =   {1.f,0,1.f,1.f};
    g_ddOpt.colorForShape = &colForShape;
}

PhysicsDemo::~PhysicsDemo()
{
    cpSpaceFree(space_);
}

void PhysicsDemo::enter()
{
    
}

void PhysicsDemo::processEvent(const sf::Event &evt)
{
    if (evt.type == sf::Event::MouseButtonPressed)
    {
        const float r = 20.f;
        
        auto body = cpBodyNew(10.f, cpMomentForCircle(10.f, 0.f, r, cpvzero));
        cpBodySetPosition(body, cpv(evt.mouseButton.x, evt.mouseButton.y));
        
        auto sh = cpCircleShapeNew(body, r, cpvzero);
        cpShapeSetElasticity(sh, 0.5f);
        
        cpSpaceAddBody(space_, body);
        cpSpaceAddShape(space_, sh);
    }
}

void PhysicsDemo::update(float dt)
{
    cpSpaceStep(space_, dt);
}

void PhysicsDemo::draw(sf::RenderTarget &rt)
{
    DrawData dd = { &rt };
    g_ddOpt.data = &dd;
    cpSpaceDebugDraw(space_, &g_ddOpt);
}

void PhysicsDemo::exit()
{
    
}

    
