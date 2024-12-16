#include "SelectCharacterView.h"

SelectCharacterView::SelectCharacterView()
{
	model = std::make_shared<SelectCharacter>();
}

SelectCharacterView::SelectCharacterView(std::shared_ptr<SelectCharacter> model)
{
	this->model = model;
	EnableCursor();
}

SelectCharacterView::~SelectCharacterView()
{
}

#include <iostream>

void SelectCharacterView::render()
{
	ClearBackground(RAYWHITE);
	BeginDrawing();

	model->getBackground()->draw();


	std::cout << GetMousePosition().x << " " << GetMousePosition().y << std::endl;

	model->getBackButton()->draw();
	std::vector<std::shared_ptr<Button>> characterButtons = model->getCharacterButtons();
	for (int i = 0; i < characterButtons.size(); i++)
	{
		characterButtons[i]->draw();
	}
	EndDrawing();
}

void SelectCharacterView::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
}

void SelectCharacterView::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}