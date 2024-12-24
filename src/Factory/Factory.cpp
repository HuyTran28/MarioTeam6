#include "Factory.h"

void StateFactory::createMVC(std::string state, std::shared_ptr<StateModel> &stateModel, std::shared_ptr<StateView> &stateView, std::shared_ptr<StateController> &stateController)
{
	if (state == "Menu")
	{
		stateModel = std::make_shared<MenuModel>();
		stateView = std::make_shared<MenuView>(std::dynamic_pointer_cast<MenuModel> (stateModel));
		stateController = std::make_shared<MenuController>(std::dynamic_pointer_cast<MenuModel> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
	else if (state == "LogIn")
	{
		stateModel = std::make_shared<LogInModel>();
		stateView = std::make_shared<LogInView>(std::dynamic_pointer_cast<LogInModel> (stateModel));
		stateController = std::make_shared<LogInController>(std::dynamic_pointer_cast<LogInModel> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
	else if (state == "Level Select")
	{
		stateModel = std::make_shared<LevelSelectModel>();
		stateView = std::make_shared<LevelSelectView>(std::dynamic_pointer_cast<LevelSelectModel> (stateModel));
		stateController = std::make_shared<LevelSelectController>(std::dynamic_pointer_cast<LevelSelectModel> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
	else if (state == "Stage1")
	{
		stateModel = std::make_shared<Stage1Model>();
		stateView = std::make_shared<Stage1View>(std::dynamic_pointer_cast<Stage1Model> (stateModel));
		stateController = std::make_shared<Stage1Controller>(std::dynamic_pointer_cast<Stage1Model> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
	else if (state == "Stage2")
	{
		stateModel = std::make_shared<Stage2Model>();
		stateView = std::make_shared<Stage2View>(std::dynamic_pointer_cast<Stage2Model> (stateModel));
		stateController = std::make_shared<Stage2Controller>(std::dynamic_pointer_cast<Stage2Model> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
	else if (state == "Pause")
	{
		stateModel = std::make_shared<Pause>();
		stateView = std::make_shared<PauseView>(std::dynamic_pointer_cast<Pause> (stateModel));
		stateController = std::make_shared<PauseController>(std::dynamic_pointer_cast<Pause> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
	else if (state == "Select Character")
	{
		stateModel = std::make_shared<SelectCharacter>();
		stateView = std::make_shared<SelectCharacterView>(std::dynamic_pointer_cast<SelectCharacter> (stateModel));
		stateController = std::make_shared<SelectCharacterController>(std::dynamic_pointer_cast<SelectCharacter> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
	else if (state == "Setting")
	{
		stateModel = std::make_shared<SettingModel>();
		stateView = std::make_shared<SettingView>(std::dynamic_pointer_cast<SettingModel> (stateModel));
		stateController = std::make_shared<SettingController>(std::dynamic_pointer_cast<SettingModel> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
	else if (state == "Game Over")
	{
		stateModel = std::make_shared<GameOverModel>();
		stateView = std::make_shared<GameOverView>(std::dynamic_pointer_cast<GameOverModel> (stateModel));
		stateController = std::make_shared<GameOverController>(std::dynamic_pointer_cast<GameOverModel> (stateModel));
		stateController->registerSelf();
		stateView->registerSelf();
	}
}
