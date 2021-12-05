#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "units.h"

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
	std::vector<Units*> allyunitvector;
	sf::RectangleShape units;
	sf::Font font;
	sf::Text text;
	int cash;
	int playerLife;
	//0-czysto, 1-droga
	int placeCheck[32][18];
	int offset;

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
		for(int i = 0; i < 300; i++){
			//if(!unitvector.empty()){
				if(choice == 3)
					unitvector[i]->createSprite(4,370);
				else if(choice == 4)
					unitvector[i]->createSprite(300,300);
				else if(choice == 5)
					unitvector[i]->createSprite(300,300);
				//unitvector[i]->moveUnit(1);
			//}
		}
	}
public:
	WindowChoice(){
		font.loadFromFile("../assets/Font/OpenSans-Bold.ttf");
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color(162,250,193));
		text.setPosition(sf::Vector2f(700, 10));
		text.setString("");
		playerLife = 30;
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
			float scalex = (float)vec.x/(float)vec2.x*8/10;
			float scaley = (float)vec.y/(float)vec2.y*8/10;
			sprite.setScale(scalex,scaley);
			//obliczenie polozenia tekstury mapy
			int posy = vec.y*1/10;
		//zmiana pozycji
			sprite.setPosition(0.0f,(float)posy);
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
			spritebuttonquit.setScale(0.5,0.5);

			posx = (vec.x/8);
			posy = (vec.y/5);
			spritebuttonmap1.setPosition(posx,posy);
			spritebuttonmap2.setPosition(posx,posy+200);
			spritebuttonmap3.setPosition(posx,posy+400);
		}
		else {
			int posx = (vec.x/10) - 100;
			int posy = (vec.y/5) - 140;
			spritebuttonquit.setPosition(posx,posy);
			spritebuttonquit.setScale(0.5,0.5);
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
			drawUnits(&window);
			window->draw(text);
		}
	}
	//Funkcja sprawdza, czy zostały naciśnięte przyciski
	void mouseInput(sf::RenderWindow *window){
		sf::Vector2i mousepos = sf::Mouse::getPosition(*window);
		std::cout<<"mouse x = "<<mousepos.x<<std::endl;
		std::cout<<"mouse y = "<<mousepos.y<<std::endl;
		sf::Vector2f translated_pos = window->mapPixelToCoords(mousepos);
		if(choice > 2)
			placeTurret(mousepos);
		
		if(choice == 1){
			if(spritebuttonstart.getGlobalBounds().contains(translated_pos))
				changeMap(2);
			else if(spritebuttonquit.getGlobalBounds().contains(sf::Vector2f(mousepos)))
				window->close();
		}
		else if(choice != 1){
			if(spritebuttonquit.getGlobalBounds().contains(translated_pos)){
				/*if(choice != 2){
					//destroyUnits();
				}*/
				changeMap(1);
				spritebuttonquit.scale(2,2);
			}
			if(choice == 2){
				if(spritebuttonmap1.getGlobalBounds().contains(translated_pos)){
					changeMap(3);
					createUnits();
					turretTex();
					playerLife = 30;
					
				}
				else if(spritebuttonmap2.getGlobalBounds().contains(translated_pos)){
					changeMap(4);
					createUnits();
					turretTex();
					playerLife = 30;
				}
				else if(spritebuttonmap3.getGlobalBounds().contains(translated_pos)){
					changeMap(5);
					createUnits();
					turretTex();
					playerLife = 30;
				}
			}
		}
	}
	void turretTex(){
		turrettexture.loadFromFile("../assets/turretf.png");
		unitTurret1.setTexture(turrettexture);
		unitTurret1.setPosition(1224,500);
		unitTurret1.setScale(2,2);
	}
	void createUnits(){
		if(choice > 2){
			for(int i = 0; i < 300; i++){
				unitvector.push_back(new Units(5));
			}
			workUnits();
		}
	}


	void drawUnits(sf::RenderWindow **window){
		int random = std::rand() % 300;
		int random1 = (std::rand() % 4)+1;
		for(int i = 0; i < 300; i++){
			//if(!unitvector.empty()){
				unitvector[i]->moveUnit(1, choice);
				unitvector[i]->drawUnit(*window);
				if(i < allyunitvector.size()){
					//std::cout<<"i = "<<i<<std::endl;
					allyunitvector[i]->drawUnit(*window);
				}
			//}
			playerLife -= unitvector[i]->checkiffin();
		}
		//text.setString("Life: %d",playerLife);
		std::string s = std::to_string(playerLife);
		std::string str = "life: "+s;
		text.setString(str);
	}

	void destroyUnits(){
		for(int i = 0; i < 300; i++){
			delete unitvector[i];
			//unitvector.erase(unitvector.begin()+i);
			std::cout<<"unit: "<<i<<" destroyed"<<std::endl;
		}
		cash += 10;
	}

	void unitMenu(sf::RenderWindow *window){
		if(choice > 2){
			if(units.getPosition().x != 1024){
				units.setPosition(sf::Vector2f(1024,0));
				units.setSize(sf::Vector2f((window->getSize().x-1024),window->getSize().y));
				units.setFillColor(sf::Color::Red);
			}
			window->draw(units);
			window->draw(unitTurret1);
		}
	}

	void highlight(sf::RenderWindow *window){
		int offsetx;
		int offsety = 0;

		if(choice > 2){
			sf::Vector2i mpos = sf::Mouse::getPosition(*window);
			if(mpos.x<1024 && mpos.y>70 && mpos.y < 640){
				mpos.x = (int)mpos.x/32;
				mpos.y = (int)mpos.y/18;
				//mpos.x = (mpos.x*32)+20;
				//mpos.y = (mpos.y*18)+2;

				mpos.x = (mpos.x*32)+20;
				mpos.y = (mpos.y*18)+2;

				sf::VertexArray array(sf::LinesStrip, 5);
				array[0].position = sf::Vector2f((mpos.x)-20,(mpos.y)-20+offsety);
				array[1].position = sf::Vector2f((mpos.x)+20,(mpos.y)-20+offsety);
				array[2].position = sf::Vector2f((mpos.x)+20,(mpos.y)+20+offsety);
				array[3].position = sf::Vector2f((mpos.x)-20,(mpos.y)+20+offsety);
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
		sf::Vector2f tmp;
		allyunitvector.push_back(new Units(1));
		bool turretplaced = false;
		if(mpos.x < 1012 && mpos.y > 70 && mpos.y < 640){
			mpos.x = (int)mpos.x/32;
			mpos.y = (int)mpos.y/18;
			mpos.x = (mpos.x*32)+20;
			mpos.y = (mpos.y*18)+2;
			tmp.x = mpos.x;
			tmp.y = mpos.y;
			for(int i = 0; i < allyunitvector.size(); i++){
				if(tmp == allyunitvector[i]->getPos()){
					turretplaced = true;
				}
			}
			if(!turretplaced){
				std::cout<<"rysujemy x = "<<tmp.x<<"  y = "<<tmp.y<<std::endl;
				allyunitvector[allyunitvector.size()-1]->createSprite(mpos.x, mpos.y);
			}
		}
	}

	void mapPlacementSetup(){
		if(choice == 3){
			for(int i = 0; i <= 16; i++){
				for(int j = 0; j <= 8; j++){
					placeCheck[i][j] = 0;
				}
			}
		}
	};
};