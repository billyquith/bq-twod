#pragma once

#include <twod/types/vector.hpp>
#include <handy/vector.hpp>
#include "earcut.hpp"

namespace twod {

    
    // Default vertex type
    //  - All vertex types must implement this interface (duck type).
    struct Vertex
    {
        Vec2f pos_;
        
        Vec2f& pos() { return pos_; }
    };

    
    // Simple array of vertices.
    template <typename TVertex>
    class VertexArray
    {
        typedef uint32_t index_t;
        bq::vector<TVertex> verts_;
        
    public:
        
        typedef TVertex vert_t;
        
        VertexArray() = default;
        VertexArray(std::size_t nb) { verts_.reserve(nb); }
        
        std::size_t size() const { return verts_.size(); }
        bool empty() const { return size()==0; }
        void clear() { verts_.clear(); }
        
        void addVert(const TVertex& v) { verts_.emplace_back(v); }
        
        vert_t& operator[] (std::size_t i) { return verts_.at(i); }
        const vert_t& operator[] (std::size_t i) const { return verts_.at(i); }
    };
    

    // Simple array of vertex indices. Refer to VertexArray.
    template <typename I>
    class VertexIndices
    {
    public:
        
        typedef I index_t;

        VertexIndices() = default;
        VertexIndices(std::size_t nb)   { indices_.reserve(nb); }
        
        std::size_t size() const        { return indices_.size(); }
        void clear()                    { indices_.resize(0); }

        void addIndex(index_t i)        { indices_.push_back(i); }
        
        index_t& operator[] (std::size_t i) { return indices_.at(i); }
        const index_t& operator[] (std::size_t i) const { return indices_.at(i); }

    private:
        
        bq::vector<index_t> indices_;
    };
    
    
    // Variable sided polygon indices. Refer to VertexArray.
//    template <typename I, typename P = bq::vector<I>>
//    class PolygonIndices
//    {
//    public:
//        
//        typedef I index_t;
//        typedef P polygon_t;
//        
//        PolygonIndices() = default;
//        PolygonIndices(std::size_t nb)  { indices_.reserve(nb); }
//        
//        std::size_t size() const        { return indices_.size(); }
//        bool empty() const              { return size()==0; }
//        void clear()                    { indices_.resize(0); }
//        
//        void appendIndex(std::size_t polyi, index_t verti) { indices_[polyi].push_back(verti); }
//        
//        index_t& operator[] (std::size_t i) { return indices_.at(i); }
//        const index_t& operator[] (std::size_t i) const { return indices_.at(i); }
//        
//    private:
//        
//        bq::vector<polygon_t> indices_;
//    };


    // Array of polygons using vertices, not indices.
    //  - Polygons are closed loop, no need to duplicate close vertex.
    template <typename TVertex>
    class Polygons
    {
    public:
        
        typedef TVertex vertex_t;
        typedef bq::vector<vertex_t> polygon_t;
        
        Polygons() = default;
        
        std::size_t size() const        { return polys_.size(); }
        bool empty() const              { return size()==0; }
        void clear()                    { polys_.resize(0); }
        
        void addPoly(const polygon_t& p) { polys_.push_back(p); }
        void addVertex(const vertex_t& v) { polys_.back().push_back(v); }
        
        polygon_t& operator[] (std::size_t i) { return polys_.at(i); }
        const polygon_t& operator[] (std::size_t i) const { return polys_.at(i); }
        
        const bq::vector<polygon_t>& polys() const { return polys_; }
        
    private:
        
        bq::vector<polygon_t> polys_;
    };
    
    namespace mesh {
     
        // Data is stored locally as member data.
        template <typename TVertex, typename I>
        class MemberData
        {
        public:
            
            typedef TVertex vertex_t;
            typedef I index_t;
            
            VertexArray<vertex_t>& verts() { return verts_; }
            const VertexArray<vertex_t>& verts() const { return verts_; }
            VertexIndices<index_t>& indices() { return polys_; }
            const VertexIndices<index_t>& indices() const { return polys_; }
            
        private:
                
            VertexArray<vertex_t> verts_;
            VertexIndices<index_t> polys_;
        };

        
        // A triangle mesh which uses a policy to access data.
        //  - Policy allows control over how vertices and indices are generated & stored.
        template <typename TData>
        class TriMesh
        {
        public:
            
            typedef TData data_t;
            
            TriMesh() = default;
            
            VertexArray<typename data_t::vertex_t>& verts() { return data_.verts(); }
            const VertexArray<typename data_t::vertex_t>& verts() const { return data_.verts(); }
            VertexIndices<typename data_t::index_t>& indices() { return data_.indices(); }
            const VertexIndices<typename data_t::index_t>& indices() const {return data_.indices();}
            
            void clear() { verts().clear(); indices().clear(); }
            
            std::size_t triCount() const { return indices().size() / 3; }
            
        private:
            
            TData data_;
        };
        
        
        template <typename TVertexIn, typename TData>
        void triangulate(const Polygons<TVertexIn>& polys, TriMesh<TData>& mesh)
        {
            typedef typename TData::index_t index_t;
            std::vector<index_t> indices = mapbox::earcut<index_t>(polys);

            // copy verts
            for (auto const& p : polys.polys())
                for (auto const& v : p)
                    mesh.verts().addVert(v);
            
            // copy indices
            for (auto i = 0ul; i < indices.size(); ++i)
                mesh.indices().addIndex(indices[i]);
        }

        
    } // mesh

    // Default triangle mesh.
    template <typename TVertex, typename I>
    class TriMesh : public mesh::TriMesh<mesh::MemberData<TVertex, I>>
    {
    };
    
    //---------------------------------------------------------------------------

    
} // namespace twod


namespace mapbox {
namespace util {
        
    template <>
    struct nth<0, twod::Vertex> {
        inline static int64_t get(const twod::Vertex &t) {
            return t.pos_.x;
        };
    };
    
    template <>
    struct nth<1, twod::Vertex> {
        inline static int64_t get(const twod::Vertex &t) {
            return t.pos_.y;
        };
    };

}}


