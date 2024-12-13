#include "Stage1View.h"
#include <iostream>
Stage1View::Stage1View() : m_model(std::make_shared<Stage1Model>()){}


Stage1View::Stage1View(std::shared_ptr<Stage1Model> model) : m_model(model){}

void Stage1View::render()
{
	std::vector<std::shared_ptr<BlockData>> map = m_model->getMap();	

	UpdateCamera(&(m_model->getCamera()), CAMERA_FIRST_PERSON);

	BeginDrawing();
	ClearBackground(RAYWHITE);

	
	BeginMode3D(m_model->getCamera());

	renderBlocks(map);
	m_model->setCamera(m_model->getCamera());

	EndMode3D();
	EndDrawing();
}

void Stage1View::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
}

void Stage1View::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());	
}
