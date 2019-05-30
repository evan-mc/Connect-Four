#ifndef CONNECTFOURGAMENETWORK_H
#define CONNECTFOURGAMENETWORK_H

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Screen.h"
#include "Board.h"
#include "Player.h"
#include "ReplayGame.h"

class Game_Network : public Screen
{
public:
	Game_Network(char input, const std::string& ipParam);

	//the main loop of the game
	virtual int run(sf::RenderWindow& window);

	~Game_Network();
private:
	//draws all the relevant items to the screen
	void draw(sf::RenderWindow& window);

	void switchPlayer();

	bool updateGame(int columnIdx);

	void runClient(sf::Uint16& num, sf::RenderWindow& window);
	void runServer(sf::Uint16& num, sf::RenderWindow& window);

	Board board;
	ReplayGame replayGame;

	Player playerOne;
	Player playerTwo;
	Player *currentPlayer;

	bool displayReplay;
	bool someoneWon;

	sf::Font winnerFont;
	sf::Text winnerText;

	sf::Texture graphicTexture;
	sf::Sprite graphicSprite;

	sf::Packet packet1;
	sf::Packet packet2;

	sf::TcpSocket socket;
	sf::TcpSocket client;

	char connection;
	std::string ip;

	const float COLUMN_WIDTH = 91.4f;
	const float COLUMN_HEIGHT = 80.f;
};

#endif