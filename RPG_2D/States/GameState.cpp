#include "GameState.h"

void GameState::initKeyBinds() {
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

GameState::GameState(sf::RenderWindow* window,
                     std::map<std::string, int>* supportedKeys)
    : State(window, supportedKeys) {
  this->initKeyBinds();
}

GameState::~GameState() {}

void GameState::endState() { std::cout << "Ending GameState" << std::endl; }

void GameState::updateInput(const float& dt) {
  // safe key checking
  auto checkAndMove = [this](const std::string& binding, float x, float y,
                             const float& dt) {
    try {
      if (this->keybinds.count(binding) &&
          sf::Keyboard::isKeyPressed(
              sf::Keyboard::Key(this->keybinds.at(binding)))) {
        this->player.move(dt, x, y);
      }
    } catch (const std::exception& e) {
      std::cerr << "Error parsing input for " << binding << e.what()
                << std::endl;
    }
  };

  checkAndMove("MOVE_LEFT", -1.f, 0.f, dt);
  checkAndMove("MOVE_RIGHT", 1.f, 0.f, dt);
  checkAndMove("MOVE_UP", 0.f, -1.f, dt);
  checkAndMove("MOVE_DOWN", 0.f, 1.f, dt);
}

void GameState::update(const float& dt) {
  this->updateInput(dt);
  this->player.update(dt);
}

void GameState::render(sf::RenderTarget* target) {
  if (!target) {
    target = this->window;
  }
  this->player.render(target);
}
