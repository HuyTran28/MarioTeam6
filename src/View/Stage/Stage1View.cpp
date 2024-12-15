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

    Vector3 cameraOffset = { 0.0f, 10.0f, 40.0f };
    camera.position = Vector3Add(marioModel->getPlayerPos(), cameraOffset);
    camera.target = marioModel->getPlayerPos();  

    float zoomSpeed = 5.0f;
    camera.fovy -= GetMouseWheelMove() * zoomSpeed;
    if (camera.fovy < 10.0f) camera.fovy = 10.0f; 
    if (camera.fovy > 90.0f) camera.fovy = 90.0f; 
    UpdateCamera(&camera, CAMERA_CUSTOM);




    BeginDrawing();
    ClearBackground(BLUE);

    BeginMode3D(m_model->getCamera());


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

        //DrawCube(boxPosition, boxSize.x, boxSize.y, boxSize.z, RED); // Draw the box in red
        DrawCubeWires(boxPosition, boxSize.x, boxSize.y, boxSize.z, BLACK); // Draw the box wireframe in black
    }
    else if (shape->getShapeType() == CAPSULE_SHAPE_PROXYTYPE) {
        btCapsuleShape* capsuleShape = static_cast<btCapsuleShape*>(shape);

        // Get the bounding box of the model
        BoundingBox modelBounds = GetModelBoundingBox(m_model->getPlayerData()->getPlayerModel());
        float modelHeight = (modelBounds.max.y - modelBounds.min.y) * 0.9;
        float modelRadius = std::max((modelBounds.max.x - modelBounds.min.x), (modelBounds.max.z - modelBounds.min.z)) * 0.9 / 2.0f;

        // Adjust the capsule size to wrap around the model
        float radius = modelRadius * 1.1f; // Slightly larger than the model radius
        float halfHeight = (modelHeight / 2.0f) - radius;

        Vector3 startPos = { boxPosition.x, boxPosition.y - halfHeight, boxPosition.z };
        Vector3 endPos = { boxPosition.x, boxPosition.y + halfHeight, boxPosition.z };
        //DrawCapsule(startPos, endPos, radius, RED); // Draw the capsule in red
        DrawCapsuleWires(startPos, endPos, radius, 16, 16, BLACK); // Draw the capsule wireframe in black
    }
    // Add handling for other shape types here
    else if (shape->getShapeType() == SPHERE_SHAPE_PROXYTYPE) {
        btSphereShape* sphereShape = static_cast<btSphereShape*>(shape);
        float radius = sphereShape->getMargin(); // Assuming margin is the radius
        //DrawSphere(boxPosition, radius, RED); // Draw the sphere in red
        DrawSphereWires(boxPosition, radius, 16, 16, BLACK); // Draw the sphere wireframe in black
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
