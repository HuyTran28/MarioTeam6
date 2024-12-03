#include "btBulletDynamicsCommon.h"
#include <BlockFactory.h>
#include "Stage1.h"
#include "Stage2.h"
#include <iostream>

btDiscreteDynamicsWorld* initializePhysics()
{
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
    btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
    dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

    // Create ground (make sure it's static)
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1); // A static plane at y = 0
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0))); // Set ground position at y = -1
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0)); // Mass is 0 to make it static
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    groundRigidBody->setFriction(1.0f);
    dynamicsWorld->addRigidBody(groundRigidBody);

    return dynamicsWorld;
}
void renderGround()
{
    DrawPlane(Vector3{ 110.0f, 0.0f, 0.0f }, Vector2{ 50.0f, 50.0f }, DARKGRAY);
}


int main()
{
    const int screenWidth = 1500;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Bullet and Raylib Example");



    Camera camera = { 0 };
    camera.position = { 200.0f, 20.0f, 50.0f };
    camera.target = { 200.0f, 0.0f, 0.0f };

    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 30.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    btDiscreteDynamicsWorld* dynamicsWorld = initializePhysics();

    Stage1 stage1(200, 2, 9, dynamicsWorld);
    //Stage2 stage2(110, 2, 9, dynamicsWorld);

	Model brick = LoadModel("Assets/Models/Platforms/BrickBlock.glb");



    SetTargetFPS(60);

    float cameraZ = 10.0f;
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        // Update
        dynamicsWorld->stepSimulation(GetFrameTime());
        /* cameraZ += 0.2;
         camera.position.x = cameraZ;*/

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);


        //stage2.draw();
        stage1.draw();
		DrawModel(brick, Vector3{ 0.0f, 5.0f, 0.0f }, 10.0f, WHITE);


        //renderGround();

        EndMode3D();
        EndDrawing();
    }

    //delete player;
    delete dynamicsWorld;

    CloseWindow();

    return 0;
}