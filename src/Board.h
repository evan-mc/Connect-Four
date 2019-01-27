#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <SFML/Graphics.hpp>
#include <array>

class Board
{
public:
	Board();

	void draw(sf::RenderWindow& window);

	//attempts to add the players disc to the column
	//they clicked on. Returns true if the column is not full
	//and the disc was placed.
	bool dropDisc(int columnIdx, const sf::Color& playerColor);

	//checks horizontal, vertical, and diagonal pieces for wins
	bool checkForWinner(int row, const sf::Color& playerColor);

	void resetBoard();

	~Board();
private:
	bool checkForWinnerVertical(int column, const sf::Color& playerColor);
	bool checkForWinnerHorizontal(int row, const sf::Color& playerColor);
	bool checkForWinnerDiagonal(const sf::Color& playerColor);

	std::array<sf::CircleShape, 6>::iterator findNextFreeSpace(int columnIdx);

	const int NUM_OF_COLUMNS = 7;
	const int NUM_OF_ROWS = 6;

	std::array<std::array<sf::CircleShape, 6>, 7> board;
};

#endif