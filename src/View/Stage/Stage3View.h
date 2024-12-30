#include "../StateView.h"
#include "../../Model/Stage/Stage3Model.h"
#include "../../Event/EventManager.h"
#include "../../Model/Character/Player/PlayerData.h"
#include <raymath.h>
#include <memory>
#include <set>
#include <algorithm>

class Stage3View : public StateView, public std::enable_shared_from_this<Stage3View>
{
private:
	std::shared_ptr<Stage3Model> m_model;


public:
	Stage3View();
	Stage3View(std::shared_ptr<Stage3Model> model);
	void render();

	void randomEnemy(std::vector<std::shared_ptr<Enemy>>& enemies);
	void randomItem(std::vector<std::shared_ptr<ItemData>>& items);


	void renderClouds();
	void renderHealthBar();
	void renderCharacter();

	void update(std::shared_ptr<Event> event);
	void registerSelf();
};