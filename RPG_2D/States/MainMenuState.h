#pragma once

#include "../Button.h"
#include "GameState.h"

class MainMenuState : public State {
 private:
  sf::RectangleShape background;
  sf::Font font;

  void initFonts();
  void initKeyBinds();

 public:
  MainMenuState(sf::RenderWindow* window,
                std::map<std::string, int>* supportedKeys);
  virtual ~MainMenuState();

  void endState();
  void updateInput(const float& dt);
  void update(const float& dt);
  void render(sf::RenderTarget* target = nullptr);
};
