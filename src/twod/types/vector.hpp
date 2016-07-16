#pragma once

#include <cmath>
#include <stdint.h>

namespace twod {
    
    namespace detail {
    
        template <typename T, typename Enable = void> struct VectorTraits;

        template <typename T>
        struct VectorTraits<T, typename std::enable_if<std::is_integral<T>::value>::type>
        {
            static inline bool compare(T x1, T y1, T x2, T y2) {
                return x1==x2 && y1==y2;
            }
        };

        template <typename T>
        struct VectorTraits<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
        {
            constexpr static T c_eps = 1e-5;
            static inline bool fltcmp(T a, T b) { return std::abs(a-b) < T(c_eps); }

            static inline bool compare(T x1, T y1, T x2, T y2) {
                return fltcmp(x1, x2) && fltcmp(y1, y2);
            }
        };
        
    } // namespace detail

    template <typename T, typename NI = T>
    struct Vec2
    {
        T x,y;

        Vec2() : x(0), y(0) {}

        Vec2(T x_, T y_) : x(x_), y(y_) {}
        
        template <typename U>
        Vec2(const Vec2<U> &o) : x(T(o.x)), y(T(o.y)) {}
        
        bool operator == (const Vec2 &o) const {
            return detail::VectorTraits<T>::compare(x, y, o.x, o.y);
        }
        
        void set(T x_, T y_)                    { x = x_, y = y_; }
        
        Vec2 operator + (const Vec2 &o) const   { return Vec2(x + o.x, y + o.y); }
        void operator += (const Vec2 &o)        { x += o.x, y += o.y; }
        
        Vec2 operator - () const                { return Vec2(-x, -y); }
        Vec2 operator - (const Vec2 &o) const   { return Vec2(x - o.x, y - o.y); }
        void operator -= (const Vec2 &o)        { x -= o.x, y -= o.y; }
        
        Vec2 operator * (T s) const             { return Vec2(x*s, y*s); }
        void operator *= (T s)                  { x *= s, y *= s; }
        Vec2 operator * (const Vec2 &o) const   { return Vec2(x * o.x, y * o.y); }
        void operator *= (const Vec2 &o)        { x *= o.x, y *= o.y; }
        
        Vec2 operator / (T s) const             { return Vec2(x/s, y/s); }
        void operator /= (T s)                  { x /= s, y /= s; }
        
        T lengthSquared() const                 { return x*x + y*y; }
        NI length() const                       { return std::sqrt(NI(x*x + y*y)); }

        NI setLength(NI newLen)
        {
            const NI vlen = length();
            const NI scale = newLen / vlen;
            x *= scale;
            y *= scale;
            return vlen;    // Old length.
        }
        
        // normalise in-place
        NI normalise()
        {
            const NI vlen = length();
            const NI invlen = NI(1.0) / vlen;
            x *= invlen;
            y *= invlen;
            return vlen;    // Old length.
        }

        T dot(const Vec2 &o) const {
            return x * o.x + y * o.y;
        }

        static Vec2 polar(NI rad);               // anti-clkws from x-axis.
        static Vec2 compass(NI degrees);         // clkws from north.

        // Rotate vector origin anti-clkws by rad.
        void rotate(NI aclkRad);

        // Rotate around centre point anti-clkws by rad.
        void rotateAround(const Vec2 &centre, NI aclkRad);
    };

    typedef Vec2<int16_t, float> Vec2i16;
    typedef Vec2<int32_t, float> Vec2i32;
    typedef Vec2i32 Vec2i;
    
    typedef Vec2<float, float> Vec2f32;
    typedef Vec2<double, double> Vec2f64;
    typedef Vec2f32 Vec2f;
    
}
