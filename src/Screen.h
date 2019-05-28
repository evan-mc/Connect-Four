#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>

class Screen
{
public:
	virtual int run(sf::RenderWindow& window) = 0;
};

#endif