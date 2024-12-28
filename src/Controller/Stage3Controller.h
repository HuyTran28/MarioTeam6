#pragma once

#include "../Model/Stage/Stage3Model.h"
#include "StateController.h"
#include "../Event/EventManager.h"
#include "StageController.h"
#include "../Event/StateChangeEvent.h"

class Stage3Controller : public StageController, public std::enable_shared_from_this<Stage3Controller>
{
public:
	Stage3Controller();
	Stage3Controller(std::shared_ptr<Stage3Model> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;

private:
	std::shared_ptr<Stage3Model> model;
	void updateMouse();
	void updateCamera();
};
