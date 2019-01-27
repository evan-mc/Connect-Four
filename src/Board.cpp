#include "Board.h"
#include <iterator>
#include <iostream>

Board::Board()
{
	//sets the width position of each circle
	float widthPos = 0.f;
	//sets the height position of each circle
	float heightPos = 0.f;

	for (auto& arr : board)
	{
		for (auto& circle : arr)
		{
			circle.setRadius(40.f);
			circle.setPosition(widthPos, heightPos);
			circle.setFillColor(sf::Color::White);
			heightPos += 80.f;
		}
		//resets the height to zero for the next column of circles
		heightPos = 0.f;
		widthPos += 91.4f;
	}
}

void Board::draw(sf::RenderWindow& window)
{
	for (const auto& arr : board)
	{
		for (const auto& circle : arr)
		{
			window.draw(circle);
		}
	}
}

bool Board::dropDisc(int columnIdx, const sf::Color& playerColor)
{
	auto iter = findNextFreeSpace(columnIdx);
	if (iter != board[columnIdx].end())
	{
		iter->setFillColor(playerColor);
		return true;
	}

	return false;
}

bool Board::checkForWinner(int row, const sf::Color& playerColor)
{
	return (checkForWinnerHorizontal(row, playerColor) || checkForWinnerVertical(row, playerColor) || checkForWinnerDiagonal(playerColor));
}

void Board::resetBoard()
{
	for (auto& elem : board)
	{
		for (auto& innerElem : elem)
		{
			innerElem.setFillColor(sf::Color::White);
		}
	}
}

bool Board::checkForWinnerHorizontal(int row, const sf::Color& playerColor)
{

	auto iter = findNextFreeSpace(row);
	if (iter != board[row].end()) //increase the iter to the current disc location
	{
		++iter;
	}
	else //we know the last spot was just filled up, so we check the top row
	{
		iter = board[row].begin();
	}

	int rowToCheck = iter - board[row].begin();

	//returns true if there are four of the same color in a row
	int consecutiveColors = 0;
	for (int i = 0; i < NUM_OF_COLUMNS; ++i)
	{
		//loops through all of the circles in a row and stores their colors
		if (board[i][rowToCheck].getFillColor() == playerColor)
		{
			++consecutiveColors;
		}
		else
		{
			consecutiveColors = 0;
		}

		if (consecutiveColors == 4)
		{
			return true;
		}
	}
	return false;
}

bool Board::checkForWinnerVertical(int column , const sf::Color& playerColor)
{
	//returns true if there are four of the same color in a row
	int consecutiveColors = 0;
	for (int i = 0; i < NUM_OF_ROWS; ++i)
	{
		if(board[column][i].getFillColor() == playerColor)
		{
			++consecutiveColors;
		}
		else
		{
			consecutiveColors = 0;
		}

		if (consecutiveColors == 4)
		{
			return true;
		}
	}
	return false;
}

bool Board::checkForWinnerDiagonal(const sf::Color& playerColor)
{
	//top left to bottom right diagonal check for first column
	for (int startIdx = 0; startIdx < 3; ++startIdx)
	{
		int consecutiveColors = 0;
		for (int rowIdx = startIdx, columnIdx = 0; rowIdx < NUM_OF_ROWS; ++rowIdx, ++columnIdx)
		{
			if (board[columnIdx][rowIdx].getFillColor() == playerColor)
			{
				++consecutiveColors;
			}
			else
			{
				consecutiveColors = 0;
			}

			if (consecutiveColors == 4)
			{
				return true;
			}
		}
	}

	//top left to bottom right diagonal check for the other columns
	for (int startIdx = 1; startIdx < 4; ++startIdx)
	{
		int consecutiveColors = 0;
		for (int rowIdx = 0, columnIdx = startIdx; rowIdx < NUM_OF_ROWS - startIdx + 1; ++rowIdx, ++columnIdx)
		{
			if (board[columnIdx][rowIdx].getFillColor() == playerColor)
			{
				++consecutiveColors;
			}
			else
			{
				consecutiveColors = 0;
			}

			if (consecutiveColors == 4)
			{
				return true;
			}
		}
	}

	//top right to bottom left diagonal check for last column
	for (int startIdx = 0; startIdx < 3; ++startIdx)
	{
		int consecutiveColors = 0;
		for (int rowIdx = startIdx, columnIdx = 6; rowIdx < NUM_OF_ROWS; ++rowIdx, --columnIdx)
		{
			if (board[columnIdx][rowIdx].getFillColor() == playerColor)
			{
				++consecutiveColors;
			}
			else
			{
				consecutiveColors = 0;
			}

			if (consecutiveColors == 4)
			{
				return true;
			}
		}
	}

	//top right to bottom left diagonal check for the other columns
	for (int startIdx = 5; startIdx > 2; --startIdx)
	{
		int consecutiveColors = 0;
		for (int rowIdx = 0, columnIdx = startIdx; rowIdx < startIdx + 1; ++rowIdx, --columnIdx)
		{
			if (board[columnIdx][rowIdx].getFillColor() == playerColor)
			{
				++consecutiveColors;
			}
			else
			{
				consecutiveColors = 0;
			}

			if (consecutiveColors == 4)
			{
				return true;
			}
		}
	}


	return false;
}

std::array<sf::CircleShape, 6>::iterator Board::findNextFreeSpace(int columnIdx)
{
	std::array<sf::CircleShape, 6>::iterator columnIter = board[columnIdx].begin();

	//checks if the column is filled
	if (columnIter->getFillColor() == sf::Color::White)
	{
		++columnIter;

		while (columnIter != board[columnIdx].end() && columnIter->getFillColor() == sf::Color::White)
		{
			//keep iterating forward until we find a filled disc, or we reach the end
			++columnIter;
		}
		//back up one space to the highest unfilled disc
		--columnIter;

		return columnIter;
	}
	else
	{
		return board[columnIdx].end();
	}
}

Board::~Board()
{
}