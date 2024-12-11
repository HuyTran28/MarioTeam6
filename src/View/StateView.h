#pragma once

#include <string>
#include "../Event/Event.h"
#include "../Observer/IObserver.h"
#include "../Model/Block/BlockData.h"

class StateView : public IObserver
{
public:
	virtual void render() = 0;
	virtual ~StateView() = default;
	void renderBlocks(std::vector<std::shared_ptr<BlockData>> map);
	virtual void registerSelf() = 0;
};