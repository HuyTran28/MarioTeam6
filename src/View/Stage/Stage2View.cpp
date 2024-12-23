#include "Stage2View.h"


Stage2View::Stage2View()
{
    m_model = std::make_shared<Stage2Model>();

}

Stage2View::Stage2View(std::shared_ptr<Stage2Model> model) : m_model(model) {}



void Stage2View::render()
{
    std::vector<std::shared_ptr<BlockData>> map = m_model->getMap();
    std::vector<std::shared_ptr<Enemy>> enemies = m_model->getEnemies();
    std::vector<std::shared_ptr<ItemData>> items = m_model->getItems();


    std::shared_ptr<PlayerData> marioModel = std::dynamic_pointer_cast<PlayerData>(m_model->getPlayerData());

    Camera3D& camera = m_model->getCamera();
    UpdateCamera(&camera, CAMERA_CUSTOM);


    BeginDrawing();
    ClearBackground(SKYBLUE);

    BeginMode3D(m_model->getCamera());


    //renderClouds();

    renderCharacter();
    StateView::renderBlocks(map, m_model->getCamera());
    StateView::renderEnemies(enemies, m_model->getCamera());
    StateView::renderItems(items, m_model->getCamera());
    

    std::cout << m_model->getPlayerData()->getPlayerPos().x << " " << m_model->getPlayerData()->getPlayerPos().y << " " << m_model->getPlayerData()->getPlayerPos().z << '\n';
    m_model->setCamera(m_model->getCamera());




    EndMode3D();

    renderHealth(marioModel, m_model->getHealthButton());
    renderCoin(m_model->getCoins());
    renderTimer(m_model->getTimer(), m_model->getTimerButton());
    renderScore(m_model->getScore());

    m_model->getPauseButton()->draw();
    m_model->getSettingButton()->draw();

    EndDrawing();
}

void Stage2View::renderClouds()
{
    for (int i = 0; i < m_model->getClouds().size(); i++) {
        DrawModelEx(m_model->getClouds()[i], m_model->getCloudPositions()[i], m_model->getCloudRotationsAxis(), m_model->getCloudRotationsAngle()[i], m_model->getCloudScales(), WHITE);
    }

    DrawModelEx(m_model->getHills(), m_model->getHillsPosition(), m_model->getHillsRotationAxis(), m_model->getHillsRotationAngle(), m_model->getHillsScale(), WHITE);
}

void Stage2View::renderCharacter()
{
    std::shared_ptr<PlayerData> marioModel = std::dynamic_pointer_cast<PlayerData>(m_model->getPlayerData());
    DrawModelEx(marioModel->getPlayerModel(), marioModel->getPlayerPos(), marioModel->getPlayerRotationAxis(), marioModel->getPlayerRotationAngle(),
        marioModel->getPlayerScale(), WHITE);
}

void Stage2View::update(std::shared_ptr<Event> event)
{
    if (event->getType() == "Tick Event")
    {
        render();
    }
}

void Stage2View::registerSelf()
{
	EventManager::getInstance().addObserver(shared_from_this());
}
