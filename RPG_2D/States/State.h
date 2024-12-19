#pragma once

#include "../Entities/Entity.h"

class State {
 private:
 protected:
  sf::RenderWindow* window;
  std::map<std::string, int>* supportedKeys;
  std::map<std::string, int> keybinds;
  std::vector<sf::Texture> textures;
  bool quit;
  sf::Vector2i mousePosScreen;
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;

  virtual void initKeyBinds() = 0;

 public:
  State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
  virtual ~State();

  const bool& getQuit() const;
  virtual void updateInput(const float& dt) = 0;
  virtual void checkForQuit();
  virtual void endState() = 0;
  virtual void updateMousePositions();
  virtual void update(const float& dt) = 0;
  virtual void render(sf::RenderTarget* target = nullptr) = 0;
  bool loadTexture(const std::string& path);
};
