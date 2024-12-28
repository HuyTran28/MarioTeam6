#include "Stage3View.h"


Stage3View::Stage3View()
{
    m_model = std::make_shared<Stage3Model>();

}

Stage3View::Stage3View(std::shared_ptr<Stage3Model> model) : m_model(model) {}



void Stage3View::render()
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


    renderCharacter();
    StateView::renderBlocks(map, m_model->getCamera());
    StateView::renderEnemies(enemies, m_model->getCamera());
    randomEnemy(enemies, m_model->getCamera());
    m_model->setEnemies(enemies);
    StateView::renderItems(items, m_model->getCamera());
    randomItem(items, m_model->getCamera());
    m_model->setItems(items);


    std::cout << m_model->getPlayerData()->getPlayerPos().x << " " << m_model->getPlayerData()->getPlayerPos().y << " " << m_model->getPlayerData()->getPlayerPos().z << '\n';

    if (m_model->getBoomerang()->getIsvisble())
    {
        btTransform transform;
        m_model->getBoomerang()->getRigidBody()->getMotionState()->getWorldTransform(transform);
        btQuaternion rotation = transform.getRotation();
        Vector3 rotationAxis = { (float)rotation.getAxis().getX(),
                                 (float)rotation.getAxis().getY(),
                                 (float)rotation.getAxis().getZ() };
        float rotationAngleDeg = btDegrees(rotation.getAngle());


        DrawModelEx(m_model->getBoomerang()->getModel(), m_model->getBoomerang()->getPosition(), rotationAxis, rotationAngleDeg,
            { m_model->getBoomerang()->getScale().x, m_model->getBoomerang()->getScale().y, m_model->getBoomerang()->getScale().z }, WHITE);
    }


    EndMode3D();

    renderHealth(marioModel, m_model->getHealthButton());
    renderCoin(m_model->getCoins());
    renderTimer(m_model->getTimer(), m_model->getTimerButton());
    renderScore(m_model->getScore());

    m_model->getPauseButton()->draw();
    m_model->getSettingButton()->draw();

    EndDrawing();
}




void Stage3View::randomEnemy(std::vector<std::shared_ptr<Enemy>>& enemies, Camera3D cam)
{
    Vector3 rotaionAxisGoomba = { 0.0f, 1.0f, 0.0f };
    float rotationAngleGoomba = 0.0f;

    Vector3 rotaionAxisKoopa = { 0.0f, 1.0f, 0.0f };
    float rotationAngleKoopa = 0.0f;

    Vector3 scaleGoomba = { 1.0f, 1.0f, 1.0f };
    Vector3 scaleKoopa = { 0.8f, 0.8f, 0.8f };

    Vector3 forwardDirGoomba = { 0, 0, 1 };
    Vector3 forwardDirKoopa = { 0, 0, 1 };

    float speedGooba = 5.0f;
    float speedKoopa = 5.0f;

    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();
    auto addEnemy = [&](EnemyType type, const std::string& path, const Vector3& position, const Vector3& forwardDir, const Vector3& scale,
        const Vector3& pointA, const Vector3& pointB, const float& speed, const Vector3& rotationAxis, const float& rotationAngle)
        {
            auto enemy = EnemyFactory::createEnemy(type, dynamicsWorld, path, position, forwardDir, rotationAxis, rotationAngle, scale, speed, pointA, pointB);
            if (enemy)
                enemies.push_back(enemy);
        };

    std::vector<Vector3> position1 = { { 26, 1, -28 }, { 26, 1, 31 }, { 20, 1, 33 }, { -25, 1, 33 }, { 20, 1, -32 }, { -24, 1, -32 } };
    std::vector<Vector3> position2 = { { 27, 1, 1 }, { 27, 1, 1 }, { -3, 1, 33 }, { -3, 1, 33 }, { -2, 1, -32 }, { -2, 1, -32 } };

    static auto lastSpawnTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();

    auto positionExists = [&](const Vector3& pos) {
        for (auto enemy : enemies)
        {
            if (enemy->getPointA() == pos)
                return false;
        }
        return true;
        };

    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastSpawnTime).count() >= 15)
    {
        lastSpawnTime = currentTime;

        for (size_t i = 0; i < position1.size(); ++i)
        {
            if ( positionExists(position1[i]) == true)
            {
                if (i == 4 || i == 5)
                {
                    addEnemy(EnemyType::Koopa, PATH_KOOPA, position1[i], forwardDirKoopa, scaleKoopa, position1[i], position2[i], speedKoopa, rotaionAxisKoopa, rotationAngleKoopa);
                }
                else
                {
                    addEnemy(EnemyType::Goomba, PATH_GOOMBA, position1[i], forwardDirGoomba, scaleGoomba, position1[i], position2[i], speedGooba, rotaionAxisGoomba, rotationAngleGoomba);
                }
         
            }
        }
    }

}

