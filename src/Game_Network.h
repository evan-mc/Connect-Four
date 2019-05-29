#ifndef CONNECTFOURGAMENETWORK_H
#define CONNECTFOURGAMENETWORK_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

#include "Screen.h"
#include "Board.h"
#include "Player.h"
#include "ReplayGame.h"
#include "EnemyBot.h"

class Game_Network : public Screen
{
public:
	Game_Network(char input);

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
	EnemyBot enemyBot;

	Player playerOne;
	Player playerTwo;
	Player *currentPlayer;

	bool someoneWon;
	bool displayReplay;
	bool botTurn;

	sf::Font winnerFont;
	sf::Text winnerText;

	sf::Texture graphicTexture;
	sf::Sprite graphicSprite;

	sf::Packet packet1;
	sf::Packet packet2;

	sf::TcpSocket socket;
	sf::TcpSocket client;

	char connection;

	const float COLUMN_WIDTH = 91.4f;
	const float COLUMN_HEIGHT = 80.f;
};

#endif