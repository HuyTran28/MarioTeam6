#include "LogInView.h"

LogInView::LogInView()
{
	this->model = std::make_shared<LogInModel>();
}

LogInView::LogInView(std::shared_ptr<LogInModel> model)
{
	EnableCursor();
	this->model = model;
}

LogInView::LogInView(const LogInView& logInView)
{
	this->model = logInView.model;
}

void LogInView::render()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	Rectangle usernameBox = model->getUsernameBox();
	Rectangle passwordBox = model->getPasswordBox();

	std::string username = model->getUsername();
	std::string password = model->getPassword();

	DrawTexture(model->getBackground(), 0, 0, WHITE);

	DrawRectangleRec(usernameBox, LIGHTGRAY);
	DrawText("Username:", usernameBox.x, usernameBox.y - 50.0f, LogInModel::FONT_TITLE_SIZE, WHITE);
	DrawText(username.c_str(), usernameBox.x + LogInModel::FONT_INPUT_SIZE, usernameBox.y + LogInModel::BOX_HEIGHT / 2.0f - LogInModel::FONT_INPUT_SIZE / 2.0f, LogInModel::FONT_INPUT_SIZE, BLACK);
	
	DrawRectangleRec(passwordBox, LIGHTGRAY);
	DrawText("Password:", passwordBox.x, passwordBox.y - 50.0f, LogInModel::FONT_TITLE_SIZE, WHITE);
	DrawText(std::string(password.size(), '*').c_str(), passwordBox.x + LogInModel::FONT_INPUT_SIZE, passwordBox.y + LogInModel::BOX_HEIGHT / 2.0f - LogInModel::FONT_INPUT_SIZE / 2.0f, LogInModel::FONT_INPUT_SIZE, BLACK);

	EndDrawing();
}

void LogInView::update(std::shared_ptr<Event> event)
{
	if (event->getType() == "Tick Event")
	{
		render();
	}
	else if (event->getType() == "State Change Event")
	{
		//changeState();
	}
}

void LogInView::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

