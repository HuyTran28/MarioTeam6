#pragma once

#include "StateView.h"
#include "../Model/MenuModel.h"
#include <raylib.h>
#include <memory>

class MenuView : public StateView, public std::enable_shared_from_this<MenuView>
{
private:
	std::shared_ptr<MenuModel> model;
	bool isInit = false;
public:
	MenuView(std::shared_ptr<MenuModel> model);
	MenuView();
	MenuView(const MenuView& menuView);

	~MenuView();

	void render() override;
	void update(std::shared_ptr<Event> event) override;
	void drawCrosshair();
	void registerSelf() override;
};