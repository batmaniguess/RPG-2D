#include "MainMenuState.h"

void MainMenuState::initFonts() {
  if (!this->font.loadFromFile("Fonts/Geo-Regular.ttf")) {
    throw("Could not load font ERROR::MAINMENUSTATE");
  }
}

void MainMenuState::initButtons() {
  this->buttons["GAME_STATE_BUTTON"] = new Button(
      100, 100, 150, 50, &this->font, "Start Game", sf::Color{70, 70, 70, 200},
      sf::Color{87, 98, 123, 255}, sf::Color{0, 0, 20, 200});

  this->buttons["EXIT_STATE"] = new Button(
      100, 200, 150, 50, &this->font, "Quit", sf::Color{70, 70, 70, 200},
      sf::Color{87, 98, 123, 255}, sf::Color{0, 0, 20, 200});
}

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
  this->initFonts();
  this->initKeyBinds();
  this->initButtons();

  this->background.setSize(
      sf::Vector2f(window->getSize().x, window->getSize().y));
  this->background.setFillColor(sf::Color{121, 119, 237, 255});
}

MainMenuState::~MainMenuState() {
  auto it = this->buttons.begin();
  for (; it != this->buttons.end(); ++it) {
    delete it->second;
  }
}

void MainMenuState::endState() {
  std::cout << "Ending MainMenuState!" << std::endl;
}

void MainMenuState::updateInput(const float& dt) {
  this->checkForQuit();
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    this->background.setFillColor(sf::Color::Black);
}

void MainMenuState::updateButtons() {
  for (auto& it : this->buttons) {
    it.second->update(this->mousePosView);
  }

  if (this->buttons["EXIT_STATE"]->isPressed()) {
    this->endState();
    this->quit = true;
  }
}

void MainMenuState::update(const float& dt) {
  this->updateMousePositions();
  this->updateInput(dt);
  this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target) {
  for (auto& it : this->buttons) {
    it.second->render(target);
  }
}

void MainMenuState::render(sf::RenderTarget* target) {
  if (!target) target = this->window;

  target->draw(this->background);
  this->renderButtons(target);
}
