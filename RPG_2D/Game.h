#pragma once

#include "State.h"

class Game {
private:
	// Variables
	sf::VideoMode videoMode;
	sf::RenderWindow *window;
	sf::Event event;

	sf::Clock dtClock;
	float dt;


	
	// Initialization

	void initWindow();


public:
	Game();
	virtual ~Game();

	void updateDt();
	void updateEvents();
	void update();
	void render();
	void run();
};

