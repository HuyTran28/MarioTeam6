#pragma once

#include "Stage.h"
#include "Block.h"
#include <memory>
#include <string>
#include "BlockFactory.h"
#include "btBulletDynamicsCommon.h"




class Stage1 : public Stage
{
public:
	Stage1();
	Stage1(int width, int depth, int height, btDiscreteDynamicsWorld* dynamicsWorld);
	~Stage1();
	void update(btRigidBody* player) override;
	void draw() override;
private:
	int m_width;
	int m_depth;
	int m_height;

	std::vector<Block*> m_normalBrickBlock;
	std::vector<Block*> m_questionBlock;
	std::vector<Block*> m_map;

};