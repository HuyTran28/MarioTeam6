#include "../StateView.h"
#include "../../Model/Stage/Stage1Model.h"
#include "../../Event/EventManager.h"
#include <memory>
#include "../../Model/Character/Player/PlayerData.h"

class Stage1View : public StateView, public std::enable_shared_from_this<Stage1View>
{
private:
	std::shared_ptr<Stage1Model> m_model;
public:
	Stage1View();
	Stage1View(std::shared_ptr<Stage1Model> model);
	void render();
	void update(std::shared_ptr<Event> event);
	void registerSelf();
};