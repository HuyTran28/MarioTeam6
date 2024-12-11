#pragma once

#include <memory>
#include "../View/StateView.h"
#include "../Model/StateModel.h"
#include "../Controller/StateController.h"
#include "../View/MenuView.h"
#include "../Model/MenuModel.h"
#include "../Controller/MenuController.h"
#include "../View/LogInView.h"
#include "../Model/LogInModel.h"
#include "../Controller/LogInController.h"
#include "../View/LevelSelectView.h"
#include "../Model/LevelSelectModel.h"
#include "../Controller/LevelSelectController.h"

class StateFactory
{
public:
	static void createMVC(std::string state, std::shared_ptr<StateModel> &stateModel, std::shared_ptr<StateView> &stateView, std::shared_ptr<StateController> &stateController);
};