#include "Game.h"

void Game::initWindow() {
	this->videoMode = sf::VideoMode::getDesktopMode();
	this->window = new sf::RenderWindow(videoMode, "RPG Open", sf::Style::Fullscreen);
	this->window->setFramerateLimit(75);
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
}

void Game::render() {
	this->window->clear();
	this->window->display();
}

void Game::run() {
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}
