#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

int main() {
    // Constants
    const unsigned int WIDTH = 1000;
    const unsigned int HEIGHT = 1000;
    const int n = 50;

    // Create render window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");

    // Store randomly generated dead and alive cells in 2D vector
    std::vector<std::vector<RectangleShape>> grid = Utils::genArray(n, WIDTH, HEIGHT);

    // Render loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::vector<std::vector<RectangleShape>> next = Utils::checkNeighbours(grid, n);
        
        next = Utils::updateVector(next);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                window.draw(grid.at(i).at(j));
            }
        }

        grid = next;

        window.display();
    }

    return 0;
}
