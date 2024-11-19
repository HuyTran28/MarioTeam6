#include "Menu.h"

Menu::Menu()
{
    cameraInitialPosition = Vector3{ 0.0f, 20.0f, 0.0f };
    camera.position = cameraInitialPosition;
    camera.target = Vector3{ -20.0f, 30.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    lobbyModel = LoadModel("C:\\Users\\ASUS\\OneDrive - VNU-HCMUS\\MarioTeam6\\Assets\\Models\\Lobby\\lobby.obj");

    playerModel = LoadModel("C:\\Users\\ASUS\\OneDrive - VNU-HCMUS\\MarioTeam6\\Assets\\Models\\Platforms\\Prop_Block_Brick.obj");

    playerPosition = Vector3{ 0.0f, 0.0f, 0.0f };

	playerBox = GetModelBoundingBox(playerModel);

    BoundingBox modelBox = GetModelBoundingBox(lobbyModel);
    modelBox.max.y -= 600.0f; // Adjust the bounding box height as needed

    lobbyBox[4] = modelBox;
    lobbyBox[4].max.x -= 450.0f;
    lobbyBox[4].min.x += 450.0f;

    lobbyBox[5] = modelBox;
    lobbyBox[5].max.z -= 400.0f;
    lobbyBox[5].min.z += 400.0f;

    // Define the bounding boxes for the walls

    // Left wall
    lobbyBox[0] = BoundingBox{
        Vector3{ modelBox.min.x + 30.0f, modelBox.min.y, modelBox.min.z },
        Vector3{ modelBox.min.x, modelBox.max.y + 4000.0f, modelBox.max.z }
    };

    // Right wall
    lobbyBox[1] = BoundingBox{
        Vector3{ modelBox.max.x - 70.0f, modelBox.min.y, modelBox.min.z },
        Vector3{ modelBox.max.x, modelBox.max.y + 4000.0f, modelBox.max.z }
    };

    // Front wall
    lobbyBox[2] = BoundingBox{
        Vector3{ modelBox.min.x, modelBox.min.y, modelBox.min.z + 30.0f },
        Vector3{ modelBox.max.x, modelBox.max.y + 4000.0f, modelBox.min.z }
    };

    // Back wall
    lobbyBox[3] = BoundingBox{
        Vector3{ modelBox.min.x, modelBox.min.y, modelBox.max.z - 70.0f},
        Vector3{ modelBox.max.x, modelBox.max.y + 4000.0f , modelBox.max.z }
    };
    lobbyBox[6] = BoundingBox{
        Vector3{ modelBox.max.x - 2300.0f, modelBox.max.y, modelBox.max.z - 1000.0f},
        Vector3{ modelBox.max.x - 1800.0f, modelBox.max.y + 600.0f, modelBox.min.z + 250.0f }
    };

    lobbyBox[7] = BoundingBox{
        Vector3{ modelBox.max.x - 1800.0f, modelBox.max.y + 400.0f, modelBox.max.z - 1000.0f},
        Vector3{ modelBox.max.x - 1400.0f, modelBox.max.y + 600.0f, modelBox.min.z + 250.0f }
    };

    // Initialize 3D buttons
    playButtonBox = { Vector3{ -15.0f, modelBox.max.y + 50.0f, 55.0f }, Vector3{ 50.0f, 10.0f, 75.0f } };
    exitButtonBox = { Vector3{ -15.0f, modelBox.max.y + 50.0f, -95.0f }, Vector3{ 50.0f, 10.0f, -115.0f } };

    normalColor = GRAY;
    hoverColor = LIGHTGRAY;

    playButtonColor = normalColor;
    exitButtonColor = normalColor;
}

Menu::~Menu()
{
    UnloadModel(lobbyModel);
	UnloadModel(playerModel);
}

void Menu::updateMovement()
{

    float moveSpeed = 1.0f; // Increased movement speed in units per frame

    // Calculate direction vector from camera position to target
    Vector3 direction = Vector3Subtract(camera.target, camera.position);
    float length = Vector3Length(direction);

    // Normalize the direction vector to avoid NaN values
    if (length != 0.0f) {
        direction = Vector3Scale(direction, 1.0f / length);
    }

    float xChange = moveSpeed * direction.x;
    float zChange = moveSpeed * direction.z;

    // WASD controls for movement
    if (IsKeyDown(KEY_W)) {
        playerPosition.x += xChange;
        playerPosition.z += zChange;
    }

    if (IsKeyDown(KEY_S)) {
        playerPosition.x -= xChange;
        playerPosition.z -= zChange;
    }

    if (IsKeyDown(KEY_A)) {
        playerPosition.x += zChange;
        playerPosition.z -= xChange;
    }

    if (IsKeyDown(KEY_D)) {
        playerPosition.x -= zChange;
        playerPosition.z += xChange;
    }

    // hit space to jump
    if (IsKeyDown(KEY_SPACE))
    {
        playerPosition.y += 10.0f;
    }

    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        playerPosition.y -= 10.0f;
    }

    // Update camera position based on player position
    camera.position = Vector3Add(playerPosition, cameraInitialPosition);
    // Update the camera target to avoid NaN values
    camera.target = Vector3Add(camera.position, direction);
}

