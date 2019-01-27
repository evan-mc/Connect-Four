#ifndef REPLAYGAME_H
#define REPLAYGAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

class ReplayGame
{
public:
	ReplayGame();

	void addMove(int columnIdx, const sf::Color& playerColor);

	void resetMoves();

	//returns true if the last move has been sent
	bool lastMove() const;

	std::pair<int, sf::Color> getNextMove();

	~ReplayGame();
private:
	struct discPlaceData
	{
		int columnIdx;
		sf::Color playerColor;
	};

	std::vector<discPlaceData*> movesPlayed;
	std::vector<discPlaceData*>::const_iterator movesIter;
};

#endif