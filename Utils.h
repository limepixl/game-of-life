#pragma once

#include <vector>
#include <time.h>
#include "RectangleShape.h"

class Utils{
private:
    Utils() {}

public:
    // Check the neighbours of a cell and add up the number of alive cells
    static int checkCell(std::vector<RectangleShape> neighbours) {
        int sum = 0;
        for(int i = 0; i < neighbours.size(); i++) { 
            if(neighbours.at(i).value) {
                sum++;
            }
        }
        return sum;
    }
    
    // Generate an array of rectangle shapes with randomized values.
    // n - number of rows and columns
    // width / height - the dimensions of the window
    static std::vector<std::vector<RectangleShape>> genArray(int n, unsigned int width, unsigned int height) {
        std::srand(time(nullptr));

        std::vector<std::vector<RectangleShape>> rows;

        for(int i = 0; i < n; i++) {
            std::vector<RectangleShape> row;
            for(int j = 0; j < n; j++) {
                RectangleShape cell(sf::Vector2f((float)width / n, (float)height / n));
                cell.setPosition(sf::Vector2f(j* (float)width / n, i* (float)height / n));
                
                cell.value = std::rand() % 2;
                
                if(cell.value) {
                    cell.setFillColor(sf::Color(255,255,255,255));
                } else {
                    cell.setFillColor(sf::Color(0,0,0,255));
                }
                row.push_back(cell);
            }
            rows.push_back(row);
        }

        return rows;
    }

    // Check each neighbour to see if it will die or live in the next generation
    static std::vector<std::vector<RectangleShape>> checkNeighbours(std::vector<std::vector<RectangleShape>> grid, int n) {
        std::vector<std::vector<RectangleShape>> next;
        next = grid;

        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid.size(); j++) {
                // Store all neighbours of each cell in a vector
                std::vector<RectangleShape> neighbours;
                for(int k = -1; k < 2; k++) {
                    for(int l = -1; l < 2; l++) {
                        if(!(k == 0 && l == 0))
                            neighbours.push_back(grid.at((i+k+n)%n).at((j+l+n)%n));
                    }
                }

                // Check neighbours of each cell
                int sum = checkCell(neighbours);
                if(sum < 2 || sum > 3)
                    next.at(i).at(j).value = false;  
                else if(sum == 3 && !grid.at(i).at(j).value)
                    next.at(i).at(j).value = true;
            }
        }

        return next;
    }

    // Update vector entries (rectangle shapes) to update the fill color of each cell
    static std::vector<std::vector<RectangleShape>> updateVector(std::vector<std::vector<RectangleShape>> grid) {
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid.size(); j++) {
                if(grid.at(i).at(j).value)
                    grid.at(i).at(j).setFillColor(sf::Color(255,255,255,255));
                else  
                    grid.at(i).at(j).setFillColor(sf::Color(0,0,0,255));                    
            }
        }

        return grid;
    }
};