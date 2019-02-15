
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "MandSet.hpp"

int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(1600, 1600), "Benoit Mandelbrot Set", sf::Style::None);
    
    mandelbrot fractal(window, 1600, 1600);
    
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
            
            if(event.type == sf::Event::MouseButtonPressed){
                
            }
        }
        window.clear();
        fractal.drawSet();
        window.display();
    }

    return EXIT_SUCCESS;
}
