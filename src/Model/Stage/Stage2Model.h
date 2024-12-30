#pragma once
#include "StageModel.h"
#include <vector>
#include "btBulletDynamicsCommon.h"
#include "../../Model/Character/Player/PlayerData.h"
#include "../../CollisionManager/CollisionManager.h"

class Stage2Model : public StageModel
{
private:
	Model volcano;
	Vector3 volcanoPosition;
	Vector3 volcanoScale;
	Vector3 volcanoRotationAxis;
	float volcanoRotationAngle;

	Model BowserCastle;
	Vector3 BowserCastlePosition;
	Vector3 BowserCastleScale;
	Vector3 BowserCastleRotationAxis;
	float BowserCastleRotationAngle;



public:
	Stage2Model();
	Stage2Model(int continu);
	~Stage2Model();

	std::vector<std::shared_ptr<BlockData>> createMap();
	std::vector<std::shared_ptr<Enemy>> createEnemies();
	std::vector<std::shared_ptr<ItemData>> createItems();
	

	std::shared_ptr<Button> getPauseButton() const;
	Model getVolcano() const;
	Vector3 getVolcanoPosition() const;
	Vector3 getVolcanoScale() const;
	Vector3 getVolcanoRotationAxis() const;
	float getVolcanoRotationAngle() const;
	Model getBowserCastle() const;
	Vector3 getBowserCastlePosition() const;
	Vector3 getBowserCastleScale() const;
	Vector3 getBowserCastleRotationAxis() const;
	float getBowserCastleRotationAngle() const;
};

