#include "Stage2View.h"

Stage2View::Stage2View(std::shared_ptr<Stage2Model> model) : m_model(model) {}

void Stage2View::render()
{
}

void Stage2View::update(std::shared_ptr<Event> event)
{
}

void Stage2View::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}
