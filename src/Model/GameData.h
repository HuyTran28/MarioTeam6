#pragma once

#include <string>
#include <memory>
#include "btBulletDynamicsCommon.h"

class GameData
{
public:
	static GameData& getInstance();
	GameData(const GameData&) = delete;
	GameData& operator=(const GameData&) = delete;

	std::string getPlayerName();
	int getPlayerScore();
	bool getIsLogIn();
	void setPlayerName(std::string playerName);
	void setPlayerScore(int playerScore);
	void setIsLogIn(bool isLogIn);
	std::string getLastState();
	void setLastState(std::string lastState);

	~GameData();

private:
	std::string playerName;
	int playerScore;
	bool isLogIn;
	std::string lastState;
	GameData();

};