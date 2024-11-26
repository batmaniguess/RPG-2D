#pragma once
#include <SFML/Graphics.hpp>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <vector>

class State {
 private:
  sf::RenderWindow* window;
  std::vector<sf::Texture> textures;
  bool quit;

 public:
  State(sf::RenderWindow* window);
  virtual ~State();

  const bool& getQuit() const;
  virtual void updateKeyBinds(const float& dt) = 0;
  virtual void checkForQuit();
  virtual void endState() = 0;
  virtual void update(const float& dt) = 0;
  virtual void render(sf::RenderTarget* target = nullptr) = 0;
};
