
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include "imgui/imgui-SFML.h"
#include "imgui/imgui.h"

enum class Demo : int
{
    None,
    Overlap,
    Physics
};


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 1024), "BQ Twod Test");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    
    bool showUiDemo = false;
    Demo demoChoice = Demo::None;
    
    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        
        ImGui::SFML::Update(deltaClock.restart());
        
        ImGui::Begin("Twod");
        ImGui::RadioButton("Overlap", (int*)&demoChoice, (int)Demo::Overlap);
        ImGui::RadioButton("Physics", (int*)&demoChoice, (int)Demo::Physics);
        ImGui::Separator();
        ImGui::Checkbox("Show demo", &showUiDemo);
        ImGui::End();
        
        if (showUiDemo)
            ImGui::ShowTestWindow();
        
        window.clear(sf::Color(80,80,80));
        ImGui::Render();
        window.display();
    }
    
    ImGui::SFML::Shutdown();
    return 0;
}