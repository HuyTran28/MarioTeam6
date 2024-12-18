#pragma once

#include <memory>
#include "Observer/IObserver.h"
#include "Factory/Factory.h"
#include "Event/Event.h"
#include "Event/EventManager.h"
#include "Event/TickEvent.h"
#include "Event/InitializeEvent.h"
#include "Event/StateChangeEvent.h"
#include "Controller/StateController.h"
#include <raylib.h>
#include <stack>
#include "Model/GameData.h"
#include "btBulletDynamicsCommon.h"
#include "CollisionManager/CollisionManager.h"
#include "SoundManager/SoundManager.h"

class GameEngine : public IObserver, public std::enable_shared_from_this<GameEngine>
{
private:
	bool isRunning;
	bool isInit = false;
	std::string curState;
	std::shared_ptr<StateModel> stateModel;
	std::shared_ptr<StateView> stateView;
	std::shared_ptr<StateController> stateController;

	std::stack<std::shared_ptr<StateModel>> stateModelStack;
	std::stack<std::shared_ptr<StateView>> stateViewStack;
	std::stack<std::shared_ptr<StateController>> stateControllerStack;
	std::stack<std::string> stateStack;
public:
	GameEngine();
	void run();
	void update(std::shared_ptr<Event> event) override;

	void registerSelf();
};