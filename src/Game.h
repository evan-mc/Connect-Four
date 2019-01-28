#ifndef CONNECTFOURGAME_H
#define CONNECTFOURGAME_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Board.h"
#include "Player.h"
#include "ReplayGame.h"
#include "EnemyBot.h"

class Game
{
public:
	Game();

	//the main loop of the game
	void start();

	~Game();
private:
	//draws all the relevant items to the screen
	void draw();

	void switchPlayer();

	void updateGame(float xMousePos, float yMousePos);

	sf::RenderWindow window;

	Board board;
	ReplayGame replayGame;
	EnemyBot enemyBot;

	Player playerOne;
	Player playerTwo;
	Player *currentPlayer;

	bool someoneWon;
	bool displayReplay;

	sf::Font winnerFont;
	sf::Text winnerText;

	sf::Texture graphicTexture;
	sf::Sprite graphicSprite;

	const float COLUMN_WIDTH = 91.4f;
	const float COLUMN_HEIGHT = 80.f;
};

#endif