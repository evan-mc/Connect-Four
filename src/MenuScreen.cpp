#include "MenuScreen.h"
#include <iostream>

MenuScreen::MenuScreen()
{
	gameFont.loadFromFile("arial.ttf");

	playBot.setFont(gameFont);
	playBot.setPosition(193, 30);
	playBot.setFillColor(sf::Color::White);
	playBot.setString("Play vs Bot");
	playBot.setCharacterSize(50);

	playOnlineServer.setFont(gameFont);
	playOnlineServer.setPosition(118, 130);
	playOnlineServer.setFillColor(sf::Color::White);
	playOnlineServer.setString("Play Online (Server)");
	playOnlineServer.setCharacterSize(50);

	playOnlineClient.setFont(gameFont);
	playOnlineClient.setPosition(118, 230);
	playOnlineClient.setFillColor(sf::Color::White);
	playOnlineClient.setString("Play Online (Client)");
	playOnlineClient.setCharacterSize(50);

	playLocal.setFont(gameFont);
	playLocal.setPosition(177, 330);
	playLocal.setFillColor(sf::Color::White);
	playLocal.setString("Play vs Local");
	playLocal.setCharacterSize(50);

}

int MenuScreen::run(sf::RenderWindow& window)
{
	while (window.isOpen())
	{

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				return 0;
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
				sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
				std::cout << "X Position: " << coord_pos.x << std::endl;
				std::cout << "Y Position: " << coord_pos.y << std::endl;

				if (playLocal.getGlobalBounds().contains(coord_pos))
				{
					std::cout << "Entering vs local\n";
					return 2; //returning 2 means to play vs local player
				}
				else if (playBot.getGlobalBounds().contains(coord_pos))
				{
					std::cout << "Entering vs bot\n"; 
					return 3; //returning 3 means to play vs bot
				}
				else if (playOnlineServer.getGlobalBounds().contains(coord_pos))
				{
					std::cout << "Entering online (as server)\n";
					return 4; //returning 4 means we are the server
				}
				else if (playOnlineClient.getGlobalBounds().contains(coord_pos))
				{
					std::cout << "Entering online (as client)\n";
					return 5; //returning 5 means we are the client
				}
				break;
			}
		}

		sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
		sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
		if (playLocal.getGlobalBounds().contains(coord_pos))
		{
			playLocal.setFillColor(sf::Color::Yellow);
		}
		else if (playBot.getGlobalBounds().contains(coord_pos))
		{
			playBot.setFillColor(sf::Color::Yellow);
		}
		else if (playOnlineServer.getGlobalBounds().contains(coord_pos))
		{
			playOnlineServer.setFillColor(sf::Color::Yellow);
		}
		else if (playOnlineClient.getGlobalBounds().contains(coord_pos))
		{
			playOnlineClient.setFillColor(sf::Color::Yellow);
		}
		else
		{
			playBot.setFillColor(sf::Color::White);
			playLocal.setFillColor(sf::Color::White);
			playOnlineServer.setFillColor(sf::Color::White);
			playOnlineClient.setFillColor(sf::Color::White);
		}
		window.clear();
		window.draw(playBot);
		window.draw(playOnlineServer);
		window.draw(playOnlineClient);
		window.draw(playLocal);
		window.display();
	}

	return 0;
}

MenuScreen::~MenuScreen()
{

}