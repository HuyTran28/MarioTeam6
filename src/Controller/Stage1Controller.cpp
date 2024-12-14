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
	
	if (event->getType() == "Tick Event")
	{
		updateMovementOfMario(std::dynamic_pointer_cast<Mario>(model->getPlayerData()));
	}

}