void Stage3View::randomItem(std::vector<std::shared_ptr<ItemData>>& items, Camera3D cam)
{
    Vector3 rotaionAxis = {0.0f, 1.0f, 0.0f};
    float rotationAngle = 0.0f;
    Vector3 scale = { 1.0f, 1.0f, 1.0f };

    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();

    auto addItem = [&](ItemType type, const std::string& modelPath, const Vector3& position, const Vector3& scale,
        const Vector3& rotationAxis, float rotationAngle, std::shared_ptr<btDiscreteDynamicsWorld> world)
        {
            auto item = ItemFactory::createItem(type, position, modelPath, scale, rotationAxis, rotationAngle, world);
            if (item)
                items.push_back(item);
        };


    std::vector<Vector3> position1 = { { -36, 3, 24 }, { -36, 3, -22 }, { 18, 3, -22 }, { 16, 3, 26 }, { 0, 3, 25 }, { 0, 3, -25 } };


    static auto lastSpawnTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();

    auto positionExists = [&](const Vector3& pos) {
        for (auto item : items)
        {
            if (item->getPosition() == pos)
                return false;
        }
        return true;
        };

    if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastSpawnTime).count() >= 15)
    {
        lastSpawnTime = currentTime;

        for (size_t i = 0; i < position1.size(); ++i)
        {
            if (positionExists(position1[i]) == true)
            {
                if (i == 0)
                {
                    addItem(ItemType::COIN, PATH_COIN, position1[i], scale, rotaionAxis, -90.0f, dynamicsWorld);
                }
                else if (i == 1)
                {
                    addItem(ItemType::RED_MUSHROOM, PATH_REDMUSHROOM, position1[i], scale, rotaionAxis, -90.0f, dynamicsWorld);
                }
                else if (i == 2)
                {
                    addItem(ItemType::GREEN_MUSHROOM, PATH_GREENMUSHROOM, position1[i], scale, rotaionAxis, -90.0f, dynamicsWorld);

                }
                else if (i == 3)
                {
                    addItem(ItemType::BOOMERANG_FLOWER, PATH_BOOMERANGFLOWER, position1[i], scale, rotaionAxis, -90.0f, dynamicsWorld);

                }
                else if (i == 4)
                {
                    addItem(ItemType::COIN, PATH_COIN, position1[i], scale, rotaionAxis, -90.0f, dynamicsWorld);

                }
                else if (i == 5)
                {
                    addItem(ItemType::COIN, PATH_COIN, position1[i], scale, rotaionAxis, -90.0f, dynamicsWorld);

                }

            }
        }
    }
}

void Stage3View::renderClouds()
{
    for (int i = 0; i < m_model->getClouds().size(); i++) {
        DrawModelEx(m_model->getClouds()[i], m_model->getCloudPositions()[i], m_model->getCloudRotationsAxis(), m_model->getCloudRotationsAngle()[i], m_model->getCloudScales(), WHITE);
    }

    DrawModelEx(m_model->getHills(), m_model->getHillsPosition(), m_model->getHillsRotationAxis(), m_model->getHillsRotationAngle(), m_model->getHillsScale(), WHITE);
}

void Stage3View::renderCharacter()
{
    std::shared_ptr<PlayerData> marioModel = std::dynamic_pointer_cast<PlayerData>(m_model->getPlayerData());
    DrawModelEx(marioModel->getPlayerModel(), marioModel->getPlayerPos(), marioModel->getPlayerRotationAxis(), marioModel->getPlayerRotationAngle(),
        marioModel->getPlayerScale(), WHITE);
}

void Stage3View::update(std::shared_ptr<Event> event)
{
    if (event->getType() == "Tick Event")
    {
        render();
    }
}

void Stage3View::registerSelf()
{
    EventManager::getInstance().addObserver(shared_from_this());
}
