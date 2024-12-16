#include "StageModel.h"
#include <iostream>
StageModel::StageModel(std::shared_ptr<PlayerData> playerData, Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode )
    : StageModel(cameraInitPos,cameraTarget, fovy, cameraMode)
{
    m_playerData = playerData;
    //initializeCamera();
}

StageModel::StageModel(Vector3 cameraInitPos, Vector3 cameraTarget, float fovy, CameraProjection cameraMode)
{
	m_cameraInitialPosition = cameraInitPos;
	m_camera.position = cameraInitPos;
	m_camera.target = cameraTarget;
	m_camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	m_camera.fovy = fovy;
	m_camera.projection = cameraMode;

	Texture2D texture = LoadTexture("../../Assets/Icons/pause.png");
	Rectangle sourceRec = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
	Rectangle destRec = { 50.0f, 50.0f, 100.0f, 100.0f };
	m_pause = std::make_shared<Button>("", texture, sourceRec, destRec, Vector2{0.0f, 0.0f}, 0.0f, WHITE);
}

Camera3D& StageModel::getCamera()
{
    return m_camera;
}

void StageModel::setCamera(Camera3D camera)
{
    m_camera = camera;
}

std::shared_ptr<PlayerData> StageModel::getPlayerData() const
{
    return m_playerData;
}

std::shared_ptr<Button> StageModel::getPauseButton() const
{
    return m_pause;
}

std::shared_ptr<PlayerData> StageModel::createMarioModel(Vector3 position, Vector3 scale)
{
    std::shared_ptr<PlayerData> marioModel;
    std::shared_ptr<btDiscreteDynamicsWorld> dynamicsWorld = CollisionManager::getInstance()->getDynamicsWorld();

    Vector3 forwardDir = { 0.0f, 0.0f, 1.0f };
    Vector3 positionMario = position;
    Vector3 scaleMario = scale;
    Vector3 rotationAxisMario = { 0.0f, 1.0f, 0.0f };
    Model playerModel = LoadModel("../../Assets\\Models\\Characters\\Mario.glb");
    BoundingBox modelBounds = GetModelBoundingBox(playerModel);

    // Calculate the arm span (distance along the X-axis)
    float armSpan = (modelBounds.max.x - modelBounds.min.x) * scaleMario.x;

    // Set the capsule radius to half the arm span
    float radius = armSpan * 0.5f - 0.2f;

    // Calculate height of the capsule based on the model's bounding box
    float height = (modelBounds.max.y - modelBounds.min.y) * scaleMario.y - 1.0f; // Height of the model

    // Adjust height to exclude spherical parts of the capsule
    float capsuleHeight = height - radius;
    if (capsuleHeight < 0) {
        capsuleHeight = 0; // Prevent negative height
    }

    // Define initial transformation for the player
    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(btVector3(positionMario.x, positionMario.y, positionMario.z));

    // Create capsule shape
    std::shared_ptr<btCollisionShape> playerShape = std::make_shared<btCapsuleShape>(radius, capsuleHeight);

    // Physics body setup remains the same
    btScalar mass = 75.0f;
    btVector3 localInertia(0, 0, 0);
    playerShape->calculateLocalInertia(mass, localInertia);

    std::shared_ptr<btDefaultMotionState> motionState = std::make_shared<btDefaultMotionState>(btDefaultMotionState(startTransform));
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState.get(), playerShape.get(), localInertia);

    std::shared_ptr<btRigidBody> playerRigidBody = std::make_shared<btRigidBody>(rbInfo);

    std::string modelPath = "../../Assets\\Models\\Characters\\Mario.glb";
    marioModel = std::make_shared<PlayerData>(
        playerRigidBody,                               // std::shared_ptr<btRigidBody>
        playerShape,                                   // std::shared_ptr<btCollisionShape>
        motionState,								   // std::shared_ptr<btDefaultMotionState>
        modelPath,                                     // std::string
        forwardDir,                                    // Vector3
        positionMario,                                 // Vector3
        10.0f,                                         // float
        scaleMario,                                    // Vector3
        rotationAxisMario,                             // Vector3
        0.0f,                                          // float
        80000.0f,                                      // float
        100,                                           // int
        dynamicsWorld                                 // std::shared_ptr<btDynamicsWorld>
    );

    return marioModel;
}

