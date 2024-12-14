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
	std::shared_ptr<btDiscreteDynamicsWorld> getDynamicsWorld() const;
	std::string getLastState();
	void setLastState(std::string lastState);

	~GameData();

private:
	std::string playerName;
	int playerScore;
	bool isLogIn;
	std::string lastState;
	GameData();

	std::shared_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;
	std::shared_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
	std::shared_ptr<btCollisionDispatcher> m_dispatcher;
	std::shared_ptr<btBroadphaseInterface> m_overlappingPairCache;
	std::shared_ptr<btSequentialImpulseConstraintSolver> m_solver;
};