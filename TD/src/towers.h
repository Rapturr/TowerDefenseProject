#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "units.h"
#include "bullets.h"

class towers
{
public:
    sf::CircleShape collisionArea;
    sf::Vector2f position;
    sf::Texture texture;
	sf::Sprite sprite;

    sf::Clock clock;
    sf::Time time;

    float reload;
    float power;
    

    towers(int type, sf::Vector2f position);
    void createBullet(Units unit, std::vector<bullets> bulletvector);
    ~towers();
};


towers::towers(int type, sf::Vector2f position)
{
    this->position = position;
    switch(type){
        case 1://szybka
            reload = 0.5f;
            break;
        case 2://normalna
            reload = 1.f;
            break;
        case 3://wolna
            reload = 2.f;
            break;
    }
    collisionArea.setRadius(50);
}

towers::~towers()
{
}

void towers::createBullet(Units unit, std::vector<bullets> bulletvector)
{
    if(collisionArea.getGlobalBounds().intersects(unit.sprite.getGlobalBounds())){

    }
}

