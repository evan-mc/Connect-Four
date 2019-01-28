#include "Game.h"

Game::Game() : playerOne("Red"), playerTwo("Yellow"), currentPlayer(&playerOne), someoneWon(false), displayReplay(false)
{
	window.create(sf::VideoMode(640, 480), "Connect Four", sf::Style::Close);

	winnerFont.loadFromFile("arial.ttf");
	winnerText.setFont(winnerFont);
	winnerText.setPosition(0, 60);
	winnerText.setFillColor(sf::Color::Color(255, 124, 31, 255)); //orange color
	winnerText.setString("Player wins!");
	winnerText.setCharacterSize(70);

	graphicTexture.loadFromFile("graphic.png");
	graphicSprite.setTexture(graphicTexture);
	graphicSprite.setPosition(-3, -2);
}

void Game::start()
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
				break;
			case sf::Event::KeyPressed:
				if (someoneWon && evnt.key.code == sf::Keyboard::R)
				{
					someoneWon = false;
					board.resetBoard();
					replayGame.resetMoves();
				}
				else if(someoneWon && evnt.key.code == sf::Keyboard::N)
				{
					displayReplay = true;
					board.resetBoard();
				}
				break;
			case sf::Event::MouseButtonPressed:
				sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
				sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
				std::cout << "X Position: " << coord_pos.x << std::endl;
				std::cout << "Y Position: " << coord_pos.y << std::endl;
				updateGame(coord_pos.x, coord_pos.y);
				break;
			}
		}
		draw();
	}
}

void Game::draw()
{
	window.clear();
	board.draw(window);
	window.draw(graphicSprite);
	if (someoneWon && !displayReplay)
	{
		window.draw(winnerText);
	}
	window.display();
}

void Game::switchPlayer()
{
	if (currentPlayer == &playerOne)
		currentPlayer = &playerTwo;
	else
		currentPlayer = &playerOne;
}

void Game::updateGame(float xMousePos, float yMousePos)
{
	//gets the index of the column the player clicked on
	int columnIdx = static_cast<int>(xMousePos / COLUMN_WIDTH);

	if (!someoneWon && !displayReplay && board.dropDisc(columnIdx, currentPlayer->getPlayerColor()))
	{
		replayGame.addMove(columnIdx, currentPlayer->getPlayerColor());

		if (board.checkForWinner(columnIdx, currentPlayer->getPlayerColor()))
		{
			someoneWon = true;

			if (currentPlayer == &playerOne)
				winnerText.setString("Red Wins! Press R\nto play again Press \nN to replay the\nmatch.");
			else
				winnerText.setString("Yellow Wins! Press \nR to play again\nPress N to replay\nthe match.");

		}
		else
		{
			switchPlayer();
		}
	}
	else if (displayReplay)
	{
		if (!replayGame.lastMove())
		{
			std::pair<int, sf::Color> discData = replayGame.getNextMove();
			board.dropDisc(discData.first, discData.second);
		}
		else
		{
			displayReplay = false;
		}
	}
}

Game::~Game()
{
}