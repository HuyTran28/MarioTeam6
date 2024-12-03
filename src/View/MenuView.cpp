#include "MenuView.h"

MenuView::MenuView() : MenuView(std::make_shared<MenuModel>())
{
}

MenuView::MenuView(std::shared_ptr<MenuModel> model)
{
	this->model = model;
}

MenuView::MenuView(const MenuView& menuView)
{
	this->model = menuView.model;
}

void MenuView::render()
{
	UpdateCamera(&(model->getCamera()), CAMERA_FIRST_PERSON);

	BeginDrawing();
	ClearBackground(RAYWHITE);

	BeginMode3D(model->getCamera());

	DrawModelEx(model->getLobbyModel(), model->getLobbyPos(), model->getLobbyRotationAxis(), model->getLobbyRotationAngle(), model->getLobbyScale(), WHITE);

	std::shared_ptr<PlayerData> playerData = model->getPlayerData();
	DrawModelEx(playerData->getPlayerModel(), playerData->getPlayerPos(), playerData->getPlayerRotationAxis(), playerData->getPlayerRotationAngle(), playerData->getPlayerScale(), WHITE);

	EndMode3D();
	EndDrawing();
}

void MenuView::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "State Change Event")
	{
		//changeState();
	}
	else if (event->getType() == "Tick Event")
	{
		render();
	}
	render();
}

void MenuView::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

