#include "Stage1Controller.h"

Stage1Controller::Stage1Controller()
{
	model = std::make_shared<Stage1Model>();
}

Stage1Controller::Stage1Controller(std::shared_ptr<Stage1Model> model)
{
	this->model = model;
}

void Stage1Controller::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}

void Stage1Controller::update(std::shared_ptr<Event> event)
{
	std::vector<std::shared_ptr<Enemy>> enemies = model->getEnemies();
	std::vector<std::shared_ptr<BlockData>> blockData = model->getMap();
	if (event->getType() == "Tick Event")
	{
		
		updateMovementOfPlayer(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));
		updateBigDuration(std::dynamic_pointer_cast<PlayerData>(model->getPlayerData()));
		updateMovemenOfEnemy(enemies);

		for (auto block : blockData)
		{
			if (block->getIsBouncing())
			{
				updateBounceOfBlock(block);
			}
		}
		updateMouse();
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
	}

}

//void StageController::update(std::shared_ptr<Event> events)
//{
//    if (events->getType() == "Block Change Event")
//    {
//        std::shared_ptr<BlockChangeEvent> blockChange = std::dynamic_pointer_cast<BlockChangeEvent>(events);
//        BlockData* preBlock = blockChange->getPre();
//        std::shared_ptr<BlockData> newBlock = blockChange->getNew();
//
//
//        std::vector<std::shared_ptr<BlockData>> map = mode
//
//    }
//}

void Stage1Controller::updateMouse()
{
	if (model->getPauseButton()->isClicked(GetMousePosition()))
	{
		EventManager::getInstance().notify(std::make_shared<StateChangeEvent>("Pause"));
		return;
	}
}

void Stage1Controller::updateCamera()
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



