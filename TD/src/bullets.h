#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>

class bullets
{
public:
    sf::Music music;
    sf::Vector2f position;
    sf::Texture texture;
	sf::Sprite sprite;
    sf::Vector2f target;
    float power;

    bullets(sf::Vector2f target,float power);
    void move();
    ~bullets();
};

bullets::bullets(sf::Vector2f target,float power)
{
    this->target = target;
    this->power = power;
}

void bullets::move(){
    sf::Vector2f offset;
    offset = target - position;
    position + offset;
}

bullets::~bullets()
{
}
