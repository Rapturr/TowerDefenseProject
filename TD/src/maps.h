#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include "units.h"
#include "towers.h"
#include <windows.h>
#include <mmsystem.h>

class WindowChoice{
private:
//1-menu | 2-level selection | 3-level 1 | 4-level 2 | 5-level 3 |
	int choice;
	sf::Texture texture;
	sf::Texture turrettexture;
	sf::Texture textureButtonStart;
	sf::Texture textureButtonQuit;
	sf::Texture textureButtonMap1;
	sf::Texture textureButtonMap2;
	sf::Texture textureButtonMap3;

	sf::Sprite sprite;
	sf::Sprite spritebuttonstart;
	sf::Sprite spritebuttonquit;
	sf::Sprite spritebuttonmap1;
	sf::Sprite spritebuttonmap2;
	sf::Sprite spritebuttonmap3;
	sf::Sprite unitTurret1;

	sf::Vector2u vec2;
	sf::Vector2u vec;

	std::vector<Units*> unitvector;
	std::vector<towers*> allyunitvector;
    std::vector<bullets> bulletvector;

	sf::RectangleShape units;

	sf::Font font;
	sf::Text text;
	sf::Text textmoney;
	sf::Text textpoints;

	int cash;
	int playerLife;
	int points;
	//0-czysto, 1-droga
	int placeCheck[32][18];
	int offset;
	int index = 0;
	bool switcher;
	int lastx;
	int lasty;
	int unitIt;

	sf::Clock myclock;
	sf::Clock tmpclock;
	
	void setmap(){
		switch (choice)
		{
		case 1:
			//texture.loadFromFile("../assets/m1.jpg", sf::IntRect(0,0,1920*1.5,1080*1.5));
			texture.loadFromFile("../assets/m1.jpg");
			//texture.loadFromFile("../assets/m1.jpg", sf::IntRect(0,0,600,400));
			break;
		case 2:
			texture.loadFromFile("../assets/m1.jpg");
			break;
		case 3:
			texture.loadFromFile("../assets/map1.png");
			break;
		case 4:
			texture.loadFromFile("../assets/map2.png");
			break;
		case 5:
			texture.loadFromFile("../assets/map3.png");
			break;
		default:
			std::cout<<"Error"<<std::endl;
			break;
		}
		textureButtonStart.loadFromFile("../assets/start.png");
		textureButtonQuit.loadFromFile("../assets/quit.png");
		
		textureButtonMap1.loadFromFile("../assets/mapbutton1.png");
		textureButtonMap2.loadFromFile("../assets/mapbutton2.png");
		textureButtonMap3.loadFromFile("../assets/mapbutton3.png");
	}
	void workUnits(){
			//if(!unitvector.empty()){
				if(choice == 3)
					unitvector[unitIt]->createSprite();
				else if(choice == 4)
					unitvector[unitIt]->createSprite();
				else if(choice == 5)
					unitvector[unitIt]->createSprite();
				unitIt++;
				//unitvector[i]->moveUnit(1);
			//}
	}
	void moveemyunits(){
		if(unitIt > 0){
			for(int i = 0; i < unitIt-1; i++){
				//if(!unitvector.empty()){
				unitvector[i]->moveUnits();
			}
				
		}
	}
	void createemyunits(){
			//if(!unitvector.empty()){
			unitvector[unitIt-1]->fillMoveTab(1, choice);
	}
public:
	WindowChoice(){
		font.loadFromFile("../assets/Font/OpenSans-Bold.ttf");
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color(162,250,193));
		text.setPosition(sf::Vector2f(700, 10));
		text.setString("");

		textmoney.setFont(font);
		textmoney.setCharacterSize(24);
		textmoney.setFillColor(sf::Color(162,250,193));
		textmoney.setPosition(sf::Vector2f(700,36));
		textmoney.setString("");

		textpoints.setFont(font);
		textpoints.setCharacterSize(24);
		textpoints.setFillColor(sf::Color(162,250,193));
		textpoints.setPosition(sf::Vector2f(1000,36));
		textpoints.setString("");
		points = 0;

		playerLife = 30;
		
