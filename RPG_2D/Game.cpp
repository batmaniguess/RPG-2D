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
  this->window =
      new sf::RenderWindow(windowBounds, title); /*sf::Style::Fullscreen*/
  this->window->setFramerateLimit(frameRateLimit);
  this->window->setVerticalSyncEnabled(verticalSyncEnabled);
}

void Game::initStates() { this->states.push(new GameState(this->window)); }

Game::Game() {
  this->initWindow();
  this->initStates();
}

Game::~Game() {
  delete this->window;

  while (!this->states.empty()) {
    delete this->states.top();  // erases the data
    this->states.pop();         // removes the pointer
  }
}

void Game::endApplication() { std::cout << "Ending Application" << std::endl; }

void Game::updateDt() {
  /*
   * @return void
   * updates the dt variable with the time it takes to update and render one
   * frame.
   */
  this->dt = this->dtClock.restart().asSeconds();
}

// Functions
void Game::updateEvents() {
  while (this->window->pollEvent(this->event)) {
    switch (this->event.type) {
      case sf::Event::Closed:
        this->window->close();
        break;
      case sf::Event::KeyPressed:
        if (this->event.key.code == sf::Keyboard::Escape) this->window->close();
        break;
      default:
        break;
    }
  }
}

void Game::update() {
  this->updateEvents();
  if (!this->states.empty()) {
    this->states.top()->update(this->dt);
    if (this->states.top()->getQuit()) {
      this->states.top()->endState();
      delete this->states.top();
      this->states.pop();
    }
  } else {
    this->endApplication();
    this->window->close();
  }
}

void Game::render() {
  this->window->clear();
  if (!this->states.empty()) {
    this->states.top()->render();
  }
  this->window->display();
}

void Game::run() {
  while (this->window->isOpen()) {
    this->updateDt();
    this->update();
    this->render();
  }
}
