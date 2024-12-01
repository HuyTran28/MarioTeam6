#pragma once

#include "Stage.h"
#include "Block.h"
#include <memory>
#include <string>
#include "BlockFactory.h"
#include "btBulletDynamicsCommon.h"
#include <unordered_set>



class Stage2 : public Stage
{
public:
	Stage2() : m_width(0), m_depth(0), m_height(0) {}
	Stage2(int width, int depth, int height, btDiscreteDynamicsWorld* dynamicsWorld);
	~Stage2() {};

	void update(btRigidBody* player) override;
	void draw() override;
private:
	int m_width;
	int m_depth;
	int m_height;

	std::vector<Block*> m_map;
	std::vector<Block*> m_questionBlock;
	std::vector<Block*> m_normalBrickBlock;

};