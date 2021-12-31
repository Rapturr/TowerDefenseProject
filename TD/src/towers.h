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
    
    int target;

    towers(int type, sf::Vector2f position);
    void createBullet(Units unit, std::vector<bullets> *bulletvector, int tgt);
    void drawUnit(sf::RenderWindow *window);
    ~towers();
};


towers::towers(int type, sf::Vector2f positionm)
{
    position = positionm;
    texture.loadFromFile("../assets/turretb.png");

    sprite.setTexture(texture);
    switch(type){
        case 1://szybka
            reload = 0.5f;
            power = 1;
            break;
        case 2://normalna
            reload = 1.f;
            power = 3;
            break;
        case 3://wolna
            reload = 2.f;
            power = 5;
            break;
    }
    target = -1;
    collisionArea.setRadius(50);
}

towers::~towers()
{
}

void towers::createBullet(Units unit, std::vector<bullets> *bulletvector, int tgt)
{
    
    if(unit.exists && target != 10000)
        target = tgt;
    else if(!unit.exists)
        target = -1;
    if(collisionArea.getGlobalBounds().intersects(unit.sprite.getGlobalBounds())){
        std::cout<<"target: "<<target<<"\n";
        bullets bullet(unit.getPos(),this->power, sprite.getPosition());
        if(clock.getElapsedTime().asMilliseconds() >= 250){
            bulletvector->push_back(bullet);
            clock.restart();
        }
    }
}

void towers::drawUnit(sf::RenderWindow *window) {
    window->draw(sprite);
}

