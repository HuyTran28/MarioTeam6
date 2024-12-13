#pragma once
#include "StageModel.h"
#include <vector>
#include <memory>
#include "btBulletDynamicsCommon.h"

class Stage2Model : public StageModel
{
private:
	int m_width;
	int m_depth;
	int m_height;
	std::vector<std::shared_ptr<BlockData>> m_map;

public:
	Stage2Model();
	~Stage2Model();
	const std::vector<std::shared_ptr<BlockData>>& getMap() const;
};

