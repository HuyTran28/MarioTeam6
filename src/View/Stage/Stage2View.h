#include "../StateView.h"
#include "../../Model/Stage/Stage2Model.h"
#include "../../Event/EventManager.h"
#include "../../Model/Character/Player/PlayerData.h"
#include <memory>


class Stage2View : public StateView, public std::enable_shared_from_this<Stage2View>
{
private:
	std::shared_ptr<Stage2Model> m_model;
public:
	Stage2View();
	Stage2View(std::shared_ptr<Stage2Model> model);
	void render();

	void renderClouds();
	void renderCharacter();

	void update(std::shared_ptr<Event> event);
	void registerSelf();
};