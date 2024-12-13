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
	btDiscreteDynamicsWorld* getDynamicsWorld() const;

	~GameData();

private:
	std::string playerName;
	int playerScore;
	bool isLogIn;
	GameData();

	btDiscreteDynamicsWorld* m_dynamicsWorld;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
};