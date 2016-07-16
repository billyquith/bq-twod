
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
        sf::CircleShape cs(6.f);
        cs.setPosition(points_[i].sfVec() - sf::Vector2f(3.f,3.f));
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
                pt.state = Point::State(
                    (pt.state & ~Point::STATE_MOUSE_OVER) | (over ? Point::STATE_MOUSE_OVER : 0));
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
                            break;
                        }
                    }
                }
                else
                {
                    dragging_ = false;
                    selectedPt_ = nullptr;
                }
            }
        }
            
        default:
            ;
    }
}
