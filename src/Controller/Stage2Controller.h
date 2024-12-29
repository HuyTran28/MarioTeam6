#pragma once

#include "../Model/Stage/Stage2Model.h"
#include "StateController.h"
#include "../Event/EventManager.h"
#include "StageController.h"
#include "../Event/StateChangeEvent.h"

class Stage2Controller : public StageController, public std::enable_shared_from_this<Stage2Controller>
{
public:
	Stage2Controller();
	Stage2Controller(std::shared_ptr<Stage2Model> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;

private:
	std::shared_ptr<Stage2Model> model;
};
