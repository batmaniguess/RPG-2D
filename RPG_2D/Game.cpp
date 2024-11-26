#include "Game.h"

void Game::initWindow() {

	std::ifstream inFileStream("Config/window.ini");
	std::string title = "None";
	sf::VideoMode windowBounds(1280, 720);
	unsigned frameRateLimit = 75;
	bool verticalSyncEnabled = false;

	if (inFileStream.is_open()) {
		std::getline(inFileStream, title);
		inFileStream >> windowBounds.width >> windowBounds.height;
		inFileStream >> frameRateLimit;
		inFileStream >> verticalSyncEnabled;
	}

	inFileStream.close();


	this->window = new sf::RenderWindow(windowBounds, title); /*sf::Style::Fullscreen*/
	this->window->setFramerateLimit(frameRateLimit);
	this->window->setVerticalSyncEnabled(verticalSyncEnabled);
}

Game::Game() {
	this->initWindow();
	this->updateEvents();
	this->update();
	this->render();
	this->run();
}

Game::~Game() {
	delete this->window;
}


void Game::updateDt() {
	/*
	* @return void
	* updates the dt variable with the time it takes to update and render one frame.
	*/
	this->dt = this->dtClock.restart().asSeconds();
	//system("cls");
	//std::cout << this->dt << std::endl;
}

// Functions
void Game::updateEvents() {
	while (this->window->pollEvent(this->event)) {
		switch (this->event.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		default:
			break;
		}
	}
}

void Game::update() {
	this->updateEvents();
	//int sum = 0;
	//for (int i = 0; i < 100000000; i++) {
	//	sum += i;
	//}
}

void Game::render() {
	this->window->clear();
	this->window->display();
}

void Game::run() {
	while (this->window->isOpen()) {
		this->updateDt();
		this->update();
		this->render();
	}
}
