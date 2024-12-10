#include "LogInController.h"

LogInController::LogInController()
{
}

LogInController::LogInController(std::shared_ptr<LogInModel> model)
{
	this->model = model;
}

void LogInController::update(std::shared_ptr<Event> event)
{
	updateKeyboard();

	updateMouse();


}

void LogInController::updateKeyboard()
{
	char c = GetCharPressed();
	if (model->getUsernameActive() == true)
	{
		if (c != 0 && model->getUsername().size() < LogInModel::MAX_USERNAME_LENGTH)
		{
			model->setUsername(model->getUsername() + c);
		}
		if (IsKeyPressed(KEY_BACKSPACE) && model->getUsername().size() > 0)
		{
			model->setUsername(model->getUsername().substr(0, model->getUsername().size() - 1));
		}
	}
	else if (model->getPasswordActive() == true)
	{
		if (c != 0 && model->getPassword().size() < LogInModel::MAX_PASSWORD_LENGTH)
		{
			model->setPassword(model->getPassword() + c);
		}
		if (IsKeyPressed(KEY_BACKSPACE) && model->getPassword().size() > 0)
		{
			model->setPassword(model->getPassword().substr(0, model->getPassword().size() - 1));
		}
	}
}

void LogInController::updateMouse()
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePoint = GetMousePosition();
		if (CheckCollisionPointRec(mousePoint, model->getUsernameBox()))
		{
			model->setUsernameActive(true);
			model->setPasswordActive(false);
		}
		else if (CheckCollisionPointRec(mousePoint, model->getPasswordBox()))
		{
			model->setUsernameActive(false);
			model->setPasswordActive(true);
		}
		else
		{
			model->setUsernameActive(false);
			model->setPasswordActive(false);
		}
	}
	if (isIconClicked(model->getHidePassword(), model->getHidePasswordPosition(), model->getHidePasswordScale()))
	{
		model->setIsHidenPassword(!model->getIsHidenPassword());
	}
	if (isIconClicked(model->getBackArrow(), model->getBackArrowPosition(), model->getBackArrowScale()))
	{
		EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Menu"));
	}
	if (isIconClicked(model->getNextArrow(), model->getNextArrowPosition(), model->getNextArrowScale()))
	{
		if (checkCredentials())
		{
			GameData::getInstance().setIsLogIn(true);
			EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Menu"));
		}
		else
		{
		}
	}
}

void LogInController::updateGameState()
{

}

bool LogInController::isIconClicked(Texture2D icon, Vector2 position, float scale)
{
	// Define the destination rectangle (where the icon is drawn on the screen)
	Rectangle destRec = { position.x, position.y, icon.width * scale, icon.height * scale };

	// Get the current mouse position
	Vector2 mousePosition = GetMousePosition();

	// Check if the mouse is over the icon and if the left mouse button is pressed
	return CheckCollisionPointRec(mousePosition, destRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void LogInController::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

bool LogInController::checkCredentials()
{
	std::ifstream file;
	std::string filename = "..\\..\\account\\" + model->getUsername() + ".txt";
	file.open(filename);
	if (file.is_open())
	{
		std::string password;
		std::getline(file, password);
		file.close();
		return password == model->getPassword();
	}
	return false;
}



