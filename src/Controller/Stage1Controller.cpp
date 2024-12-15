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
		setPlayerAnimationState(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));
		updateMovementOfMario(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));
		updateAnimationState(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));

		std::cout <<" tttttttttttttttttttttttttttttttttttttttttt " << model->getPlayerData()->getAnimationCount() << '\n';

		updateMovemenOfEnemy(enemies);


		updateMouse();
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



