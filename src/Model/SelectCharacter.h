#pragma once

#include "Button/Button.h"
#include <memory>
#include "Model/GameData.h"
#include "StateModel.h"
#include <vector>

class SelectCharacter : public StateModel
{
private:
	std::shared_ptr<Button> backButton;
	std::vector<std::shared_ptr<Button>> characterButtons;
	std::shared_ptr<Button> background;
public:
	SelectCharacter();
	std::string getSelectCharacter();
	std::shared_ptr<Button> getBackButton();
	std::vector<std::shared_ptr<Button>> getCharacterButtons();
	std::shared_ptr<Button> getBackground();
	~SelectCharacter();
};

