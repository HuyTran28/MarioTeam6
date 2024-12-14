#pragma once

#include <string>
#include <memory>
#include "StateModel.h"
#include <raylib.h>
#include "../Button/Button.h"

class Pause : public StateModel
{
private:
	std::string title;

	const int buttonSize = 200;

	std::shared_ptr<Button> backButton;
	std::shared_ptr<Button> retryButton;
	std::shared_ptr<Button> resumeButton;
	std::shared_ptr<Button> quitButton;
public:
	Pause();

	std::string getTitle();
	std::shared_ptr<Button> getBackButton();
	std::shared_ptr<Button> getRetryButton();
	std::shared_ptr<Button> getResumeButton();
	std::shared_ptr<Button> getQuitButton();
};