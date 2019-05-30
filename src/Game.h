#ifndef CONNECTFOURGAME_H
#define CONNECTFOURGAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Screen.h"
#include "Board.h"
#include "Player.h"
#include "ReplayGame.h"
#include "EnemyBot.h"

class Game : public Screen
{
public:
	Game(bool vsPlayerParam);

	//the main loop of the game
	virtual int run(sf::RenderWindow& window);

	~Game();
private:
	//draws all the relevant items to the screen
	void draw(sf::RenderWindow& window);

	void switchPlayer();

	void updateGame(float xMousePos, float yMousePos);

	Board board;
	ReplayGame replayGame;
	EnemyBot enemyBot;

	Player playerOne;
	Player playerTwo;
	Player *currentPlayer;

	bool someoneWon;
	bool displayReplay;
	bool botTurn;
	bool vsPlayer;

	sf::Font winnerFont;
	sf::Text winnerText;

	sf::Texture graphicTexture;
	sf::Sprite graphicSprite;

	const float COLUMN_WIDTH = 91.4f;
};

#endif