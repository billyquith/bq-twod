#pragma once

#include <twod/types/vector.hpp>

namespace twod {
    
    template <typename T, typename NI = T>
    struct Rect
    {
        typedef Vec2<T, NI> Vec;
        
        Vec tl, br;
        
        Rect() {}
        Rect(T l, T t, T r, T b) : tl(l,t), br(r,b) {}
        Rect(const Vec &tl_, const Vec &br_) : tl(tl_), br(br_) {}
        
        template <typename OT, typename ONI>
        Rect(const Rect<OT,ONI> &other) : tl(Vec2<T,NI>(other.tl)), br(Vec2<T,NI>(other.br)) {}

        void set(const Vec &tl_, const Vec &br_) { tl = tl_, br = br_; }
        
        void set(T left, T top, T right, T bottom) {
            set(Vec(left,top), Vec(right,bottom));
        }
        
        T width() const     { return br.x - tl.x; }
        T height() const    { return br.y - tl.y; }
        Vec size() const    { return Vec(width(), height()); }
        T area() const      { const T sz(size()); return sz.x * sz.y; }
        
        T left() const      { return tl.x; }
        T right() const     { return br.x; }
        T top() const       { return tl.y; }
        T bottom() const    { return br.y; }
        
        Vec centre() const  { return Vec((tl.x+br.x)/2, (tl.y+br.y)/2); }
        
        Vec topLeft() const       { return tl; }
        Vec topRight() const      { return Vec(br.x, tl.y); }
        Vec bottomLeft() const    { return Vec(tl.x, br.y); }
        Vec bottomRight() const   { return br; }
        
        Rect operator += (const Rect &other) {
            tl += other.tl;
            br += other.br;
            return *this;
        }
        
        Rect operator += (const Vec& vec) { return moveBy(vec); }
        
        Rect operator + (const Rect& other) {
            return Rect(tl + other.tl, br + other.br);
        }

        Rect operator + (const Vec& vec) {
            return Rect(tl + vec, br + vec);
        }
        
        Rect moveTo(const Vec& vec) {  // absolute
            const Vec sz(size());
            tl = vec;
            br = tl + sz;
            return *this;
        }
        
        Rect moveBy(const Vec& vec) {  // relative
            tl += vec;
            br += vec;
            return *this;
        }

        Rect scaleAbout(const Vec& o, NI scale) {
            tl = (tl - o) * scale + o;
            br = (br - o) * scale + o;
            return *this;
        }

        bool contains(const Vec& pt) const {
            return  !(pt.x < tl.x || pt.x > br.x || pt.y < tl.y || pt.y > br.y);
        }

        bool contains(const Rect& r) const {
            return contains(r.tl) && contains(r.br);
        }

        // Ensure this inside container. Fails if container smaller.
        bool clampInside(const Rect& container)
        {
            const auto szThis(size()), szCont(container.size());
            
            if (tl.x < container.tl.x)
                tl.x = container.tl.x, br.x = container.tl.x + szThis.x;
            else if (br.x > container.br.x)
                tl.x = container.br.x - szThis.x, br.x = container.br.x;

            if (tl.y < container.tl.y)
                tl.y = container.tl.y, br.y = container.tl.y + szThis.y;
            else if (br.y > container.br.y)
                tl.y = container.br.y - szThis.y, br.y = container.br.y;

            return szThis.x <= szCont.x && szThis.y <= szCont.y;
        }
        
        // Ensure origin top-left.
        Rect& normalise()
        {
            if (tl.x > br.x) std::swap(tl.x, br.x);
            if (tl.y > br.y) std::swap(tl.y, br.y);
            return *this;
        }
    };

    typedef Rect<int32_t, float> Recti32;
    typedef Recti32 Recti;
    
    typedef Rect<float, float> Rectf32;
    typedef Rectf32 Rectf;
    
}
