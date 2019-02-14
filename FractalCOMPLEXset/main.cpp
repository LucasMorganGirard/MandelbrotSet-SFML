
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "MandSet.hpp"

int main(int, char const**)
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Benoit Mandelbrot Set", sf::Style::None);
    
    mandelbrot fractal(window, 400, 400);
    
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
        }
        window.clear();
        fractal.drawSet();
        window.display();
    }

    return EXIT_SUCCESS;
}
