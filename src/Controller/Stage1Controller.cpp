#include "Stage1Controller.h"

Stage1Controller::Stage1Controller()
{
	model = std::make_shared<Stage1Model>();
}

Stage1Controller::Stage1Controller(std::shared_ptr<Stage1Model> model)
{
	this->model = model;
}

void Stage1Controller::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void Stage1Controller::update(std::shared_ptr<Event> event)
{
	std::vector<std::shared_ptr<Enemy>> enemies = model->getEnemies();
	if (event->getType() == "Tick Event")
	{
		
		updateMovementOfPlayer(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));
		updateMovemenOfEnemy(enemies);


		updateMouse();
		
		updateCamera();
	}

}

void Stage1Controller::updateMouse()
{
	if (model->getPauseButton()->isClicked(GetMousePosition()))
	{
		EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Pause"));
		return;
	}
}

void Stage1Controller::updateCamera()
{
	Camera3D& camera = model->getCamera();
	std::shared_ptr<PlayerData> marioModel = std::dynamic_pointer_cast<PlayerData>(model->getPlayerData());

	Vector3 cameraOffset = { 0.0f, 10.0f, 40.0f };
	camera.position = Vector3Add(marioModel->getPlayerPos(), cameraOffset);
	camera.target = marioModel->getPlayerPos();

	float zoomSpeed = 5.0f;
	camera.fovy -= GetMouseWheelMove() * zoomSpeed;

	if (camera.fovy < 10.0f) camera.fovy = 10.0f;
	if (camera.fovy > 90.0f) camera.fovy = 90.0f;
}



