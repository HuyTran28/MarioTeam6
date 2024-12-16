#pragma once
#include "StageController.h"
#include "../Model/MenuModel.h"
#include "../Event/KeyboardEvent.h"
#include "../Event/MouseClickedEvent.h"
#include <raymath.h>
#include "../Event/StateChangeEvent.h"



class MenuController : public StageController, public std::enable_shared_from_this<MenuController>
{
public:
	MenuController();
	MenuController(std::shared_ptr<MenuModel> model);
	void registerSelf() override;
	void update(std::shared_ptr<Event> event) override;
	void updateCamera();
	void updateGameState();
	~MenuController();
private:
	std::shared_ptr<MenuModel> model;
	float verticalOffset = 0.0f;	
	bool CheckCollisionRayBox(Ray ray, BoundingBox box);
	bool IsMouseOver3DObject(Camera3D camera, BoundingBox box);
};