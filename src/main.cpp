#include "raylib.h"
#include "GameEngine.h"
#include "btBulletDynamicsCommon.h"

int main()
{
    std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
    gameEngine->run();
    return 0;
}

//int main()
//{
//    const int screenwidth = 1500;
//    const int screenheight = 600;
//
//    InitWindow(screenwidth, screenheight, "Bullet and Raylib Example");
//    
//    Camera camera = { 0 };
//    camera.position = { 0.0f, 5.0f, 5.0f };
//    camera.target = { 0.0f, 0.0f, 0.0f };
//
//    camera.up = { 0.0f, 1.0f, 0.0f };
//    camera.fovy = 45.0f;
//    camera.projection = CAMERA_PERSPECTIVE;
//   
//    Model model = LoadModel("../../assets\\models\\platforms\\Island.glb");
//
//    while (!WindowShouldClose())
//    {
//        UpdateCamera(&camera, CAMERA_FREE);
//      
//       
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//
//        BeginMode3D(camera);
//       //d DrawModel(model, { 0.0f, 0.0f, 0.0f }, 2.0f, WHITE);
//        DrawModelEx(model, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, -90.0f, { 2.0f, 2.0f, 2.0f }, WHITE);
//        
//
//        EndMode3D();
//        EndDrawing();
//    }
//
//
//
//    CloseWindow();
//
//    return 0;
//}

