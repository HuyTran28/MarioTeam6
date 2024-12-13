#pragma once
#include "StageModel.h"
#include <vector>
#include "btBulletDynamicsCommon.h"

class Stage1Model : public StageModel
{
private:
	int m_width;
	int m_depth;
	int m_height;
	std::vector<std::shared_ptr<BlockData>> m_map;

public:
	Stage1Model();
	Stage1Model(int width, int depth, int height, btDiscreteDynamicsWorld* dynamicsWorld);
	~Stage1Model();
	const std::vector<std::shared_ptr<BlockData>>& getMap() const;
};

