#include "Stage2Controller.h"


Stage2Controller::Stage2Controller()
{
	model = std::make_shared<Stage2Model>();
}

Stage2Controller::Stage2Controller(std::shared_ptr<Stage2Model> model)
{
	this->model = model;
}

void Stage2Controller::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void Stage2Controller::update(std::shared_ptr<Event> event)
{
	std::vector<std::shared_ptr<Enemy>> enemies = model->getEnemies();
	std::vector<std::shared_ptr<BlockData>> blockData = model->getMap();
	if (event->getType() == "Tick Event")
	{

		updateMovementOfPlayer(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()), model->getCamera());
		updateBigDuration(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));
		updateMovementOfEnemy(enemies, model->getCamera(), std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));
		updatePlayerDie(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));
		updateTimeBoomerang(model->getPlayerData(), model->getBoomerang());

		for (const auto& block : blockData)
		{
			if (block->getIsBouncing())
			{
				updateBounceOfBlock(block);
			}
		}
		updateMouse();
		float timer = model->getTimer();
		updateTimer(timer);
		model->setTimer(timer);

		updateCamera();
	}
	else if (event->getType() == "Block Change Event")
	{
		std::shared_ptr<BlockChangeEvent> blockChange = std::dynamic_pointer_cast<BlockChangeEvent>(event);
		BlockData* preBlock = blockChange->getPre();
		std::shared_ptr<BlockData> newBlock = blockChange->getNew();
		std::vector<std::shared_ptr<BlockData>> map = model->getMap();
		std::vector<std::shared_ptr<ItemData>> items = model->getItems();

		updateBlock(preBlock, newBlock, map, items);
		model->setMap(map);
		model->setItems(items);
	}
	else if (event->getType() == "Item Touched Event")
	{

		std::shared_ptr<ItemTouchedEvent> itemTouched = std::dynamic_pointer_cast<ItemTouchedEvent>(event);


		ItemData* item = itemTouched->getItem();
		std::vector<std::shared_ptr<ItemData>> items = model->getItems();
		removeItem(items, item);
		model->setItems(items);

		if (itemTouched->getObjectType() == "Item-Coin")
		{
			std::shared_ptr<PlayerData> playerData = std::dynamic_pointer_cast<PlayerData>(model->getPlayerData());
			model->setCoins(model->getCoins() + 1);
		}
		else if (itemTouched->getObjectType() == "Item-RedMushroom")
		{
			//std::shared_ptr<PlayerData> playerData = std::dynamic_pointer_cast<PlayerData>(model->getPlayerData());
			//playerData->setBig(true);
			//playerData->setBigDuration(1000);
		}
	}
	else if (event->getType() == "Enemy Die Event")
	{
		auto enemyDie = std::dynamic_pointer_cast<EnemyDie>(event);

		Enemy* enemy = enemyDie->getEnemy();
		std::vector<std::shared_ptr<Enemy>> enemies = model->getEnemies();
		removeEnemy(enemies, enemy);
		model->setEnemies(enemies);
	}
	updateScore(event, model);
}

void Stage2Controller::updateMouse()
{
	updatePauseAndSetting(model->getSettingButton(), model->getPauseButton());
}

void Stage2Controller::updateCamera()
{
	Camera3D& camera = model->getCamera();
	std::shared_ptr<PlayerData> marioModel = std::dynamic_pointer_cast<PlayerData>(model->getPlayerData());

	Vector3 cameraOffset = { -40.0f, 20.0f, 0.0f };
	camera.position = Vector3Add(marioModel->getPlayerPos(), cameraOffset);
	camera.target = marioModel->getPlayerPos();

	float zoomSpeed = 5.0f;
	camera.fovy -= GetMouseWheelMove() * zoomSpeed;

	if (camera.fovy < 10.0f) camera.fovy = 10.0f;
	if (camera.fovy > 90.0f) camera.fovy = 90.0f;
}
