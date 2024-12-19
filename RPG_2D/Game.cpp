#include "Game.h"

void Game::initWindow() {
  sf::VideoMode windowBounds(1280, 720);
  std::string title = "SFML 2D";
  unsigned frameRateLimit = 75;
  bool verticalSyncEnabled = false;

  try {
    std::ifstream inFileStream("Config/window.ini");
    if (inFileStream.is_open()) {
      std::getline(inFileStream, title);
      inFileStream >> windowBounds.width >> windowBounds.height;
      if (windowBounds.width < 100 || windowBounds.height < 100)
        throw std::runtime_error("Invalid window bounds");
      inFileStream >> frameRateLimit;
      inFileStream >> verticalSyncEnabled;
      inFileStream.close();
    }
  } catch (const std::exception& e) {
    std::cerr << "Failed to load window.ini file: " << e.what() << std::endl;
    std::cerr << "Using default values" << std::endl;
  }

  try {
    this->window =
        new sf::RenderWindow(windowBounds, title); /*sf::Style::Fullscreen*/
    this->window->setFramerateLimit(frameRateLimit);
    this->window->setVerticalSyncEnabled(verticalSyncEnabled);
  } catch (const std::exception& e) {
    std::cerr << "Failed to create window." << e.what() << std::endl;
    throw;
  }
}

// reading input from a while
void Game::initKeys() {
  std::ifstream ifs("Config/supported_keys.ini");
  if (ifs.is_open()) {
    std::string key = "";
    int key_value = 0;
    while (ifs >> key >> key_value) {
      this->supportedKeys[key] = key_value;
    }
  }
  ifs.close();

  // debug
  for (auto& i : this->supportedKeys) {
    std::cout << i.first << " " << i.second << std::endl;
  }
}

void Game::initStates() {
  this->states.push(new MainMenuState(this->window, &this->supportedKeys));
}

Game::Game() {
  this->initWindow();
  this->initKeys();
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
    State* currentState = this->states.top();
    currentState->update(this->dt);

    if (currentState->getQuit()) {
      currentState->endState();
      delete currentState;
      this->states.pop();
    }
  } else {
    this->endApplication();
    this->window->close();
  }
}

void Game::render() {
  this->window->clear();
  if (!this->states.empty() && this->window) {
    this->states.top()->render(this->window);
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
