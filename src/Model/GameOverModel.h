#pragma once

#include "StateModel.h"
#include <memory>
#include "../Button/Button.h"

class GameOverModel : public StateModel
{
public:
	GameOverModel();
	std::shared_ptr<Button> getRetryButton() const;
	std::shared_ptr<Button> getQuitButton() const;

private:
	std::shared_ptr<Button> m_retryButton;
	std::shared_ptr<Button> m_quit;
};