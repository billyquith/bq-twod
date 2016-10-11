#pragma once

#include <handy/vector.hpp>

namespace twod {
    
    
    template <typename TVertex>
    class Mesh
    {
        bq::vector<TVertex> verts_;
        
    public:
        Mesh() = default;
        Mesh(std::size_t nb) { verts_.reserve(nb); }
        
        void addVert(const TVertex& v) { verts_.emplace_back(v); }
    };
    
    
    struct Vertex
    {
        Vec2f pos_;
        
        Vec2f& pos() { return pos_; }
    };
    
    typedef Mesh<Vertex> TwodMesh;
    
    
} // namespace twod
