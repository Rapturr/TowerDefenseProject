#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "maps.h"

int main(){
	WindowChoice windowChoice;
	
	int width = 1280;
	int height = 720;
	sf::Vector2u currsize;
	sf::Event event;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(width,height),"Tower Defense", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize, settings);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	windowChoice.changeMap(1);
	windowChoice.drawMap(&window);

	//game loop
	while(window.isOpen()){
		while (window.pollEvent(event)){
		if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
			currsize = window.getSize();
			if(currsize == sf::Vector2u(width,height)){
				window.create(sf::VideoMode(1920,1080),"Tower Defense", sf::Style::Fullscreen, settings);
				window.setKeyRepeatEnabled(false);
				window.setFramerateLimit(60);
			}
			else{
				window.create(sf::VideoMode(width,height),"Tower Defense", sf::Style::Close | sf::Style::Titlebar , settings);
				window.setPosition(sf::Vector2i(0,0));
				window.setKeyRepeatEnabled(false);
				window.setFramerateLimit(60);
			}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			windowChoice.changeMap(1);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			windowChoice.changeMap(2);
		
		windowChoice.drawMap(&window);
		windowChoice.setbuttons();

		window.clear(sf::Color::Black);

		windowChoice.drawsprites(&window);
		windowChoice.unitMenu(&window);
		windowChoice.highlight(&window);
		//windowChoice.renderUnits(&window);
		//mouse input
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			windowChoice.mouseInput(&window);
		}
		window.display();
	}

	return EXIT_SUCCESS;
}