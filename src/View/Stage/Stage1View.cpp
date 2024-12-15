#include "Stage1View.h"
#include <iostream>

Stage1View::Stage1View()
{
    m_model = std::make_shared<Stage1Model>();

}


Stage1View::Stage1View(std::shared_ptr<Stage1Model> model) : m_model(model) {}

void Stage1View::render()
{

    std::vector<std::shared_ptr<BlockData>> map = m_model->getMap();
    std::vector<std::shared_ptr<Enemy>> enemies = m_model->getEnemies();

    std::shared_ptr<PlayerData> marioModel = std::dynamic_pointer_cast<PlayerData>(m_model->getPlayerData());
    //UpdateCamera(&(m_model->getCamera()), CAMERA_FIRST_PERSON);

    Camera3D& camera = m_model->getCamera();
    UpdateCamera(&camera, CAMERA_CUSTOM);

    BeginDrawing();
    ClearBackground(BLUE);

    BeginMode3D(m_model->getCamera());

    StateView::renderBlocks(m_model->getMap());

	renderClouds();

	renderCharacter();
    StateView::renderBlocks(map);
    StateView::renderEnemies(enemies);
    for (int i = 0; i < m_model->getClouds().size(); i++) {
		DrawModelEx(m_model->getClouds()[i], m_model->getCloudPositions()[i], m_model->getCloudRotationsAxis(), m_model->getCloudRotationsAngle()[i], m_model->getCloudScales(), WHITE);
    }


	DrawModelEx(m_model->getHills(), m_model->getHillsPosition(), m_model->getHillsRotationAxis(), m_model->getHillsRotationAngle(), m_model->getHillsScale(), WHITE);
    DrawModelEx(marioModel->getPlayerModel(), marioModel->getPlayerPos(), marioModel->getPlayerRotationAxis(), marioModel->getPlayerRotationAngle(),
        marioModel->getPlayerScale(), WHITE);

    m_model->setCamera(m_model->getCamera());
  //  std::cout << marioModel->getPlayerPos().x << " " << marioModel->getPlayerPos().y <<" " << marioModel->getPlayerPos().z << '\n';


    btCollisionShape* shape = m_model->getPlayerData()->getRigidBody()->getCollisionShape();
    btTransform transform;
    m_model->getPlayerData()->getRigidBody()->getMotionState()->getWorldTransform(transform);
    btVector3 origin = transform.getOrigin();
    btQuaternion rotation = transform.getRotation();
    Vector3 boxPosition = { origin.getX(), origin.getY(), origin.getZ() };
    Quaternion boxRotation = { rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW() };
    if (shape->getShapeType() == BOX_SHAPE_PROXYTYPE) {
        btBoxShape* boxShape = static_cast<btBoxShape*>(shape);
        btVector3 halfExtents = boxShape->getHalfExtentsWithMargin();
        Vector3 boxSize = { halfExtents.getX() * 2, halfExtents.getY() * 2, halfExtents.getZ() * 2 };
    }

    EndMode3D();

    m_model->getPauseButton()->draw();

    EndDrawing();
}

void Stage1View::update(std::shared_ptr<Event> event)
{

    if (event->getType() == "Tick Event")
    {
        render();
    }
}

void Stage1View::registerSelf()
{
    EventManager::getInstance().addObserver(shared_from_this());
}

void Stage1View::renderClouds()
{
    for (int i = 0; i < m_model->getClouds().size(); i++) {
        DrawModelEx(m_model->getClouds()[i], m_model->getCloudPositions()[i], m_model->getCloudRotationsAxis(), m_model->getCloudRotationsAngle()[i], m_model->getCloudScales(), WHITE);
    }

    DrawModelEx(m_model->getHills(), m_model->getHillsPosition(), m_model->getHillsRotationAxis(), m_model->getHillsRotationAngle(), m_model->getHillsScale(), WHITE);
}

void Stage1View::renderCharacter()
{
    std::shared_ptr<PlayerData> marioModel = std::dynamic_pointer_cast<PlayerData>(m_model->getPlayerData());
    DrawModelEx(marioModel->getPlayerModel(), marioModel->getPlayerPos(), marioModel->getPlayerRotationAxis(), marioModel->getPlayerRotationAngle(),
        marioModel->getPlayerScale(), WHITE);
}
