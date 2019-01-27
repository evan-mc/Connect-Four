#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player
{
public:
	Player(const std::string& colorChoice);

	const sf::Color& getPlayerColor() const;

	~Player();
private:
	sf::Color playerColor;
};

#endif