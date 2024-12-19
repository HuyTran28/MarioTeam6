#pragma once

#include "StateView.h"
#include "../Model/GameOverModel.h"

class GameOverView : public StateView, public std::enable_shared_from_this<GameOverView>
{
public:
	GameOverView(std::shared_ptr<GameOverModel> gameOverModel);
	void render() override;
	void update(std::shared_ptr<Event> event) override;
	void registerSelf() override;
private:
	std::shared_ptr<GameOverModel> model;
};