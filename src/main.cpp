#include "btBulletDynamicsCommon.h"
#include <BlockFactory.h>
#include "Stage1.h"
#include "Player.h"
#include "CollisionManager.h"
#include "EnemyFactory.h"
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

    // Create ground shape
    btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
    btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
    btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
    dynamicsWorld->addRigidBody(groundRigidBody);

    return dynamicsWorld;
}
void renderGround()
{
    DrawPlane(Vector3{ 0.0f, -1.0f, 0.0f }, Vector2{ 1000.0f, 1000.0f }, DARKGRAY);
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
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    btDiscreteDynamicsWorld* dynamicsWorld = initializePhysics();

    Stage1 stage1(200, 2, 9, dynamicsWorld);
    //Stage2 stage2(110, 2, 9, dynamicsWorld);

	//Player* mario = Player::createPlayer(dynamicsWorld, "Assets/Models/Characters/Mario.glb", {0, 10, 0}, {0, 0, 1}, 10.0f, 0.9f, 80000.0f, 100);
	Player* luigi = Player::createPlayer(dynamicsWorld, "Assets/Models/Characters/Luigi.glb", { 5, 10, 0 }, { 0, 0, 1 }, 15.0f, 0.9f, 100000.0f, 100);
	PatrollingEnemyAttributes patrolling1({ 0, 5, 10 }, { 0, 5, 20 });
    Enemy* koopa = EnemyFactory::createEnemy(EnemyType::Koopa, dynamicsWorld, "Assets/Models/Characters/Koopa.glb", { 0, 5, 5 }, { 0, 0, 1 }, 5.0f, 0.7f, &patrolling1);
    
    PatrollingEnemyAttributes patrolling({ 10, 4, 3 }, { 20, 4, 3 });
    Enemy* goomba = EnemyFactory::createEnemy(EnemyType::Patrolling, dynamicsWorld, "Assets/Models/Characters/Goomba.glb", { 10, 4, 3}, { 0, 0, 1 }, 5.0f, 0.8f, &patrolling);
    
    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);
        // Update
        dynamicsWorld->stepSimulation(GetFrameTime());
        Vector3 cameraOffset = { 0.0f, 5.0f, 10.0f }; // Offset behind and above the player
        camera.position = Vector3Add(luigi->getPosition(), cameraOffset);
        camera.target = luigi->getPosition(); // Camera always looks at the player
        float zoomSpeed = 5.0f; // How fast the zoom changes
        camera.fovy -= GetMouseWheelMove() * zoomSpeed;

        // Clamp FOV to prevent extreme zoom
        if (camera.fovy < 10.0f) camera.fovy = 10.0f; // Minimum zoom-in
        if (camera.fovy > 90.0f) camera.fovy = 90.0f; // Maximum zoom-out
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

		// Update
        CollisionManager collisionManager(dynamicsWorld);
        collisionManager.detectCollisions();
        //mario->update();
        luigi->update();
		
		koopa->update();
		goomba->update();

        //stage2.draw();
        stage1.draw();
		//mario->render();
		luigi->render();
		
		goomba->render();
		koopa->render();
		renderGround();

        EndMode3D();
        EndDrawing();
    }

    //delete player;
    delete dynamicsWorld;

    CloseWindow();

    return 0;
}