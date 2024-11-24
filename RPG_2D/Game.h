#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

class Game {
private:
	// Variables
	sf::VideoMode videoMode;
	sf::RenderWindow *window;
	sf::Event event;

	
	// Initialization

	void initWindow();


public:
	Game();
	virtual ~Game();

	void updateEvents();
	void update();
	void render();
	void run();
};

