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
		updatePlayerMovement();

		if (IsKeyDown(KEY_G))
		{
			updateGameState();
		}
	}
}

void MenuController::updatePlayerMovement()
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
}

void MenuController::updateGameState()
{
	std::shared_ptr<Event> event = std::make_shared<StateChangeEvent>("LogIn");
	EventManager::getInstance().notify(event);
}

bool MenuController::CheckCollisionRayBox(Ray ray, BoundingBox box)
{
    float tmin = (box.min.x - ray.position.x) / ray.direction.x;
    float tmax = (box.max.x - ray.position.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (box.min.y - ray.position.y) / ray.direction.y;
    float tymax = (box.max.y - ray.position.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (box.min.z - ray.position.z) / ray.direction.z;
    float tzmax = (box.max.z - ray.position.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return ((tmin < 0) && (tmax > 0)) || ((tmin > 0) && (tmax > 0));
}

bool MenuController::IsMouseOver3DObject(Camera3D camera, BoundingBox box)
{
	// Get the mouse ray
	Ray mouseRay = GetMouseRay(GetMousePosition(), camera);

	// Check for collision between the mouse ray and the bounding box
	return CheckCollisionRayBox(mouseRay, box);
}

MenuController::~MenuController()
{
}