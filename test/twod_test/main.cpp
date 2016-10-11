
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

#include "demo/intersect.hpp"
#include "demo/physics.hpp"
#include "demo/turtle.hpp"

#define BQ_ARRAY_SIZE(A) (sizeof(A)/sizeof(A[0]))

enum class DemoType : int
{
    None,
    Intersect,
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "BQ Twod Test");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    
    struct { const char *name; Demo *demo; } demos[] =
    {
        { "Turtle", new TurtleDemo() },
        { "Physics", new PhysicsDemo() },
        { "Intersect", new IntersectDemo() }
    };
    const auto nbDemos = BQ_ARRAY_SIZE(demos);
    
    int demoChoice = 0, lastDemoChoice = demoChoice;
    bool showUiDemo = false;
    sf::Clock deltaClock;
    twod::Vec2i mousePos;
    const int minDt = 1000/60;
    
    demos[demoChoice].demo->enter();
    while (window.isOpen())
    {
//        while (deltaClock.getElapsedTime().asMilliseconds() < minDt)
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                demos[demoChoice].demo->processEvent(event);
                ImGui::SFML::ProcessEvent(event);
                
                switch (event.type)
                {
                    case sf::Event::Closed:
                        window.close();
                        break;
                        
                    case sf::Event::MouseMoved:
                        mousePos.set(event.mouseMove.x, event.mouseMove.y);
                        break;
                        
                    default:
                        ;
                }
            }
        }
        
        // update
        sf::Time tm = deltaClock.restart();
        demos[demoChoice].demo->update(tm.asSeconds());
        ImGui::SFML::Update(tm);
        
        ImGui::Begin("Twod");
        for (int i=0; i < nbDemos; ++i)
        {
            ImGui::RadioButton(demos[i].name, &demoChoice, i);
        }
        ImGui::Separator();
        ImGui::Text("Mouse (%d,%d)", mousePos.x, mousePos.y);
        ImGui::Separator();
        ImGui::Checkbox("Show demo", &showUiDemo);
        ImGui::End();
        
        if (showUiDemo)
            ImGui::ShowTestWindow();
        
        window.clear(sf::Color(80,80,80));
        demos[demoChoice].demo->draw(window);
        ImGui::Render();
        window.display();

        if (lastDemoChoice != demoChoice)
        {
            demos[lastDemoChoice].demo->exit();
            demos[demoChoice].demo->enter();
        }
        lastDemoChoice = demoChoice;
    }
    
    ImGui::SFML::Shutdown();
    return 0;
}