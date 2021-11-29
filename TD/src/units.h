#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Units{
private:
	int lives;
	int posx;
	int posy;
	sf::Texture texture;
	sf::Sprite sprite;
	bool lt = false;
	float mapOffset = 0;
	//0-can't move, 1-right, 2-up, 3-down, 4-left
	int movedir = 1;
public:
	//flag 1 - 4 player units, 5-6 enemy units
	Units(int flag){
		switch (flag)
		{
		case 1:
			texture.loadFromFile("../assets/turretb.png");
			lives = 99;
			break;
		case 2:
			texture.loadFromFile("../assets/turretf.png");
			lives = 99;
			break;
		case 3:
			texture.loadFromFile("../assets/turretl.png");
			lives = 99;
			break;
		case 4:
			texture.loadFromFile("../assets/turretr.png");
			lives = 99;
			break;
		case 5:
			texture.loadFromFile("../assets/carrot1.png");
			lives = 1;
			break;
		case 6:
			texture.loadFromFile("../assets/carrot1.png");
			lives = 3;
			break;
		default:
			break;
		}
	}

	void createSprite(int positionx, int positiony){
		posx = positionx;
		posy = positiony;
		sprite.setTexture(texture);
		sprite.setPosition(posx,posy);
	}

	sf::Vector2f getPos(){
		return sprite.getPosition();
	}

	//1-right   2-down   3-left   4-up
	void moveUnit(int direction, int map){
		if(map == 3){
			if(posx > 0 && posx < 159 && posy > 360 && posy < 380){
				posx+=4;
			}
			if(posx > 159 && posx < 170 && posy < 380 && posy > 280){
				posy-=4;
			}
			if(posx > 159 && posx < 440 && posy < 280 && posy > 260){
				posx+=4;
			}
			if(posx > 419 && posx < 424 && posy < 560 && posy > 260){
				posy+=4;
			}
			if(posx > 415 && posx < 480 && posy < 570 && posy > 550){
				posx+=4;
			}
			if(posx > 476 && posx < 484 && posy < 570 && posy > 500){
				posy-=4;
			}
			if(posx > 476 && posx < 544 && posy < 508 && posy > 490){
				posx+=4;
			}
			if(posx > 543 && posx < 548 && posy < 508 && posy > 270){
				posy-=4;
			}
			if(posx > 543 && posx < 632 && posy < 274 && posy > 266){
				posx+=4;
			}
			if(posx > 630 && posx < 636 && posy < 274 && posy > 150){
				posy-=4;
			}
		}
		/*switch (direction)
		{
		case 1:
			posx+=4;
			break;
		case 2:
			posy+=4;
			break;
		case 3:
			posx-=4;
			break;
		case 4:
			posy-=4;
			break;
		
		default:
			break;
		}*/
		sprite.setPosition(posx,posy);
	}

	bool hit(){
		lives--;
		if(lives <= 0){
			texture.~Texture();
			return false;
		}
		return true;
	}

	int checkiffin(){
		if(posx > 400 && !lt){
			return 0;
			lt = true;
		}
		else
			return 0;
	}

	void drawUnit(sf::RenderWindow *window){
		window->draw(sprite);
	}
	~Units() {};
};