#include <SFML/Graphics.hpp>

class RectangleShape: public sf::RectangleShape{
    using sf::RectangleShape::RectangleShape;

public:
    bool value;
};
