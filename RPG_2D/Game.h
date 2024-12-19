#pragma once

#include "States/MainMenuState.h"

class Game {
 private:
  // Variables
  sf::RenderWindow *window;
  sf::Event event;

  sf::Clock dtClock;
  float dt;

  std::stack<State *> states;

  std::map<std::string, int> supportedKeys;

  // Initialization
  void initWindow();
  void initKeys();
  void initStates();

 public:
  Game();
  virtual ~Game();

  void endApplication();
  void updateDt();
  void updateEvents();
  void update();
  void render();
  void run();
};
