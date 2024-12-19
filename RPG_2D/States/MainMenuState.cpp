#include "MainMenuState.h"

void MainMenuState::initKeyBinds() {
  std::ifstream ifs("Config/gamestate_keys.ini");
  if (ifs.is_open()) {
    std::string key1 = "";
    std::string key2 = "";
    while (ifs >> key1 >> key2) {
      this->keybinds[key1] = this->supportedKeys->at(key2);
    }
  }
  ifs.close();
}

MainMenuState::MainMenuState(sf::RenderWindow* window,
                             std::map<std::string, int>* supportedKeys)
    : State(window, supportedKeys) {
  this->initKeyBinds();
  this->background.setSize(
      sf::Vector2f(window->getSize().x, window->getSize().y));
  this->background.setFillColor(sf::Color{121, 119, 237, 255});
}

MainMenuState::~MainMenuState() {}

void MainMenuState::endState() {
  std::cout << "Ending MainMenuState!" << std::endl;
}

void MainMenuState::updateInput(const float& dt) {
  this->checkForQuit();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    this->background.setFillColor(sf::Color::Black);
}

void MainMenuState::update(const float& dt) { this->updateInput(dt); }

void MainMenuState::render(sf::RenderTarget* target) {
  if (!target) target = this->window;

  target->draw(this->background);
}
