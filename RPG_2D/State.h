#pragma once
#include <vector>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <sstream>

class State {
private:
	std::vector<sf::Texture> textures;

public:
	State();
	virtual ~State();


	virtual void update() = 0;
	virtual void render() = 0;
};
