
#include "turtle.hpp"

namespace twod {

    
Turtle& Turtle::forward(float d)
{
    pos_ += fwd_ * d;
    
    if (penDown_)
        pen_->moveTo(pos_);

    return *this;
}
    
Turtle& Turtle::right(float da)
{
    angle_ += da;
    fwd_ = Vec2f::compass(angle_);
    return *this;
}

Turtle& Turtle::angleTo(float a)
{
    angle_ = a;
    fwd_ = Vec2f::compass(angle_);
    return *this;
}

Turtle& Turtle::moveTo(Vec2f p)
{
    pos_ = p;

    if (penDown_)
        pen_->moveTo(pos_);
    
    return *this;
}
    
Turtle& Turtle::moveBy(Vec2f p)
{
    pos_ += p;
    
    if (penDown_)
        pen_->moveTo(pos_);

    return *this;
}

Turtle& Turtle::penDown(bool d)
{
    penDown_ = d;
    
    if (penDown_)
    {
        pen_->drawBegin();
        pen_->moveTo(pos_);
    }
    else
    {
        pen_->drawEnd();
    }

    return *this;
}
    
} // namespace twod
