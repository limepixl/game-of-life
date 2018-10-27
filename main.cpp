#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

int main() {
    // Constants
    const unsigned int WIDTH = 500;
    const unsigned int HEIGHT = 500;
    const int n = 50;

    // Create render window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");

    // Store randomly generated dead and alive cells in 2D vector
    std::vector<std::vector<RectangleShape>> grid = Utils::genArray(n, WIDTH, HEIGHT);

    /* std::vector<std::vector<RectangleShape>> grid;
    for(int i = 0; i < n; i++) {
        std::vector<RectangleShape> row;
        for(int j = 0; j < n; j++) {
            RectangleShape cell(sf::Vector2f((float)WIDTH / n, (float)HEIGHT / n));
            cell.setPosition(sf::Vector2f(j* (float)WIDTH / n, i* (float)HEIGHT / n));
                
            if(i == 15)
                cell.value = 1;
            else
                cell.value = 0;
                
            if(cell.value) {
                cell.setFillColor(sf::Color(255,255,255,255));
            } else {
                cell.setFillColor(sf::Color(0,0,0,255));
            }
            row.push_back(cell);
        }
        grid.push_back(row);
    } */

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
