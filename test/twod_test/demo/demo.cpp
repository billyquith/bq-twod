
#include "demo.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cassert>


void InteractiveDemo::processEvent(const sf::Event &evt)
{
}

void InteractiveDemo::draw(sf::RenderTarget &rt) {}


void DemoPoints::drawLine(sf::RenderTarget &rt)
{
    const int nb = points_.size();
    sf::VertexArray va(sf::PrimitiveType::LinesStrip, nb);
    for (int i=0; i < nb; ++i)
    {
        va[i].position = points_[i].sfVec();
    }
    rt.draw(va);
}

void DemoPoints::drawPoints(sf::RenderTarget &rt)
{
    const int nb = points_.size();
    for (int i=0; i < nb; ++i)
    {
        const float r = points_[i].radius;
        sf::CircleShape cs(r);
        cs.setPosition(points_[i].sfVec() - sf::Vector2f(r,r));
        cs.setFillColor(points_[i].sfCol());
        rt.draw(cs);
    }
}

void DemoPoints::processEvent(const sf::Event &evt)
{
    switch (evt.type)
    {
        case sf::Event::MouseMoved:
        {
            const twod::Vec2f mp(evt.mouseMove.x, evt.mouseMove.y);
            for (auto& pt : points_)
            {
                const bool over = (pt.pos - mp).length() <= pt.radius;
                pt.setState(Point::STATE_MOUSE_OVER, over);
            }
            
            if (dragging_)
            {
                assert(selectedPt_ != nullptr);
                selectedPt_->pos = mp;
            }
            break;
        }
            
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        {
            const bool pressed = evt.type == sf::Event::MouseButtonPressed;
            const twod::Vec2f mp(evt.mouseButton.x, evt.mouseButton.y);
            
            if (evt.mouseButton.button == sf::Mouse::Button::Left)
            {
                if (pressed)
                {
                    selectedPt_ = nullptr;
                    for (auto& pt : points_)
                    {
                        const bool over = (pt.pos - mp).length() <= pt.radius;
                        if (over)
                        {
                            selectedPt_ = &pt;
                            dragging_ = true;
                            pt.pos = mp;
                            pt.setState(Point::STATE_MOUSE_DRAGGING, true);
                            break;
                        }
                    }
                }
                else
                {
                    dragging_ = false;
                    if (selectedPt_)
                        selectedPt_->setState(Point::STATE_MOUSE_DRAGGING, false);
                    selectedPt_ = nullptr;
                }
            }
        }
            
        default:
            ;
    }
}
