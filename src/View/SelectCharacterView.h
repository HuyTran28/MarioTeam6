#pragma once

#include "StateView.h"
#include "../Event/StateChangeEvent.h"
#include "../Event/EventManager.h"
#include "../Event/BackEvent.h"
#include "../Event/TickEvent.h"
#include "../Model/SelectCharacter.h"

class SelectCharacterView : public StateView, public std::enable_shared_from_this<SelectCharacterView>
{
public:
	SelectCharacterView();
	SelectCharacterView(std::shared_ptr<SelectCharacter> model);

	~SelectCharacterView();
	void render() override;
	void update( std::shared_ptr<Event> event) override;
	void registerSelf() override;
private:
	std::shared_ptr<SelectCharacter> model;
};
