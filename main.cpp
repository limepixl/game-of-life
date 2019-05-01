#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

// Count the neighbors of each cell
int countNeighbors(bool grid[], int index, int cols)
{
	int sum = 0;
	for(int i = -1; i < 2; i++)
	for(int k = -1; k < 2; k++)
	{
		if(i == 0 && k == 0)
			continue;

		if(grid[index + i*cols + k])
			sum++;
	}

	return sum;
}

int main()
{
	// Seed randomness
	srand(time(nullptr));

	// Constants
	const int PIXLWIDTH = 2;
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	const int COLS = WIDTH / PIXLWIDTH;
	const int ROWS = HEIGHT / PIXLWIDTH;

	// Grid of cells
	bool grid[ROWS * COLS];
	for(int i = 0; i < COLS; i++)
	for(int j = 0; j < ROWS; j++)
	{
		grid[i + j*COLS] = rand() % 2;
	}

	// Window creation
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");
	window.setFramerateLimit(60);

	// Rectangle to be drawn
	sf::RectangleShape cell(sf::Vector2f(PIXLWIDTH, PIXLWIDTH));
	cell.setFillColor(sf::Color::White);

	// Temporary grid
	bool copy[ROWS * COLS];
    while (window.isOpen())
    {
		// Event processing
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

		for(int i = 0; i < COLS; i++)
		for(int j = 0; j < ROWS; j++)
		{
			// If the cell is alive draw it
			if(grid[i + j*COLS])
			{
				cell.setPosition(i*PIXLWIDTH, j*PIXLWIDTH);
				window.draw(cell);
			}

			// Calculate offspring
			int n = countNeighbors(grid, i + j*COLS, COLS);
			if((n == 2 || n == 3) && grid[i + j*COLS])
				copy[i + j*COLS] = true;
			else if((n==3) && !grid[i + j*COLS])
				copy[i+j*COLS] = true;
			else
				copy[i+j*COLS] = false;
		}

		// Set temp grid as main one
		for(int i = 0; i < COLS; i++)
		for(int j = 0; j < ROWS; j++)
			grid[i + j*COLS] = copy[i + j*COLS];

        window.display();
    }

    return 0;
}
