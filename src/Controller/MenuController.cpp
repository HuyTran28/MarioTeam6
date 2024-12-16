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
	// Calculate direction vector from camera position to target
	Camera3D camera = model->getCamera();

	float moveSpeed = model->getPlayerData()->getMoveSpeed();

	// Calculate direction vector from camera position to target
	Vector3 direction = Vector3Subtract(camera.target, camera.position);
	float length = Vector3Length(direction);

	// Normalize the direction vector to avoid NaN values
	if (length != 0.0f) {
		direction = Vector3Scale(direction, 1.0f / length);
	}

	float xChange = moveSpeed * direction.x;
	float zChange = moveSpeed * direction.z;

	Vector3 playerPosition = model->getPlayerData()->getPlayerPos();

	Vector3 cameraInitialPosition = model->getCameraInitialPosition();

	if (IsKeyDown(KEY_W)) {
		playerPosition.x += xChange;
		playerPosition.z += zChange;
		model->getPlayerData()->setPlayerPos(playerPosition);
	}

	if (IsKeyDown(KEY_S)) {
		playerPosition.x -= xChange;
		playerPosition.z -= zChange;
		model->getPlayerData()->setPlayerPos(playerPosition);

	}

	if (IsKeyDown(KEY_A)) {
		playerPosition.x += zChange;
		playerPosition.z -= xChange;
		model->getPlayerData()->setPlayerPos(playerPosition);

	}

	if (IsKeyDown(KEY_D)) {
		playerPosition.x -= zChange;
		playerPosition.z += xChange;
		model->getPlayerData()->setPlayerPos(playerPosition);

	}


	// Update camera position based on player position
	camera.position = Vector3Add(playerPosition, cameraInitialPosition);
	// Update the camera target to avoid NaN values
	camera.target = Vector3Add(camera.position, direction);
	model->setCamera(camera);

	model->getPlayerData()->setForwarDir(direction);

	std::cout << model->getCamera().position.x << " " << model->getCamera().position.y << " " << model->getCamera().position.z << std::endl;

	UpdateCamera(&(model->getCamera()), CAMERA_FIRST_PERSON);
}

void MenuController::updateGameState()
{
	std::shared_ptr<Event> event = std::make_shared<StateChangeEvent>("LogIn");
	EventManager::getInstance().notify(event);
}

MenuController::~MenuController()
{
}