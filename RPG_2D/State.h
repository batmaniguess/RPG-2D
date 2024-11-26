#pragma once
#include <vector>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

class State {
private:
	std::vector<sf::Texture> textures;

public:
	State();
	virtual ~State();


	virtual void update() = 0;
	virtual void render() = 0;
};