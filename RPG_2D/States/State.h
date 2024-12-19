#pragma once

#include "../Entities/Entity.h"

class State {
 protected:
  sf::RenderWindow* window;
  std::map<std::string, int>* supportedKeys;
  std::map<std::string, int> keybinds;
  std::vector<sf::Texture> textures;
  bool quit;

  virtual void initKeyBinds() = 0;

 public:
  State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
  virtual ~State();

  const bool& getQuit() const;
  virtual void updateInput(const float& dt) = 0;
  virtual void checkForQuit();
  virtual void endState() = 0;
  virtual void update(const float& dt) = 0;
  virtual void render(sf::RenderTarget* target = NULL) = 0;
};
