#pragma once

#include <twod/types/vector.hpp>
#include <handy/vector.hpp>

namespace twod {
    
    
    template <typename TVertex>
    class Mesh
    {
        bq::vector<TVertex> verts_;
        
    public:
        
        typedef TVertex vert_t;
        
        Mesh() = default;
        Mesh(std::size_t nb) { verts_.reserve(nb); }
        
        std::size_t count() const { return verts_.size(); }
        
        void addVert(const TVertex& v) { verts_.emplace_back(v); }
        
        vert_t& operator[] (std::size_t i) { return verts_.at(i); }
        const vert_t& operator[] (std::size_t i) const { return verts_.at(i); }
    };
    
    
    struct Vertex
    {
        Vec2f pos_;
        
        Vec2f& pos() { return pos_; }
    };
    
    typedef Mesh<Vertex> TwodMesh;
    
    
} // namespace twod
