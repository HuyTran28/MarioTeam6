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
#include "../View/Stage/Stage1View.h"
#include "../Model/Stage/Stage1Model.h"
#include "../Controller/Stage1Controller.h"
#include "../View/Stage/Stage2View.h"
#include "../Model/Stage/Stage2Model.h"
#include "../Controller/Stage2Controller.h"
#include "../View/Stage/Stage3View.h"
#include "../Model/Stage/Stage3Model.h"
#include "../Controller/Stage3Controller.h"
#include "../View/PauseView.h"
#include "../Model/Pause.h"
#include "../Controller/PauseController.h"
#include "../View/SelectCharacterView.h"
#include "../Model/SelectCharacter.h"
#include "../Controller/SelectCharacterController.h"
#include "../View/SettingView.h"
#include "../Model/SettingModel.h"
#include "../Controller/SettingController.h"
#include "../View/GameOverView.h"
#include "../Model/GameOverModel.h"
#include "../Controller/GameOverController.h"
#include "../View/WinView.h"
#include "../Model/WinModel.h"
#include "../Controller/WinController.h"

class StateFactory
{
public:
	static void createMVC(std::string state, std::shared_ptr<StateModel> &stateModel, std::shared_ptr<StateView> &stateView, std::shared_ptr<StateController> &stateController);
};