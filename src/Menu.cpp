#include "Menu.h"

Menu::Menu()
{
	camera.position = Vector3{ 100.0f, 100.0f, 100.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 60.0f;
	camera.projection = CAMERA_PERSPECTIVE;

	lobbyModel = LoadModel("C:\\Users\\ASUS\\OneDrive - VNU-HCMUS\\MarioTeam6\\Assets\\Models\\Lobby\\lobby.obj");

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

}

Menu::~Menu()
{
	UnloadModel(lobbyModel);
}

void Menu::update()
{
	float moveSpeed = 1.0f; // Movement speed in units per frame
	// WASD controls for movement
	if (IsKeyDown(KEY_W)) camera.position.z -= moveSpeed;
	if (IsKeyDown(KEY_S)) camera.position.z += moveSpeed;
	if (IsKeyDown(KEY_A)) camera.position.x -= moveSpeed;
	if (IsKeyDown(KEY_D)) camera.position.x += moveSpeed;

	// Vertical movement (optional)
	if (IsKeyDown(KEY_SPACE)) camera.position.y += moveSpeed;      // Move up
	if (IsKeyDown(KEY_LEFT_SHIFT)) camera.position.y -= moveSpeed; // Move down

	// Update target position to always look at the origin or the model center
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	UpdateCamera(&camera, CAMERA_CUSTOM); // Update camera based on user input
}

void Menu::draw()
{
	BeginMode3D(camera);
	// Draw the model
	Vector3 modelPosition = Vector3{ 0.0f, 0.0f, 0.0f };
	Vector3 modelScale = Vector3{ 0.1f, 0.1f, 0.1f };
	DrawModelEx(lobbyModel, modelPosition, Vector3{ 0.0f, 1.0f, 0.0f }, 0.0f, modelScale, WHITE);
	// Transform the bounding box to match the model's transformation
	for (int i = 0; i < 8; i++)
	{
		BoundingBox transformedBox = {
			Vector3Add(Vector3Scale(lobbyBox[i].min, modelScale.x), modelPosition),
			Vector3Add(Vector3Scale(lobbyBox[i].max, modelScale.x), modelPosition)
		};
		DrawBoundingBox(transformedBox, RED);
	}




	// Draw the bounding box
	EndMode3D();
}

