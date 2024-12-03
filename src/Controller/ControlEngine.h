#pragma once

#include "../Observer/IObserver.h"
#include <string>
#include "../Event/EventManager.h"
#include "../Model/MenuModel.h"
#include "../Model/StateModel.h"

class ControlEngine : public IObserver, public std::enable_shared_from_this<ControlEngine>
{
private:
	std::shared_ptr<StateModel> curStateModel;
public:
	ControlEngine();
	void update(std::shared_ptr<Event> event) override;
};