		zerowanieTab();
	}
	void zerowanieTab(){
		for(int i = 0; i < 32; i++){
			for(int j = 0; j<18; j++){
				placeCheck[i][j] = 0;
			}
		}
	}
	void changeMap(int x){
		if(x < 1 || x > 5)
			exit(-1);
		else{
			choice = x;
			setmap();
		}
		cash = 100;
	}
	void drawMap(sf::RenderWindow *window){
		sprite.setTexture(texture);
		sprite.setPosition(0,0);
		//wektory rozmiarow okna i obrazu
		vec = window->getSize();
		vec2 = texture.getSize();
		//obliczanie skali
		if(choice != 1 && choice != 2){
			//float scalex = (float)vec.x/(float)vec2.x*8/10;
			//float scaley = (float)vec.y/(float)vec2.y*8/10;
			sprite.setScale(1,1);
			//obliczenie polozenia tekstury mapy
			int posy = vec.y*1/10;
		//zmiana pozycji
			sprite.setPosition(0.0f,(float)posy);
			if(tmpclock.getElapsedTime().asSeconds() > 6){
				moveemyunits();
			}
		}
		else{
			float scalex = (float)vec.x/(float)vec2.x;
			float scaley = (float)vec.y/(float)vec2.y;
			sprite.setScale(scalex,scaley);
		}
	}
	//Funkcja ustawia przyciski na mapie
	void setbuttons(){
		//making buttons
		spritebuttonstart.setTexture(textureButtonStart);
		spritebuttonquit.setTexture(textureButtonQuit);

		spritebuttonmap1.setTexture(textureButtonMap1);
		spritebuttonmap2.setTexture(textureButtonMap2);
		spritebuttonmap3.setTexture(textureButtonMap3);
		spritebuttonstart.setScale(0.4,0.4);
		spritebuttonquit.setScale(0.4,0.4);
		if(choice == 1){
			int posx = (vec.x/8) - 100;
			int posy = (vec.y/4) - 40;
			spritebuttonstart.setPosition(posx,posy);

			posx = (vec.x/8) - 100;
			posy = (vec.y/4) + 200;
			spritebuttonquit.setPosition(posx,posy);
		}
		else if(choice == 2){
			int posx = (vec.x/10) - 100;
			int posy = (vec.y/5) - 140;
			spritebuttonquit.setPosition(posx,posy);
			spritebuttonquit.setScale(0.4,0.4);

			posx = (vec.x/8);
			posy = (vec.y/5);
			spritebuttonmap1.setPosition(posx,posy);
			spritebuttonmap2.setPosition(posx,posy+200);
			spritebuttonmap3.setPosition(posx,posy+400);
			spritebuttonmap1.setScale(0.4,0.4);
			spritebuttonmap2.setScale(0.4,0.4);
			spritebuttonmap3.setScale(0.4,0.4);
		}
		else {
			int posx = (vec.x/10) - 100;
			int posy = (vec.y/5) - 140;
			spritebuttonquit.setPosition(posx,posy);
			spritebuttonquit.setScale(0.2,0.2);
		}
	}
	void drawsprites(sf::RenderWindow *window){
		window->draw(sprite);
		if(choice == 1){
			window->draw(spritebuttonstart);
			window->draw(spritebuttonquit);
		}
		else if(choice == 2){
			window->draw(spritebuttonquit);
			window->draw(spritebuttonmap1);
			window->draw(spritebuttonmap2);
			window->draw(spritebuttonmap3);
		}
		else{
			window->draw(spritebuttonquit);
			drawUnits(window);
			window->draw(text);
			window->draw(textmoney);
			window->draw(textpoints);
			//drawTestMap(window);

		}
	}
	void drawTestMap(sf::RenderWindow *window){
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(40,40));
		rect.setFillColor(sf::Color(20,70,200,100));
		for(int i = 0; i < 32; i++){
			for(int j = 0; j < 18; j++){
				if(placeCheck[i][j] == 0){
					rect.setPosition(sf::Vector2f(i*40,j*40+window->getSize().y*1/10));
					window->draw(rect);
				}
				else if(placeCheck[i][j] == 1){
					rect.setPosition(sf::Vector2f(i*40,j*40+window->getSize().y*1/10));
					rect.setFillColor(sf::Color(200,70,200,100));
					window->draw(rect);
				}
			}
		}
	}
	//Funkcja sprawdza, czy zostały naciśnięte przyciski
	void mouseInput(sf::RenderWindow *window){
		sf::Vector2i mousepos = sf::Mouse::getPosition(*window);
		//std::cout<<"mouse x = "<<mousepos.x<<std::endl;
		//std::cout<<"mouse y = "<<mousepos.y<<std::endl;
		
		sf::Vector2f translated_pos = window->mapPixelToCoords(mousepos);
		if(choice > 2){
			placeTurret(mousepos);
			if(unitTurret1.getGlobalBounds().contains(translated_pos)){
				index = 1;
				//std::cout<<"kliklo\n";
			}
		}
		
		if(choice == 1){
			if(spritebuttonstart.getGlobalBounds().contains(translated_pos))
				changeMap(2);
			else if(spritebuttonquit.getGlobalBounds().contains(sf::Vector2f(mousepos)))
				window->close();
		}
		else if(choice != 1){
			if(spritebuttonquit.getGlobalBounds().contains(translated_pos)){
				spritebuttonquit.scale(2,2);
				destroyUnits();
				destroyAllyUnits();
				changeMap(1);
				zerowanieTab();
			}
			if(choice == 2){
				if(spritebuttonmap1.getGlobalBounds().contains(translated_pos)){
					unitIt = 0;
					tmpclock.restart();
					changeMap(3);
					turretTex();
					playerLife = 30;
					mapPlacementSetup();
				}
				else if(spritebuttonmap2.getGlobalBounds().contains(translated_pos)){
					unitIt = 0;
					tmpclock.restart();
					changeMap(4);
					turretTex();
					playerLife = 30;
					mapPlacementSetup();
				}
				else if(spritebuttonmap3.getGlobalBounds().contains(translated_pos)){
					unitIt = 0;
					tmpclock.restart();
					changeMap(5);
					turretTex();
					playerLife = 30;
					mapPlacementSetup();
				}
				
			}
		}
	}
	void dosomething(){
		if(choice > 2 && tmpclock.getElapsedTime().asSeconds()>=6){
			createUnits();
		}
	}
	void turretTex(){
		turrettexture.loadFromFile("../assets/turretf.png");
		unitTurret1.setTexture(turrettexture);
		unitTurret1.setPosition(1350,500);
		unitTurret1.setScale(2,2);
	}
	void createUnits(){
		if(choice > 2){
			if(myclock.getElapsedTime().asMilliseconds() > 500 && unitIt < 300){
				myclock.restart();
				unitvector.push_back(new Units(rand()%3+4));
				workUnits();
				createemyunits();
			}
		}
	}

	void drawUnits(sf::RenderWindow *window){
		for(int  i = 0; i<allyunitvector.size();i++){
			allyunitvector[i]->drawUnit(window);
		}
		if(unitIt > 0){
			for(int i = 0; i < unitIt-1; i++){
				//if(!unitvector.empty()){
					unitvector[i]->drawUnit(window);

				//}
				int dmg = unitvector[i]->checkiffin();
				if(dmg >=1){
					playerLife -= dmg;
					unitvector[i]->disappear();
				}
			}
            for(int i = 0;i<bulletvector.size();i++){
                bulletvector[i].drawUnit(window);
            }
			if(playerLife < 1){
				spritebuttonquit.scale(2,2);
				changeMap(1);
				zerowanieTab();
				playerLife = 30;
				destroyAllyUnits();
				destroyUnits();
			}
		}
		std::string s = std::to_string(playerLife);
		std::string str = "life: "+s;
		text.setString(str);
		s = std::to_string(cash);
		str = "You have: "+s+" $";
		textmoney.setString(str);
		s = std::to_string(points);
		str = "You have: "+s+" points";
		textpoints.setString(str);
	}

	void destroyUnits(){
		for(int i = 0; i < unitvector.size(); i++){
			delete unitvector[i];
			//unitvector.erase(unitvector.begin()+i);
		}
		unitvector.resize(0);
	}

	void destroyAllyUnits(){
		for(int i = 0; i < allyunitvector.size(); i++){
			delete allyunitvector[i];
		}
		allyunitvector.resize(0);
	}

	void unitMenu(sf::RenderWindow *window){
		if(choice > 2){
			if(units.getPosition().x != 1300){
				units.setPosition(sf::Vector2f(1300,0));
				units.setSize(sf::Vector2f((window->getSize().x-1300),window->getSize().y));
				units.setFillColor(sf::Color(10,10,10));
			}
			window->draw(units);
			window->draw(unitTurret1);
		}
	}

	void highlight(sf::RenderWindow *window){

		if(choice > 2){
			sf::Vector2i mpos = sf::Mouse::getPosition(*window);
			if(mpos.x<1260 && mpos.y>100 && mpos.y < 780){
				mpos.x = (int)mpos.x/(1280/32);
				mpos.y = (int)mpos.y/(720/18);
				
				mpos.x = (mpos.x*(1280/32));
				mpos.y = (mpos.y*(720/18));

				sf::VertexArray array(sf::LinesStrip, 5);
				array[0].position = sf::Vector2f((mpos.x),(mpos.y));
				array[1].position = sf::Vector2f((mpos.x)+40,(mpos.y));
				array[2].position = sf::Vector2f((mpos.x)+40,(mpos.y)+40);
				array[3].position = sf::Vector2f((mpos.x),(mpos.y)+40);
				array[4].position = array[0].position;
				array[0].color = sf::Color(sf::Color::Green);
				array[1].color = sf::Color(sf::Color::Magenta);
				array[2].color = sf::Color(sf::Color::Green);
				array[3].color = sf::Color(sf::Color::Magenta);
				array[4].color = sf::Color(sf::Color::Green);
				
				
				window->draw(array);
			}
		}
	}

	void placeTurret(sf::Vector2i mpos){
		//sf::Vector2i mpos = sf::Mouse::getPosition();
		if(index != 0 && cash > 9){
			sf::Vector2f tmp;
			bool turretplaced = false;
			if(mpos.x<1260 && mpos.y>100 && mpos.y < 780){
				mpos.x = (int)mpos.x/(1280/32);
				mpos.y = (int)mpos.y/(720/18);
				mpos.x = (mpos.x*(1280/32));
				mpos.y = (mpos.y*(720/18));
				tmp.x = mpos.x;
				tmp.y = mpos.y;
				std::cout<<"placecheck x:"<<(int)mpos.x/(1280/32)<<"   y: "<<(int)mpos.y/(720/18)<<"    =   "<<placeCheck[(int)mpos.x/(1280/32)][(int)mpos.y/(720/18)]<<"\n";
				if(placeCheck[(int)tmp.x/(1280/32)][(int)tmp.y/(720/18)]==0){
					for(int i = 0; i < allyunitvector.size(); i++){
						if(tmp == allyunitvector[i]->position){
							turretplaced = true;
						}
					}
					if(!turretplaced){
            			allyunitvector.push_back(new towers(1,sf::Vector2f(0,0)));
                        sf::Vector2f mposf;
                        mposf.x = (float)mpos.x;
                        mposf.y = (float)mpos.y;

						allyunitvector[allyunitvector.size()-1]->sprite.setPosition(mposf);

                        mposf.x = (float)mpos.x - 25;
                        mposf.y = (float)mpos.y - 25;
                        allyunitvector[allyunitvector.size()-1]->collisionArea.setPosition(mposf);
						cash -=10;
					}
				}
			}
			index = 0;
		}
	}

	void mapPlacementSetup(){
		if(choice == 3){
			switcher = true;
			lastx = 0;
			lasty = 12;
			pcHelper(5);
			pcHelper(-3);
			pcHelper(8);
			pcHelper(9);
			pcHelper(2);
			pcHelper(-2);
			pcHelper(2);
			pcHelper(-7);
			pcHelper(3);
			pcHelper(-4);
			pcHelper(1);
			pcHelper(-1);
			pcHelper(3);
			pcHelper(9);
			pcHelper(3);
			pcHelper(3);
			pcHelper(3);
			pcHelper(-5);
			pcHelper(1);
			placeCheck[lastx][lasty] = 1;
		}
		else if(choice == 4){
			switcher = false;
			lastx = 5;
			lasty = 2;
			pcHelper(5);
			pcHelper(-3);
			pcHelper(10);
			pcHelper(4);
			pcHelper(-5);
			pcHelper(3);
			pcHelper(-3);
			pcHelper(3);
			pcHelper(3);
			pcHelper(3);
			pcHelper(5);
			pcHelper(4);
			pcHelper(-10);
			pcHelper(-3);
			pcHelper(-3);
			pcHelper(7);
			pcHelper(7);
			pcHelper(3);
			pcHelper(5);
			pcHelper(3);
			pcHelper(-3);
			pcHelper(2);
			placeCheck[lastx][lasty] = 1;
		}
		else if(choice == 5){
			switcher = true;
			lastx = 0;
			lasty = 5;
			pcHelper(7);
			pcHelper(10);
			pcHelper(3);
			pcHelper(-5);
			pcHelper(2);
			pcHelper(3);
			pcHelper(3);
			pcHelper(-6);
			pcHelper(1);
			pcHelper(-1);
			pcHelper(2);
			pcHelper(-2);
			pcHelper(3);
			pcHelper(13);
			pcHelper(4);
			pcHelper(-4);
			pcHelper(2);
			pcHelper(-4);
			pcHelper(3);
			pcHelper(-5);
			pcHelper(1);
			placeCheck[lastx][lasty] = 1;
		}
	}

	void pcHelper(int n){
		if(n != 0){
			if(!switcher){
				if(n > 0){
					for(int i = 0; i<n; i++){
						placeCheck[lastx][lasty] = 1;
						lasty += 1;
					}
				}
				else{
					for(int i = 0; i>n; i--){
						placeCheck[lastx][lasty] = 1;
						lasty -= 1;
					}
				}
				switcher = !switcher;
			}
			else{
				if(n > 0){
					for(int i = 0; i<n; i++){
						placeCheck[lastx][lasty] = 1;
						lastx += 1;
					}
				}
				else{
					for(int i = 0; i>n; i--){
						placeCheck[lastx][lasty] = 1;
						lastx -= 1;
					}
				}
				switcher = !switcher;
			}
		}
	}

    void shooting(){
        for(int i = 0;i<allyunitvector.size();i++){
			if((!allyunitvector[i]->target) >=0)
				for(int j=0;j<unitvector.size();j++){
					allyunitvector[i]->createBullet(*unitvector[j],&bulletvector,i);
				}
			else{
				allyunitvector[i]->createBullet(*unitvector[allyunitvector[i]->target],&bulletvector,allyunitvector[i]->target);
			}
        }
		
    }
};