#pragma once

#include "GameOverModel.h"

GameOverModel::GameOverModel()
{
	Texture2D retryButtonTexture = LoadTexture("../../Assets\\Icons\\reset.png");
	Rectangle retryButtonSourceRec = { 0.0f, 0.0f, (float)retryButtonTexture.width, (float)retryButtonTexture.height };
	Rectangle retryButtonDestRec = { 450.0f, GetScreenHeight() / 2, 200.0f, 200.0f };
	m_retryButton = std::make_shared<Button>("", retryButtonTexture, retryButtonSourceRec, retryButtonDestRec, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

	Texture2D quitButtonTexture = LoadTexture("../../Assets\\Icons\\home-button.png");
	Rectangle quitButtonSourceRec = { 0.0f, 0.0f, (float)quitButtonTexture.width, (float)quitButtonTexture.height };
	Rectangle quitButtonDestRec = { GetScreenWidth() - 650.0f, GetScreenHeight() / 2, 200.0f, 200.0f };
	m_quit = std::make_shared<Button>("", quitButtonTexture, quitButtonSourceRec, quitButtonDestRec, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
}

std::shared_ptr<Button> GameOverModel::getRetryButton() const
{
	return m_retryButton;
}

std::shared_ptr<Button> GameOverModel::getQuitButton() const
{
	return m_quit;
}

