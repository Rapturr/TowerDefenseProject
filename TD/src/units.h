#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

class Units{
private:
	int lives;
	int posx;
	int posy;
	sf::Texture texture;
	bool lt = false;
	float mapOffset = 0;
	int movedir = 1;
	bool switcher;
	int lastx;
	int lasty;
	sf::Clock clock;
public:
	sf::Sprite sprite;
	Units(int flag){
		clock.restart();
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
			texture.loadFromFile("../assets/tomato.png");
			lives = 99;
			break;
		case 5:
			texture.loadFromFile("../assets/carrot.png");
			lives = 1;
			break;
		case 6:
			texture.loadFromFile("../assets/potato.png");
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

	void moveUnit(int direction, int map){
		if(map == 3){
			switcher = true;
			posx = 0*(1280/32);
			posy = 12*(720/18);
			movHelper(5);
			movHelper(-3);
			movHelper(8);
			/*movHelper(9);
			movHelper(2);
			movHelper(-2);
			movHelper(2);
			movHelper(-7);
			movHelper(3);
			movHelper(-4);
			movHelper(1);
			movHelper(-1);
			movHelper(3);
			movHelper(9);
			movHelper(3);
			movHelper(3);
			movHelper(3);
			movHelper(-5);
			movHelper(1);*/
			
		}
	}

	void movHelper(int n){
		n *=40;
		if(n != 0){
			if(!switcher){
				if(n > 0){
					for(int i = 0; i<n; i++){
						posy += 1;
					}
				}
				else{
					for(int i = 0; i>n; i--){
						posy -= 1;
					}
				}
				switcher = !switcher;
			}
			else{
				if(n > 0){
					for(int i = 0; i<n; i++){
						posx += 1;
					}
				}
				else{
					for(int i = 0; i>n; i--){
						posx -= 1;
					}
				}
				switcher = !switcher;
			}
			sprite.setPosition(posx,posy);
			clock.restart();
		}
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