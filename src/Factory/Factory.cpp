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
}
