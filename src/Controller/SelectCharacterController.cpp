#include "SelectCharacterController.h"

SelectCharacterController::SelectCharacterController()
{
	model = std::make_shared<SelectCharacter>();
}

SelectCharacterController::SelectCharacterController(std::shared_ptr<SelectCharacter> model)
{
	this->model = model;
}

void SelectCharacterController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void SelectCharacterController::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		if (model->getBackButton()->isClicked(GetMousePosition()))
		{
			EventManager::getInstance().notify(std::make_shared<BackEvent>());
			return;
		}
		std::vector<std::shared_ptr<Button>> characterButtons = model->getCharacterButtons();

		std::vector<std::string> characterNames;
		characterNames.push_back("Mario");
		characterNames.push_back("Luigi");
		characterNames.push_back("Peach");

		for (int i = 0; i < characterButtons.size(); i++)
		{
			if (characterButtons[i]->isClicked(GetMousePosition()))
			{
				GameData::getInstance().setPlayerName(characterButtons[i]->getText());
				EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Menu"));
				return;
			}
		}
	}
}