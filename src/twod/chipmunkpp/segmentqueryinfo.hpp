#pragma once

#include "types.hpp"

#ifndef _MSC_VER
#pragma GCC visibility push(default)
#endif

namespace twod {
namespace cp {
    
    /// Segment query info struct
    struct SegmentQueryInfo
    {
        Float t; // The normalized distance along the query segment in the range [0, 1].
        Vect n;  // The normal of the surface hit.
        
        SegmentQueryInfo() : t(0) {}        

        inline Vect hitPoint(Vect start, Vect end)
        {
            return Vect::lerp(start, end, t);
        }

        inline Float hitDist(Vect start, Vect end)
        {
            return Vect::dist(start, end)*t;
        }
    };

}}

#ifndef _MSC_VER
#pragma GCC visibility pop
#endif
