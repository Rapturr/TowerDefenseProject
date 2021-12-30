#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "maps.h"

int main(){
	WindowChoice windowChoice;
	PlaySound(TEXT("../assets/Sounds/BG.wav"),NULL,SND_ASYNC);

	int width = 1500;
	int height = 820;
	sf::Vector2u currsize;
	sf::Event event;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	sf::RenderWindow window(sf::VideoMode(width,height),"Tower Defense", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize, settings);
	window.setKeyRepeatEnabled(false);
	window.setFramerateLimit(60);
	windowChoice.changeMap(1);
	windowChoice.drawMap(&window);
	sf::Clock myclock;
	myclock.restart();
	while(window.isOpen()){
		if((int)myclock.getElapsedTime().asSeconds() % 177 >= 0){
			PlaySound(TEXT("../assets/Sounds/BG.wav"),NULL,SND_ASYNC);
		}
		while (window.pollEvent(event)){
		if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
		}
		windowChoice.drawMap(&window);
		windowChoice.setbuttons();

		window.clear(sf::Color::Black);
		windowChoice.dosomething();
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