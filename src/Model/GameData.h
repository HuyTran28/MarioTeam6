#pragma once

#include <string>
#include <memory>
#include "btBulletDynamicsCommon.h"
#include "raylib.h"

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
	std::string getCurState();
	void setCurState(std::string curState);



	Font getFont();
	Texture2D getHp();
	Texture2D getOneCoin();
	Texture2D getFiveCoin();
	Texture2D getTenCoin();
	Texture2D getZeroCoin();


	~GameData();

private:
	std::string playerName;
	int playerScore;
	bool isLogIn;
	std::string curState = "Menu";
	std::string lastState;
	GameData();

	Font font;
	Texture2D hp;
	Texture2D ZeroCoin;
	Texture2D OneCoin;
	Texture2D FiveCoin;
	Texture2D TenCoin;
};