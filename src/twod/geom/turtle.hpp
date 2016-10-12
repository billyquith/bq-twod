#pragma once

#include <twod/geom/mesh.hpp>
#include <twod/types/vector.hpp>
#include <functional>

namespace twod {
    
    
    class TurtlePen
    {
    public:
        virtual void drawBegin() {}
        virtual void drawEnd() {}
        virtual void moveTo(const Vec2f& p) {}
    };
    
    
    class Turtle
    {
        TurtlePen *pen_;
        Vec2f pos_;
        Vec2f fwd_;
        float angle_ = 0.f;             // compass: 360 degs, North = 0, clockwise.
        bool penDown_ = false;
        
    public:
        
        Turtle(TurtlePen *pen) : pen_(pen), fwd_(Vec2f::compass(0)) {}
        
        void setPen(TurtlePen *pen)     { pen_ = pen; }
        
        Vec2f pos() const               { return pos_; }
        float angle() const             { return angle_; }  // compass
        
        Turtle& forward(float d);
        Turtle& back(float d)           { return forward(-d); }

        Turtle& left(float da)          { return right(-da); }
        Turtle& right(float da);
        Turtle& angleTo(float a);
        
        Turtle& moveTo(Vec2f p);
        Turtle& moveBy(Vec2f p);
        
        Turtle& penDown(bool d = true);
        Turtle& penUp()                 { return penDown(false); }
        
        // fn == void(Turtle&, size_t index)
        template <typename F>
        Turtle& repeat(size_t times, F&& fn)
        {
            std::function<void(Turtle&, std::size_t)> wfn(fn);
            for (std::size_t i=0; i < times; ++i)
                wfn(*this, i);
            return *this;
        }
    };
    
    
//    template <typename TVertex>
//    class TurtleMeshPen : public TurtlePen
//    {
//    public:
//        
//        typedef TVertex vert_t;
//        typedef PolyMesh<vert_t, unsigned short> mesh_t;
//
//        TurtleMeshPen(mesh_t *m) : mesh_(m) {}
//        
//        void moveTo(const Vec2f& p)
//        {
//            vert_t v = {p};
//            mesh_->addVert(v);
//        }
//        
//    private:
//        
//        mesh_t *mesh_;
//    };
    
    
} // namespace twod
