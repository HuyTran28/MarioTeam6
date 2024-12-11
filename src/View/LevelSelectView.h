#pragma once

#include <raylib.h>
#include "../Model/LevelSelectModel.h"
#include "StateView.h"

class LevelSelectView : public StateView, public std::enable_shared_from_this<LevelSelectView>
{
public:
	LevelSelectView();
	LevelSelectView(std::shared_ptr<LevelSelectModel> model);
	LevelSelectView(const LevelSelectView& levelSelectView);

	void render() override;
	void update(std::shared_ptr<Event> event) override;
	void registerSelf() override;
private:
	std::shared_ptr<LevelSelectModel> model;
};