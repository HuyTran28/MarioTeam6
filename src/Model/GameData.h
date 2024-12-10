#pragma once

#include <string>
#include <memory>

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
private:
	std::string playerName;
	int playerScore;
	bool isLogIn;
	GameData();
};