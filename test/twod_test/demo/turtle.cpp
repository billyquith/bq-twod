
#include "turtle.hpp"
#include <twod/geom/turtle.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../imgui/imgui-SFML.h"
#include "../imgui/imgui.h"

using namespace twod;

struct SfmlVertex
{
    //  Vector2f  position;
    //  Color     color;
    //  Vector2f  texCoords;
    sf::Vertex sf;
    
    Vec2f& pos()        { return *(Vec2f*)&sf.position; }
    uint32_t& colour()  { return *(uint32_t*)&sf.color; }
    Vec2f& uv()         { return *(Vec2f*)&sf.texCoords; }
};

typedef Mesh<SfmlVertex> SfmlMesh;

class SfmlTurtlePen : public TurtlePen
{
public:
    SfmlMesh mesh_;
    
    void moveTo(const Vec2f& p) override
    {
        SfmlVertex v;
        v.pos() = p;
        mesh_.addVert(v);
    }
};

static void drawMesh(sf::RenderTarget &rt, const SfmlMesh& sm)
{
    const auto nv = sm.count();
    sf::VertexArray va(sf::PrimitiveType::LinesStrip, nv);
    for (auto i = 0ul; i < nv; ++i)
        va[i] = sm[i].sf;
    rt.draw(va);
}

static SfmlTurtlePen g_tpen;
static Turtle g_turtle(&g_tpen);


static void drawShape(Turtle& turt)
{
    turt
        .moveTo(Vec2f(400,400))
        .penDown()
        .repeat(50, [](Turtle& t, std::size_t i){
            t.forward(20 + i*10).right(90);
        });
}


TurtleDemo::TurtleDemo()
{
    DemoPoints::Point pt1, pt2;
    pt1.pos = Vec2f(500,200);
    pt2.pos = Vec2f(500,400);
    dpts_.addPoint(pt1);
    dpts_.addPoint(pt2);
    
    drawShape(g_turtle);
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
    drawMesh(rt, g_tpen.mesh_);
    
    dpts_.drawLine(rt);
    dpts_.drawPoints(rt);
}

void TurtleDemo::exit()
{
    
}

    
