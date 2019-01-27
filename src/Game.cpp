#include "Game.h"

Game::Game() : playerOne("Red"), playerTwo("Yellow"), currentPlayer(&playerOne), someoneWon(false)
{
	window.create(sf::VideoMode(640, 480), "Connect Four", sf::Style::Close);

	winnerFont.loadFromFile("arial.ttf");
	winnerText.setFont(winnerFont);
	winnerText.setPosition(125, 100);
	winnerText.setFillColor(sf::Color::Magenta);
	winnerText.setString("Player wins!");
	winnerText.setCharacterSize(70);
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
	if (someoneWon)
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

	if (!someoneWon && board.dropDisc(columnIdx, currentPlayer->getPlayerColor()))
	{
		if (board.checkForWinner(columnIdx, currentPlayer->getPlayerColor()))
		{
			someoneWon = true;

			if (currentPlayer == &playerOne)
				winnerText.setString("Red Wins!\n Press R to\n play again");
			else
				winnerText.setString("Yellow Wins!\n Press R to\n play again");

		}
		else
		{
			switchPlayer();
		}
	}
}

Game::~Game()
{
}