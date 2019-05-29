#include "Game_Network.h"

Game_Network::Game_Network(char input) : playerOne("Red"), playerTwo("Yellow"), currentPlayer(&playerOne), someoneWon(false), displayReplay(false), botTurn(false)
{
	winnerFont.loadFromFile("arial.ttf");
	winnerText.setFont(winnerFont);
	winnerText.setPosition(0, 60);
	winnerText.setFillColor(sf::Color::Color(255, 124, 31, 255)); //orange color
	winnerText.setString("Player wins!");
	winnerText.setCharacterSize(70);

	graphicTexture.loadFromFile("graphic.png");
	graphicSprite.setTexture(graphicTexture);
	graphicSprite.setPosition(-3, -2);

	connection = input;
}

int Game_Network::run(sf::RenderWindow& window)
{
	sf::TcpListener listener;

	sf::Uint16 num;
	if (connection == 'c')
	{
		sf::Socket::Status status = socket.connect("localhost", 53000);
		if (status != sf::Socket::Done)
		{
			std::cout << "couldn't connect to server\n";
		}

		num = 2;
	}
	else
	{
		currentPlayer = &playerTwo;
		// bind the listener to a port
		if (listener.listen(53000) != sf::Socket::Done)
		{
			std::cout << "couldnt listen on port\n";
		}
		// accept a new connection
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "couldn't accept a client\n";
		}
		num = 1;
	}

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
				else if (someoneWon && evnt.key.code == sf::Keyboard::N)
				{
					displayReplay = true;
					board.resetBoard();
				}
				break;
			case sf::Event::MouseButtonPressed:
				if (connection == 'c')
				{
					runClient(num, window);
				}
				else
				{
					runServer(num, window);
				}
				break;
			}
		}
		draw(window);
		if (num == 1)
		{
			if (connection == 'c')
			{
				runClient(num, window);
			}
			else
			{
				runServer(num, window);
			}
		}
	}

	return 0;
}

void Game_Network::draw(sf::RenderWindow& window)
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

void Game_Network::switchPlayer()
{
	if (currentPlayer == &playerOne)
		currentPlayer = &playerTwo;
	else
		currentPlayer = &playerOne;
}

bool Game_Network::updateGame(int columnIdx)
{
	bool droppedDisc = false;
	std::cout << " a\n";
	if (!someoneWon && !displayReplay && !botTurn && board.dropDisc(columnIdx, currentPlayer->getPlayerColor()))
	{
		droppedDisc = true;
		replayGame.addMove(columnIdx, currentPlayer->getPlayerColor());

		std::cout << "b\n";
		if (board.checkForWinner(columnIdx, currentPlayer->getPlayerColor()))
		{
			someoneWon = true;
			botTurn = false;
			std::cout << "c\n";
			if (currentPlayer == &playerOne)
				winnerText.setString("Red Wins! Press R\nto play again Press \nN to replay the\nmatch.");
			else
				winnerText.setString("Yellow Wins! Press \nR to play again\nPress N to replay\nthe match.");

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

	return droppedDisc;
}

void Game_Network::runClient(sf::Uint16& num, sf::RenderWindow& window)
{
	if (num % 2 == 0)
	{
		sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
		sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
		std::cout << "X Position: " << coord_pos.x << std::endl;
		std::cout << "Y Position: " << coord_pos.y << std::endl;

		//gets the index of the column the player clicked on
		int columnIdx = static_cast<int>(coord_pos.x / COLUMN_WIDTH);

		if (updateGame(columnIdx))
		{
			sf::Uint16 columnIdxSend = columnIdx;
			std::cout << "columnIdx: " << columnIdx << " columnIdxSend: " << columnIdxSend << "\n";
			packet1 << columnIdxSend;
			socket.send(packet1);
			packet1.clear();
			switchPlayer();

			--num;
		}
	}
	else
	{
		socket.receive(packet2);
		sf::Uint16 columnIdx2;
		packet2 >> columnIdx2;
		updateGame(columnIdx2);
		switchPlayer();

		++num;
	}
}

void Game_Network::runServer(sf::Uint16& num, sf::RenderWindow& window)
{
	if (num % 2 == 0)
	{
		sf::Vector2i pixel_pos = sf::Mouse::getPosition(window);
		sf::Vector2f coord_pos = window.mapPixelToCoords(pixel_pos);
		std::cout << "X Position: " << coord_pos.x << std::endl;
		std::cout << "Y Position: " << coord_pos.y << std::endl;

		//gets the index of the column the player clicked on
		int columnIdx = static_cast<int>(coord_pos.x / COLUMN_WIDTH);
		std::cout << "placing on idx " << columnIdx;

		if (updateGame(columnIdx))
		{
			sf::Uint16 columnIdxSend = columnIdx;
			std::cout << "columnIdx: " << columnIdx << " columnIdxSend: " << columnIdxSend << "\n";

			packet2 << columnIdxSend;
			client.send(packet2);
			packet2.clear();
			switchPlayer();

			--num;
			std::cout << "num after sending(should be 1): " << num << "\n";
		}
	}
	else
	{
		client.receive(packet1);

		sf::Uint16 columnIdx1;
		packet1 >> columnIdx1;
		std::cout << "idx received: " << columnIdx1 << "\n";
		updateGame(columnIdx1);
		switchPlayer();

		++num;
		std::cout << "num after receiving(should be 2): " << num << "\n";
	}
}

Game_Network::~Game_Network()
{
}
