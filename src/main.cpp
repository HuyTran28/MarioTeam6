#include "raylib.h"
#include "GameEngine.h"

int main()
{
	std::shared_ptr<GameEngine> gameEngine = std::make_shared<GameEngine>();
	gameEngine->run();
    return 0;
}