void Menu::update()
{

    Vector3 oldPosition = playerPosition;

	updateMovement();
    // Check for collisions with the walls
    playerBox = GetModelBoundingBox(playerModel);
    playerBox.min = Vector3Add(playerPosition, playerBox.min);
    playerBox.max = Vector3Add(playerPosition, playerBox.max);

    for (int i = 0; i < 4; i++)
    {
        if (CheckCollisionBoxes(playerBox, lobbyBox[i]))
        {
            playerPosition = oldPosition; // Revert to the old position if a collision is detected
            break;
        }
    }

    UpdateCamera(&camera, CAMERA_FIRST_PERSON);
}

bool CheckCollisionRayBox(Ray ray, BoundingBox box)
{
    float tmin = (box.min.x - ray.position.x) / ray.direction.x;
    float tmax = (box.max.x - ray.position.x) / ray.direction.x;

    if (tmin > tmax) std::swap(tmin, tmax);

    float tymin = (box.min.y - ray.position.y) / ray.direction.y;
    float tymax = (box.max.y - ray.position.y) / ray.direction.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax))
        return false;

    if (tymin > tmin)
        tmin = tymin;

    if (tymax < tmax)
        tmax = tymax;

    float tzmin = (box.min.z - ray.position.z) / ray.direction.z;
    float tzmax = (box.max.z - ray.position.z) / ray.direction.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax))
        return false;

    if (tzmin > tmin)
        tmin = tzmin;

    if (tzmax < tmax)
        tmax = tzmax;

    return ((tmin < 0) && (tmax > 0)) || ((tmin > 0) && (tmax > 0));
}


void Menu::draw()
{
    BeginMode3D(camera);
    // Draw the lobby model
    Vector3 modelPosition = Vector3{ 0.0f, 0.0f, 0.0f };
    Vector3 modelScale = Vector3{ 0.1f, 0.1f, 0.1f };
    DrawModelEx(lobbyModel, modelPosition, Vector3{ 0.0f, 1.0f, 0.0f }, 0.0f, modelScale, WHITE);

    // Draw the player's model
    DrawModelEx(playerModel, playerPosition, Vector3{ 0.0f, 1.0f, 0.0f }, 0.0f, Vector3{ 10.0f, 10.0f, 10.0f }, WHITE);

    // Draw the bounding boxes for the walls
    for (int i = 0; i < 8; i++)
    {
        BoundingBox transformedBox = {
            Vector3Add(Vector3Scale(lobbyBox[i].min, modelScale.x), modelPosition),
            Vector3Add(Vector3Scale(lobbyBox[i].max, modelScale.x), modelPosition)
        };
        DrawBoundingBox(transformedBox, RED);
    }

    // Create a ray from the camera position to the camera target
    Ray ray = { camera.position, Vector3Normalize(Vector3Subtract(camera.target, camera.position)) };
    // Check for intersection with the play button
    if (CheckCollisionRayBox(ray, playButtonBox)) playButtonColor = hoverColor;
    else playButtonColor = normalColor;

    // Check for intersection with the exit button
    if (CheckCollisionRayBox(ray, exitButtonBox)) exitButtonColor = hoverColor;
    else exitButtonColor = normalColor;

    Vector3 playButtonCenter = Vector3{ (playButtonBox.min.x + playButtonBox.max.x) / 2, (playButtonBox.min.y + playButtonBox.max.y) / 2, (playButtonBox.min.z + playButtonBox.max.z) / 2 };
    Vector3 exitButtonCenter = Vector3{ (exitButtonBox.min.x + exitButtonBox.max.x) / 2, (exitButtonBox.min.y + exitButtonBox.max.y) / 2, (exitButtonBox.min.z + exitButtonBox.max.z) / 2 };

    DrawCube(playButtonCenter, playButtonBox.max.x - playButtonBox.min.x, playButtonBox.max.y - playButtonBox.min.y, playButtonBox.max.z - playButtonBox.min.z, playButtonColor);
    DrawCube(exitButtonCenter, exitButtonBox.max.x - exitButtonBox.min.x, exitButtonBox.max.y - exitButtonBox.min.y, exitButtonBox.max.z - exitButtonBox.min.z, exitButtonColor);

    EndMode3D();

    // Convert Vector3 to Vector2 for text position using GetWorldToScreen
    Vector2 playButtonTextPosition = GetWorldToScreen(playButtonCenter, camera);
    Vector2 exitButtonTextPosition = GetWorldToScreen(exitButtonCenter, camera);

    // Draw 3D text on the buttons
    DrawTextEx(GetFontDefault(), "Play", playButtonTextPosition, 20, 2, BLACK);
    DrawTextEx(GetFontDefault(), "Exit", exitButtonTextPosition, 20, 2, BLACK);

    // Draw crosshair at the center of the screen
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;
    int crosshairSize = 20;

    DrawLine(centerX - crosshairSize, centerY, centerX + crosshairSize, centerY, BLACK); // Horizontal line
    DrawLine(centerX, centerY - crosshairSize, centerX, centerY + crosshairSize, BLACK); // Vertical line
}





