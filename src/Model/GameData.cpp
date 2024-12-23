#include "GameData.h"

#include <iostream>
GameData::GameData()
{
	playerName = "Mario";
	playerScore = 0;
	isLogIn = false;

	hp = LoadTexture("../../Assets\\Icons\\health.png");
	font = LoadFontEx("../../Assets\\Font\\font.otf", 256, 0, 0);
	ZeroCoin = LoadTexture("../../Assets\\Icons\\0Coin.png");
	OneCoin = LoadTexture("../../Assets\\Icons\\1Coin.png");
	FiveCoin = LoadTexture("../../Assets\\Icons\\5Coin.png");
	TenCoin = LoadTexture("../../Assets\\Icons\\10Coin.png");
}

GameData& GameData::getInstance()
{
	static GameData instance;
	return instance;
}

Texture2D GameData::getZeroCoin()
{
	return ZeroCoin;
}

Texture2D GameData::getHp()
{
	return hp;
}

Texture2D GameData::getOneCoin()
{
	return OneCoin;
}

Texture2D GameData::getFiveCoin()
{
	return FiveCoin;
}

Texture2D GameData::getTenCoin()
{
	return TenCoin;
}

std::string GameData::getPlayerName()
{
	return playerName;
}

Font GameData::getFont()
{
	return font;
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