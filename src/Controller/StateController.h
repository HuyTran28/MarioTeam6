#pragma once

#include <string>
#include "../Event/Event.h"
#include "../Observer/IObserver.h"
#include <raylib.h>

class StateController : public IObserver
{
public:
	virtual ~StateController() = default;
	virtual void registerSelf() = 0;

	bool isIconClicked(Texture2D icon, Vector2 position, float scale)
	{
		// Define the destination rectangle (where the icon is drawn on the screen)
		Rectangle destRec = { position.x, position.y, icon.width * scale, icon.height * scale };

		// Get the current mouse position
		Vector2 mousePosition = GetMousePosition();

		// Check if the mouse is over the icon and if the left mouse button is pressed
		return CheckCollisionPointRec(mousePosition, destRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
	}
};