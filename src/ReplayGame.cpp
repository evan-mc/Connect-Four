#include "ReplayGame.h"

ReplayGame::ReplayGame()
{
	movesIter = movesPlayed.cbegin();
}

void ReplayGame::addMove(int columnIdx, const sf::Color& playerColor)
{
	movesPlayed.emplace_back(new discPlaceData);

	size_t lastIdx = movesPlayed.size() - 1;
	movesPlayed[lastIdx]->columnIdx = columnIdx;
	movesPlayed[lastIdx]->playerColor = playerColor;

	//resets the iterator in the event that it was invalidated with a new vector reallocation
	movesIter = movesPlayed.cbegin();
}

void ReplayGame::resetMoves()
{
	for (auto& elem : movesPlayed)
	{
		delete elem;
		elem = nullptr;
	}
	movesPlayed.clear();
	movesIter = movesPlayed.cbegin();
}

bool ReplayGame::lastMove() const
{
	return (movesIter == movesPlayed.cend());
}

std::pair<int, sf::Color> ReplayGame::getNextMove()
{
	std::pair<int, sf::Color> returnData = std::make_pair((*movesIter)->columnIdx, (*movesIter)->playerColor);
	++movesIter;

	return (returnData);
}

ReplayGame::~ReplayGame()
{
	resetMoves();
}