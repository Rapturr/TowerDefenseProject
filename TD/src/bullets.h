#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>

class bullets
{
public:
    sf::Vector2f position;
    sf::Texture texture;
	sf::Sprite sprite;
    sf::Vector2f target;
    float power;

    bullets(sf::Vector2f target,float power);
    void move();
    void drawUnit(sf::RenderWindow *window);
    ~bullets();
};

bullets::bullets(sf::Vector2f target,float power)
{
    std::cout<<"Pif paf"<<std::endl;
    this->target = target;
    this->power = power;
}

void bullets::move(){
    sf::Vector2f offset;
    offset = target - position;
    position = position + offset;
}

bullets::~bullets()
{
}

void bullets::drawUnit(sf::RenderWindow *window) {
    window->draw(sprite);
}
