
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "MandSet.hpp"

int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Benoit Mandelbrot Set", sf::Style::None);
    
    mandelbrot fractal(window);
    
    sf::Vector2i click = {0,0};
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                fractal.reset();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                fractal.colorSwitch();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
                fractal.saveImage();
            }
            
            if(event.type == sf::Event::MouseButtonPressed){
                click = sf::Mouse::getPosition(window);
                fractal.recentrer(click.x, click.y);
            }
        }
        
        fractal.drawSet();
        window.display();
    }

    return EXIT_SUCCESS;
}
