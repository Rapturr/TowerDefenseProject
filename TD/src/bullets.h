#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    sf::Vector2f offset;
    int targetid;

    float power;

    bullets(sf::Vector2f target,float power,sf::Vector2f pos,int targetid);
    void move();
    void drawUnit(sf::RenderWindow *window);
    ~bullets();
};

bullets::bullets(sf::Vector2f target,float power, sf::Vector2f pos, int tid)
{   
    targetid = tid;
    target.x+=10;
    target.y+=10;
    //std::cout<<"Pif paf"<<std::endl;
    this->target = target;
    this->power = power;
    this->bullet.setSize(sf::Vector2f(6,6));
    this->bullet.setFillColor(sf::Color::Black);
    this->position = pos;
    this->bullet.setPosition(position);
    offset = target - position;
    offset.x/=50;
    offset.y/=50;
    //std::cout<<"x: "<<pos.x<<"  y: "<<pos.y<<"\n";
}

void bullets::move(){
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
