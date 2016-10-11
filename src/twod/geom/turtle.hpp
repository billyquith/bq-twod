#pragma once

#include <twod/geom/mesh.hpp>
#include <twod/types/vector.hpp>

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
        Vec2f pos_;
        Vec2f fwd_ = Vec2f(0,-1.f);
        float angle_ = 0.f;             // compass: 360 degs, North = 0, clockwise.
        bool penDown_ = false;
        TurtlePen *pen_;
        
    public:
        
        Turtle(TurtlePen *pen) : pen_(pen) {}
        
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
    };
    
    
    template <typename TVertex>
    class TurtleMesh : public TurtlePen
    {
    public:
        
        typedef Mesh<TVertex> MeshType;

        TurtleMesh(MeshType *m) : mesh_(m) {}
        
//        void drawBegin()
//        void drawEnd();
        void moveTo(const Vec2f& p) { mesh_->
        
    private:
        
        MeshType *mesh_;
        Vec2f last
    };
    
    
} // namespace twod
