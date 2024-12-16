#include "MenuController.h"
#include <iostream>

MenuController::MenuController()
{
	model = std::make_shared<MenuModel>();
}

MenuController::MenuController(std::shared_ptr<MenuModel> model)
{
	this->model = model;
}

void MenuController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void MenuController::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Initialize Event")
	{
	}
	else if (event->getType() == "Tick Event")
	{
		updateCamera();
		StageController::updateMovementOfPlayer(model->getPlayerData());

		Camera3D camera = model->getCamera();

		Ray ray = { 0 };
		ray.position = camera.position; // Origin of the ray is the camera's position
		ray.direction = Vector3Normalize(Vector3Subtract(camera.target, camera.position)); // Direction from camera to target
		if (GetRayCollisionBox(ray, model->getJoystickBoundingBox()).hit && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			updateGameState();
		}
		else if (GetRayCollisionBox(ray, model->getPlayModelBoundingBox()).hit && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			std::shared_ptr<Event> event = std::make_shared<StateChangeEvent>("Level Select");
			EventManager::getInstance().notify(event);
		}
	}
}

void MenuController::updateCamera()
{
	Camera3D& camera = model->getCamera();
	std::shared_ptr<PlayerData> marioModel = model->getPlayerData();

	std::cout << marioModel->getForwarDir().x << " " << marioModel->getForwarDir().y << " " << marioModel->getForwarDir().z << std::endl;

	Vector3 tmp = Vector3Scale(marioModel->getForwarDir(), 20.0f);
	camera.position = Vector3Add(marioModel->getPlayerPos(), tmp);

	Vector3 baseTarget = Vector3Add(camera.position, marioModel->getForwarDir());
	verticalOffset -= GetMouseDelta().y * 0.001f;

	camera.target = baseTarget;
	camera.target.y += verticalOffset;

	float zoomSpeed = 5.0f;
	camera.fovy -= GetMouseWheelMove() * zoomSpeed;

	if (camera.fovy < 10.0f) camera.fovy = 10.0f;
	if (camera.fovy > 90.0f) camera.fovy = 90.0f;

	UpdateCamera(&(model->getCamera()), CAMERA_CUSTOM);
}

void MenuController::updateGameState()
{
	std::shared_ptr<Event> event = std::make_shared<StateChangeEvent>("LogIn");
	EventManager::getInstance().notify(event);
}

MenuController::~MenuController()
{
}