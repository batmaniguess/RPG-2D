#pragma once

#include "States/GameState.h"

class Game {
 private:
  // Variables
  sf::RenderWindow *window;
  sf::Event event;

  sf::Clock dtClock;
  float dt;

  std::stack<State *> states;


  // Initialization
  void initWindow();
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
