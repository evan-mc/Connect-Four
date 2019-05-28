#include "Game.h"

#include <SFML/Graphics.hpp>
#include "MenuScreen.h"
#include "Screen.h"
int main() 
{
	//Game game;
	//game.start();

	Screen* mainScreen = new MenuScreen;
	//MenuScreen menu;

	int returnVal = 1;
	sf::RenderWindow window(sf::VideoMode(640, 480), "Connect Four", sf::Style::Close);
	while (returnVal != 0)
	{
		returnVal = mainScreen->run(window);
		if (returnVal == 2) //local
		{
			delete mainScreen;
			mainScreen = new Game(true);
		}
		else if (returnVal == 3) //bot
		{
			delete mainScreen;
			mainScreen = new Game(false);
		}
	}

	delete mainScreen;
}