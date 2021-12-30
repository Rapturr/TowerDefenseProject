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
    sf::RectangleShape bullet;
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
    this->bullet.setSize(sf::Vector2f(2,5));
    this->bullet.setFillColor(sf::Color(0,0,0,200));
}

void bullets::move(){
    sf::Vector2f offset;
    offset = target - position;
    position = position + offset;
    bullet.setPosition(position);
}

bullets::~bullets()
{
}

void bullets::drawUnit(sf::RenderWindow *window) {
    window->draw(bullet);
}
