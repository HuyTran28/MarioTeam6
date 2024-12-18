#include "GameData.h"

#include <iostream>
GameData::GameData()
{
	playerName = "Mario";
	playerScore = 0;
	isLogIn = false;
}

GameData& GameData::getInstance()
{
	static GameData instance;
	return instance;
}

std::string GameData::getPlayerName()
{
	return playerName;
}

int GameData::getPlayerScore()
{
	return playerScore;
}

bool GameData::getIsLogIn()
{
	return isLogIn;
}

void GameData::setPlayerName(std::string playerName)
{
	this->playerName = playerName;
}

void GameData::setPlayerScore(int playerScore)
{
	this->playerScore = playerScore;
}

void GameData::setIsLogIn(bool isLogIn)
{
	this->isLogIn = isLogIn;
}

std::string GameData::getLastState()
{
	return lastState;
}

void GameData::setLastState(std::string lastState)
{
	this->lastState = lastState;
}


GameData::~GameData()
{

}