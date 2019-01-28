#include "EnemyBot.h"

EnemyBot::EnemyBot()
{
}

int EnemyBot::playMove() const
{
	static std::default_random_engine eng{};
	static std::uniform_int_distribution<int> randomNum{};

	return randomNum(eng, std::uniform_int_distribution<int>::param_type{ 0, 6 });
}

EnemyBot::~EnemyBot()
{
}