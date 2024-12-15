#include "MenuView.h"

MenuView::MenuView() : MenuView(std::make_shared<MenuModel>())
{
}

MenuView::MenuView(std::shared_ptr<MenuModel> model)
{
	DisableCursor();

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



	std::shared_ptr<CharacterData> playerData = model->getPlayerData();
	DrawModelEx(playerData->getPlayerModel(), playerData->getPlayerPos(), playerData->getPlayerRotationAxis(), playerData->getPlayerRotationAngle(), playerData->getPlayerScale(), WHITE);

	drawAccessories();

	EndMode3D();

	drawCrosshair();
	
	EndDrawing();
}

void MenuView::drawCrosshair()
{
	// Draw crosshair at the center of the screen
	int screenWidth = GetScreenWidth();
	int screenHeight = GetScreenHeight();
	int centerX = screenWidth / 2;
	int centerY = screenHeight / 2;
	int crosshairSize = 20;

	DrawLine(centerX - crosshairSize, centerY, centerX + crosshairSize, centerY, BLACK); // Horizontal line
	DrawLine(centerX, centerY - crosshairSize, centerX, centerY + crosshairSize, BLACK); // Vertical line
}

void MenuView::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
	render();
}

void MenuView::drawAccessories()
{
	if (GameData::getInstance().getIsLogIn())
	{
		Vector3 joyStickPos = model->getJoyStickPos();
		joyStickPos.z += 2.0f;
		DrawModelEx(model->getJoyStickModel(), joyStickPos, model->getJoyStickRotationAxis(), model->getJoyStickRotationAngle(), model->getJoyStickScale(), WHITE);
	}
	else {
		DrawModelEx(model->getJoyStickModelNoLogIn(), model->getJoyStickPos(), model->getJoyStickRotationAxis(), model->getJoyStickRotationAngle(), model->getJoyStickScale(), WHITE);
	}

	DrawModelEx(model->getPlayModel(), model->getPlayPos(), model->getPlayRotationAxis(), model->getPlayRotationAngle(), model->getPlayScale(), WHITE);

	DrawModelEx(model->getMarioStatueModel(), model->getMarioStatuePos(), model->getMarioStatueRotationAxis(), model->getMarioStatueRotationAngle(), model->getMarioStatueScale(), WHITE);
}

void MenuView::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

MenuView::~MenuView()
{
}
