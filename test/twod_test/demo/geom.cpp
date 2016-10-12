
#include "geom.hpp"
#include <twod/geom/turtle.hpp>

#include <SFML/Graphics/RenderWindow.hpp>

#include "../imgui/imgui.h"

using namespace twod;


enum DemoMode
{
    MODE_TRIANGULATE,
    MODE_TURTLE,
    MODE_NUM
};
static DemoMode g_mode = MODE_TRIANGULATE;

inline sf::Vector2f conv(Vec2f v) { return sf::Vector2f(v.x, v.y); }


class SfmlTurtlePen : public TurtlePen
{
    typedef Polygons<twod::Vertex> polys_t;
    polys_t polys_;
    
    typedef TriMesh<twod::Vertex, uint16_t> mesh_t;
    mesh_t mesh_;
    
    sf::VertexArray sfverts_;
 
public:
    
    polys_t& polys() { return polys_; }

    void drawBegin() override
    {
        polys_.clear();
        polys_.addPoly(polys_t::polygon_t());
    }
    
    void moveTo(const Vec2f& p) override
    {
        Vertex v;
        v.pos() = p;
        polys_.addVertex(v);
    }
    
    void triangulate()
    {
        mesh_.clear();
        mesh::triangulate(polys_, mesh_);
        printf("polys: %ld, %ld, mesh: %ldv, %ldi\n",
               polys_.size(), polys_[0].size(),
               mesh_.verts().size(), mesh_.indices().size());
   
        sfverts_.clear();
        for (int i=0; i < mesh_.indices().size(); ++i)
        {
            uint32_t col = i * 0x8764fae2;
            col ^= col >> 11;
            sf::Vertex v(conv(mesh_.verts()[mesh_.indices()[i]].pos()), sf::Color(col | 0xff));
            sfverts_.append(v);
        }
    }
    
    void draw(sf::RenderTarget &rt)
    {
        sfverts_.setPrimitiveType(sf::PrimitiveType::Triangles);
        rt.draw(sfverts_);
    }
};


static SfmlTurtlePen g_tpen[MODE_NUM];
static Turtle g_turtle(nullptr);


static void drawShape(Turtle& turt)
{
    turt
        .moveTo(Vec2f(400,400))
        .penDown()
        .repeat(3, [=](Turtle& t, std::size_t i){
            t.forward(100).right(45)
             .forward(50).right(45);
        });
}


GeometryDemo::GeometryDemo()
{
//    DemoPoints::Point pt1, pt2;
//    pt1.pos = Vec2f(500,200);
//    pt2.pos = Vec2f(500,400);
//    dpts_.addPoint(pt1);
//    dpts_.addPoint(pt2);
    
    g_turtle.setPen(&g_tpen[g_mode]);
//    g_tpen[MODE_TRIANGULATE].drawBegin();
}

GeometryDemo::~GeometryDemo()
{
    
}

void GeometryDemo::enter()
{
    
}

void GeometryDemo::processEvent(const sf::Event &evt)
{
    switch (g_mode)
    {
        case MODE_TRIANGULATE:
            if (!dpts_.processEvent(evt))
            {
                switch (evt.type)
                {
                    case sf::Event::MouseButtonPressed:
                    {
                        DemoPoints::Point pt;
                        pt.pos.set(evt.mouseButton.x, evt.mouseButton.y);
                        
                        // new point
                        if (dpts_.size() == 0)
                            g_tpen[MODE_TRIANGULATE].drawBegin();
                        g_tpen[MODE_TRIANGULATE].moveTo(pt.pos);
                        g_tpen[MODE_TRIANGULATE].triangulate();
                        
                        // new interactive point
                        pt.data = (void*) dpts_.size();
                        pt.onDrag = [](DemoPoints::Point &pt)
                        {
                            int index = (int)(ptrdiff_t) pt.data;
                            g_tpen[MODE_TRIANGULATE].polys()[0][index].pos() = pt.pos;
                            g_tpen[MODE_TRIANGULATE].triangulate();
                        };
                        dpts_.addPoint(pt);
                        break;
                    }
                        
                    case sf::Event::KeyPressed:
                        if (evt.key.code == sf::Keyboard::Delete)
                        {
                            dpts_.clearPoints();
                            g_tpen[MODE_TRIANGULATE].polys()[0].clear();
                            g_tpen[MODE_TRIANGULATE].triangulate();
                        }
                        break;
                        
                    default:
                        ;
                }
            }
            break;
            
        default:
            ;
    };
    
    Parent::processEvent(evt);
}

void GeometryDemo::draw(sf::RenderTarget &rt)
{
    ImGui::Begin("Geometry");
    
    ImGui::PushItemWidth(200);
    ImGui::RadioButton("Triangulate", (int*)&g_mode, MODE_TRIANGULATE); //ImGui::SameLine();
    ImGui::RadioButton("Turtle", (int*)&g_mode, MODE_TURTLE); //ImGui::SameLine();
    
    ImGui::End();
    
    switch (g_mode)
    {
        case MODE_TRIANGULATE:
            g_tpen[MODE_TRIANGULATE].draw(rt);
            dpts_.drawLine(rt);
            dpts_.drawPoints(rt);
            break;
            
        case MODE_TURTLE:
            g_tpen[MODE_TURTLE].draw(rt);
            break;
            
    };
}

void GeometryDemo::exit()
{
    
}

    
