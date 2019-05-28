#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "Screen.h"
#include <SFML/Graphics.hpp>

class MenuScreen : public Screen
{
public:
	MenuScreen();

	virtual int run(sf::RenderWindow& window);

	~MenuScreen();

private:
	sf::Font gameFont;
	sf::Text playLocal;
	sf::Text playBot;

};

#endif