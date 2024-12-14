#pragma once

#include "../Model/Stage/Stage1Model.h"
#include "StateController.h"
#include "../Event/EventManager.h"
#include "StageController.h"
#include "../Event/StateChangeEvent.h"

class Stage1Controller : public StageController, public std::enable_shared_from_this<Stage1Controller>
{
public:
	Stage1Controller();
	Stage1Controller(std::shared_ptr<Stage1Model> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;

private:
	std::shared_ptr<Stage1Model> model;
	void updateMouse();
};