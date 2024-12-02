#pragma once

#include <raylib.h>
#include "Stage.h"
#include "Observer.h"
#include <vector>
//#include "StageCreator.h"


class Game
{
public:
	enum GameState { STAGE1, STAGE2 };

	// Singleton pattern
	static Game& getInstance();
	Game(const Game&) = delete;
	void operator=(const Game&) = delete;

	// Init window and setFPS
	void init();

	// Main game loop
	void run();

	// While isRunning, call update and draw
	void update();
	void draw();

	// Add observer to the observer list
	void addGameStateObserver(Observer* ob);

	// Notify all the observers
	void notifyStateChange(); // Notify all the observers

	void drawBackground();
	void drawStage();
	void drawUI();

private:
	Game(); // private constructor
	bool isRunning; // set to false when exit button is pressed
	Stage* curStage;
	GameState curState; // GameState is enum variable
	std::vector<Observer*> stateObservers;

	// Handle when the game in a stage, player want to go to another stage. Ex: stage 1 to menu when press a button.
	void switchStage(GameState state);  //  call the notify state change with the respective state
};
