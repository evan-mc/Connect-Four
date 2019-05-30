#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Screen.h"
#include "MenuScreen.h"
#include "Game.h"
#include "Game_Network.h"

int main() 
{
	Screen* mainScreen = new MenuScreen;

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
		else if (returnVal == 4) //server
		{
			std::cout << "\nLocal IP Address: " << sf::IpAddress::getLocalAddress() << "\n";
			std::cout << "\nPublic IP Address: " << sf::IpAddress::getPublicAddress() << "\n";
			delete mainScreen;
			mainScreen = new Game_Network('s', "");
		}
		else if (returnVal == 5) //client
		{
			std::cout << "\nLocal IP Address: " << sf::IpAddress::getLocalAddress() << "\n";
			std::cout << "\nPublic IP Address: " << sf::IpAddress::getPublicAddress() << "\n";
			std::cout << "\nEnter the IP to connect to: ";
			std::string ip;
			std::cin >> ip;
			std::cout << "\nConnecting to " << ip << "\n";
			delete mainScreen;
			mainScreen = new Game_Network('c', ip);
		}
	}

	delete mainScreen;
}