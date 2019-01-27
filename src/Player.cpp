#include "Player.h"

Player::Player(const std::string& colorChoice)
{
	if (colorChoice == "Red")
		playerColor = sf::Color::Red;
	else if (colorChoice == "Yellow")
		playerColor = sf::Color::Yellow;
}

const sf::Color& Player::getPlayerColor() const
{
	return playerColor;
}

Player::~Player()
{
}