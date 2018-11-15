#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"

int main() {
	// Constants
	const unsigned int WIDTH = 600;
	const unsigned int HEIGHT = 600;
	const int n = 100;

	// Create render window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");
	window.setFramerateLimit(60);

	std::vector<std::vector<RectangleShape>> grid;

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

		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			window.draw(grid[i][j]);
		}

		window.display();
	}

	return 0;
}
