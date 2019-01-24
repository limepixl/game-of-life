#include <SFML/Graphics.hpp>
#include <iostream>

enum State
{
	DEAD,
	ALIVE
};

void genArray(std::vector<State>& grid, int rows, int cols);

int checkCell(std::vector<State>& neighbours);

void checkNeighbours(std::vector<State>& grid, std::vector<State>& next, int rows, int cols);

int main()
{
	// Constants
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	const int size = 5;
	const int rows = WIDTH / size;	// Number of cells in each row
	const int cols = HEIGHT / size;	// Number of cells in each collumn

	// Create render window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Game of Life");
	window.setFramerateLimit(60);

	std::vector<sf::RectangleShape> cells;
	std::vector<State> states;

	for(int i = 0; i < rows; i++)
	for(int j = 0; j < cols; j++)
	{
		sf::RectangleShape cell(sf::Vector2f(size, size));
		cell.setPosition(sf::Vector2f((float)size * i, (float)size * j));
		cell.setFillColor(sf::Color(255, 255, 255, 255));
		cells.push_back(cell);
	}

	// Store randomly generated dead and alive cell states
	genArray(states, rows, cols);

	std::vector<State> next;

	// Render loop
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}

		next = states;

		checkNeighbours(states, next, rows, cols);

		window.clear(sf::Color(0, 0, 0, 255));

		for(int i = 0; i < rows; i++)
		for(int j = 0; j < cols; j++)
		{
			int currentPos = i + j * rows;
			if(states[currentPos] == ALIVE)
				window.draw(cells[currentPos]);
		}

		states = next;

		window.display();
	}

	return 0;
}

// Generate an array of rectangle shapes with randomized values.
void genArray(std::vector<State>& grid, int rows, int cols)
{
	std::srand(time(nullptr));

	for(int i = 0; i < rows; i++)
	for(int j = 0; j < cols; j++)
		grid.push_back((State)(std::rand() % 2));
}

// Check the neighbours of a cell and add up the number of alive cells
int checkCell(std::vector<State>& neighbours)
{
	int sum = 0;
	for(unsigned int i = 0; i < neighbours.size(); i++)
	{
		if(neighbours[i] == ALIVE)
		{
			sum++;
		}
	}
	return sum;
}

// Check each neighbour to see if it will die or live in the next generation
void checkNeighbours(std::vector<State>& grid, std::vector<State>& next, int rows, int cols)
{
	for(int i = 0; i < rows; i++)
	for(int j = 0; j < cols; j++)
	{
		int currentPos = i + j * cols;

		// Store all neighbours of each cell in a vector
		std::vector<State> neighbours;
		
		for(int k = -1; k < 2; k++)
		for(int l = -1; l < 2; l++)
		{
			if(!(k == 0 && l == 0))
				neighbours.push_back(grid[((i + l + rows) % rows) * cols + ((j + k + cols) % cols)]);
		}

		// Check neighbours of each cell
		int sum = checkCell(neighbours);
		if(sum < 2 || sum > 3)
			next[j + i * cols] = DEAD;
		else if(sum == 3 && grid[j + i * cols] == DEAD)
			next[j + i * cols] = ALIVE;
	}
}
