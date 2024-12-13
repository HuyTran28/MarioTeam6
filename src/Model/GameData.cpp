#include "GameData.h"

#include <iostream>
GameData::GameData()
{
	playerName = "";
	playerScore = 0;
	isLogIn = false;


	m_collisionConfiguration = std::make_shared<btDefaultCollisionConfiguration>();
	m_dispatcher = std::make_shared<btCollisionDispatcher>(m_collisionConfiguration.get());
	m_overlappingPairCache = std::make_shared<btDbvtBroadphase>();
	m_solver = std::make_shared<btSequentialImpulseConstraintSolver>();
	m_dynamicsWorld = std::make_shared<btDiscreteDynamicsWorld>(m_dispatcher.get(), m_overlappingPairCache.get(), m_solver.get(), m_collisionConfiguration.get());

	m_dynamicsWorld->setGravity(btVector3(0, -9.81, 0));
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

std::shared_ptr<btDiscreteDynamicsWorld> GameData::getDynamicsWorld() const
{
	return m_dynamicsWorld;
}


GameData::~GameData()
{
	std::cout << "2\n";
}