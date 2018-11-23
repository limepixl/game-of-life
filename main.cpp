#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

int main() {
	// Constants
	const unsigned int WIDTH = 600;
	const unsigned int HEIGHT = 600;
	const int n = 200;

	// Create render window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");
	window.setFramerateLimit(60);

	std::vector<std::vector<RectangleShape>> grid;
	grid.reserve(n*n);

	// Store randomly generated dead and alive cells in 2D vector
	Utils::genArray(grid, n, WIDTH, HEIGHT); 

	// Render loop
	while(window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				window.close();
		}

		Utils::checkNeighbours(grid, n);
		Utils::updateVector(grid);

		window.clear(sf::Color(0, 0, 0, 255));

		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			if(grid[i][j].value)
				window.draw(grid[i][j]);
		}

		window.display();
	}

	return 0;
}
