#pragma once

#include "../Model/Pause.h"
#include "StateView.h"

class PauseView : public StateView, public std::enable_shared_from_this<PauseView>
{
private:
	std::shared_ptr<Pause> model;
public:
	PauseView();
	PauseView(std::shared_ptr<Pause> model);
	void render() override;
	void update(std::shared_ptr<Event> event) override;
	void registerSelf() override;
};