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

    bullets(sf::Vector2f target,float power,sf::Vector2f pos);
    void move();
    void drawUnit(sf::RenderWindow *window);
    ~bullets();
};

bullets::bullets(sf::Vector2f target,float power, sf::Vector2f pos)
{
    //std::cout<<"Pif paf"<<std::endl;
    this->target = target;
    this->power = power;
    this->bullet.setSize(sf::Vector2f(10,6));
    this->bullet.setFillColor(sf::Color::Black);
    this->position = pos;
    this->bullet.setPosition(position);
    //std::cout<<"x: "<<pos.x<<"  y: "<<pos.y<<"\n";
}

void bullets::move(){
        sf::Vector2f offset;
        offset = target - position;
        offset.x/=700;
        offset.y/=700;
        position = position + offset;
        bullet.setPosition(position);
}

bullets::~bullets()
{
}

void bullets::drawUnit(sf::RenderWindow *window) {
    //std::cout<<"x: "<<bullet.getPosition().x<<"  y: "<<bullet.getPosition().y<<"\n";
    window->draw(bullet);
}
