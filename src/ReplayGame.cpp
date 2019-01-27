#include "ReplayGame.h"

ReplayGame::ReplayGame()
{
	movesIter = movesPlayed.cbegin();
}

void ReplayGame::addMove(int columnIdx, const sf::Color& playerColor)
{
	movesPlayed.emplace_back(std::make_pair(columnIdx, playerColor));

	size_t lastIdx = movesPlayed.size() - 1;
	movesPlayed[lastIdx].first = columnIdx;
	movesPlayed[lastIdx].second = playerColor;

	//resets the iterator in the event that it was invalidated with a new vector reallocation
	movesIter = movesPlayed.cbegin();
}

void ReplayGame::resetMoves()
{
	movesPlayed.clear();
	movesIter = movesPlayed.cbegin();
}

bool ReplayGame::lastMove() const
{
	return (movesIter == movesPlayed.cend());
}

std::pair<int, sf::Color> ReplayGame::getNextMove()
{
	++movesIter;
	return (*(movesIter-1));
}

ReplayGame::~ReplayGame()
{
}