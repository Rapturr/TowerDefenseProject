#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>
#include <SFML/Audio.hpp>

class Units{
private:
	int lives;
	int posx;
	int posy;
	int currentmap;
	sf::Texture texture;
	bool lt = false;
	float mapOffset = 0;
	int movedir = 1;
	bool switcher;
	//1-carrot,2-tomato,3-potato
	int type;
	int lastx;
	int lasty;
	//sf::Music music;
	sf::Clock clock;
	std::vector<char> moves;
	int currentmove;
	sf::SoundBuffer sb;
	sf::Sound sound;
public:
	bool exists;
	sf::Sprite sprite;
	Units(int flag){
		clock.restart();
		exists = true;
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
			lives = 5;
			sb.loadFromFile("../assets/Sounds/TOMATO.wav");
			sound.setVolume(50);
			break;
		case 5:
			texture.loadFromFile("../assets/carrot.png");
			lives = 1;
			sb.loadFromFile("../assets/Sounds/CARROT.wav");
			break;
		case 6:
			texture.loadFromFile("../assets/potato.png");
			lives = 3;
			sb.loadFromFile("../assets/Sounds/POTATO.wav");
			sound.setVolume(70);
			break;
		default:
			break;
		}
		currentmove = 0;
		sound.setBuffer(sb);
	}

	void createSprite(int positionx, int positiony){
		posx = positionx;
		posy = positiony;
		sprite.setTexture(texture);
		sprite.setPosition(posx,posy);
	}
	void createSprite(){
		sprite.setTexture(texture);
		sprite.setPosition(0,0);
	}

	sf::Vector2f getPos(){
		return sprite.getPosition();
	}

	void clearMoves(){
		currentmove = 0;
		moves.clear();
	}

	void fillMoveTab(int direction, int map){
		currentmap = map;
		if(map == 3){
			switcher = true;
			posx = 0*(1280/32);
			posy = 12*(720/18);
			sprite.setPosition(posx,posy);
			movHelper(5);
			movHelper(-3);
			movHelper(8);
			movHelper(9);
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
			movHelper(1);
		}
		else if(map == 4){
			switcher = false;
			posx = 5*(1280/32);
			posy = 2*(720/18);
			sprite.setPosition(posx,posy);
			movHelper(5);
			movHelper(-3);
			movHelper(10);
			movHelper(4);
			movHelper(-5);
			movHelper(3);
			movHelper(-3);
			movHelper(3);
			movHelper(3);
			movHelper(3);
			movHelper(5);
			movHelper(4);
			movHelper(-10);
			movHelper(-3);
			movHelper(-3);
			movHelper(7);
			movHelper(7);
			movHelper(3);
			movHelper(5);
			movHelper(3);
			movHelper(-3);
			movHelper(2);
		}
		else if(map == 5){
			switcher = true;
			posx = 0*(1280/32);
			posy = 5*(720/18);
			sprite.setPosition(posx,posy);
			movHelper(7);
			movHelper(10);
			movHelper(3);
			movHelper(-5);
			movHelper(2);
			movHelper(3);
			movHelper(3);
			movHelper(-6);
			movHelper(1);
			movHelper(-1);
			movHelper(2);
			movHelper(-2);
			movHelper(3);
			movHelper(13);
			movHelper(4);
			movHelper(-4);
			movHelper(2);
			movHelper(-4);
			movHelper(3);
			movHelper(-5);
			movHelper(1);
		}
	}
	void moveUnits(){
		if(clock.getElapsedTime().asMilliseconds() >= 25){
			if(moves[currentmove] == 'r'){
				posx += 4;
				currentmove++;
			}
			else if(moves[currentmove]=='l'){
				posx -= 4;
				currentmove++;
			}
			else if(moves[currentmove]=='d'){
				posy += 4;
				currentmove++;
			}
			else if(moves[currentmove]=='u'){
				posy -= 4;
				currentmove++;
			}
			sprite.setPosition(posx,posy);
			clock.restart();
		}
	}
	void movHelper(int n){
		n *=10;
		if(n != 0){
			if(!switcher){
				if(n > 0){
					for(int i = 0; i<n; i++){
						moves.push_back('d');
					}
				}
				else{
					for(int i = 0; i>n; i--){
						moves.push_back('u');
					}
				}
				switcher = !switcher;
			}
			else{
				if(n > 0){
					for(int i = 0; i<n; i++){
						moves.push_back('r');
					}
				}
				else{
					for(int i = 0; i>n; i--){
						moves.push_back('l');
					}
				}
				switcher = !switcher;
			}
		}
	}

	bool hit(){
		lives--;
		if(lives <= 0){
			disappear();
			texture.~Texture();
			return false;
		}
		return true;
	}

	int checkiffin(){
		/*if(posx > 1200){
			std::cout<<"position x: "<<posx<<"  y: "<<posy<<std::endl;
		}*/
		if(currentmap == 3){
			if(posx == 31*(1280/32) && posy == 11*(720/18) && !lt){
				lt = true;
				return 1;
			}
			else
				return 0;
		}
		else if(currentmap == 4){
			if(posx == 31*(1280/32) && posy == 13*(720/18) && !lt){
				lt = true;
				return 1;
			}
			else
				return 0;
		}
		else if(currentmap == 5){
			if(posx == 31*(1280/32) && posy == 4*(720/18) && !lt){
				lt = true;
				return 1;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	void disappear(){
		sound.play();
		exists = false;
		posx = 0;
		posy = 0;
	}
	void drawUnit(sf::RenderWindow *window){
		if(exists)
			window->draw(sprite);
	}
	~Units() {};
};