#pragma once
#include <vector>
#include <time.h>
#include "RectangleShape.h"

class Utils{
private:
    Utils() {}

public:
    // Check the neighbours of a cell and add up the number of alive cells
    static int checkCell(std::vector<RectangleShape>& neighbours) {
        int sum = 0;
        for(unsigned int i = 0; i < neighbours.size(); i++) { 
            if(neighbours[i].getFillColor() == sf::Color(255,255,255,255)) {
                sum++;
            }
        }
        return sum;
    }
    
    // Generate an array of rectangle shapes with randomized values.
    // n - number of rows and columns
    // width / height - the dimensions of the window
    static void genArray(std::vector<std::vector<RectangleShape>>& grid, int n, unsigned int width, unsigned int height) {
        std::srand(time(nullptr));

        for(int i = 0; i < n; i++) {
            std::vector<RectangleShape> row;
			row.reserve(n);
            for(int j = 0; j < n; j++) {
                RectangleShape cell(sf::Vector2f((float)width / n, (float)height / n));
                cell.setPosition(sf::Vector2f(j* (float)width / n, i* (float)height / n));
                
                cell.value = std::rand() % 2;
                
                if(cell.value) {
                    cell.setFillColor(sf::Color(255,255,255,255));
                } else {
                    cell.setFillColor(sf::Color(0,0,0,255));
                }
                row.emplace_back(cell);
            }
            grid.emplace_back(row);
        }
    }

    // Check each neighbour to see if it will die or live in the next generation
    static void checkNeighbours(std::vector<std::vector<RectangleShape>>& grid, int n) {
        for(unsigned int i = 0; i < grid.size(); i++)
        for(unsigned int j = 0; j < grid.size(); j++) {
            // Store all neighbours of each cell in a vector
            std::vector<RectangleShape> neighbours;
			neighbours.reserve(8);
            for(int k = -1; k < 2; k++)
            for(int l = -1; l < 2; l++) {
                    if(!(k == 0 && l == 0))
                        neighbours.emplace_back(grid[(i+k+n)%n][(j+l+n)%n]);
            }

            // Check neighbours of each cell
            int sum = checkCell(neighbours);
            if(sum < 2 || sum > 3)
                grid[i][j].value = false;  
            else if(sum == 3 && !grid[i][j].value)
                grid[i][j].value = true;
        }
    }

    // Update vector entries (rectangle shapes) to update the fill color of each cell
    static void updateVector(std::vector<std::vector<RectangleShape>>& grid) {
        for(unsigned int i = 0; i < grid.size(); i++)
        for(unsigned int j = 0; j < grid.size(); j++) {
                if(grid[i][j].value)
                    grid[i][j].setFillColor(sf::Color(255,255,255,255));
                else  
                    grid[i][j].setFillColor(sf::Color::Transparent);                    
        }
    }
};