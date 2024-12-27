#pragma once

#include "../Model/WinModel.h"
#include "StateView.h"

class WinView : public StateView, public std::enable_shared_from_this<WinView>
{
private:
	std::shared_ptr<WinModel> model;
public:
	WinView();
	WinView(std::shared_ptr<WinModel> model);
	void render() override;
	void update(std::shared_ptr<Event> event) override;
	void registerSelf() override;
};