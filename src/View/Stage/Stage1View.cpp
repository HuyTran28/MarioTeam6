#include "Stage1View.h"

Stage1View::Stage1View(std::shared_ptr<Stage1Model> model) : m_model(model){}

void Stage1View::render()
{
}

void Stage1View::update(std::shared_ptr<Event> event)
{
}

void Stage1View::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());	
}
