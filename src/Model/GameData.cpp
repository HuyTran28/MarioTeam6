#include "GameData.h"

#include <iostream>
GameData::GameData()
{
	playerName = "";
	playerScore = 0;
	isLogIn = false;


	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_overlappingPairCache = new btDbvtBroadphase();
	m_solver = new btSequentialImpulseConstraintSolver;

	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);
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

btDiscreteDynamicsWorld* GameData::getDynamicsWorld() const
{
	return m_dynamicsWorld;
}


GameData::~GameData()
{
	std::cout << "2\n";
	delete m_dynamicsWorld;
	delete m_solver;
	delete m_overlappingPairCache;
	delete m_dispatcher;
	delete m_collisionConfiguration;
}