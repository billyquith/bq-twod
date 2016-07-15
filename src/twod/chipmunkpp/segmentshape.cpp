#include "segmentshape.hpp"

namespace twod {
namespace cp {
    
SegmentShape::SegmentShape(std::shared_ptr<Body> body, Vect a, Vect b, Float radius)
:   Shape(cpSegmentShapeNew(body ? (*body) : (cpBody*) 0, a, b, radius), body)
{
}

}}
