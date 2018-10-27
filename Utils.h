#pragma once

#include <vector>
#include <time.h>
#include "RectangleShape.h"

class Utils{
private:
    Utils() {}

public:
    static bool checkCell(std::vector<RectangleShape> neighbours) {
        int sum = 0;
        for(int i = 0; i < neighbours.size(); i++) { 
            if(neighbours.at(i).value) {
                sum++;
            }
        }
        if(sum < 2 || sum > 3)
            return false;
        else 
            return true;
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
    static std::vector<std::vector<RectangleShape>> checkNeighbours(std::vector<std::vector<RectangleShape>> grid) {
        std::vector<std::vector<RectangleShape>> next;
        next = grid;

        for(int i = 1; i < grid.size()-1; i++) {
            for(int j = 1; j < grid.size()-1; j++) {
                // Store all neighbours of each cell in a vector
                std::vector<RectangleShape> neighbours(8);
                for(int k = -1; k < 2; k++) {
                    for(int l = -1; l < 2; l++) {
                        if(!(k == 0 && l == 0))
                            neighbours.push_back(grid.at(i+k).at(j+l));
                    }
                }

                // Check neighbours of each cell
                bool state = checkCell(neighbours);
                next.at(i).at(j).value = state;                
            }
        }

        return next;
    }

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