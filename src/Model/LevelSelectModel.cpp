#include "LevelSelectModel.h"

LevelSelectModel::LevelSelectModel()
{
	background = LoadTexture("../../Assets\\Images\\SelectLevel.png");
	backgroundScale = GetScreenHeight() / (background.height - 0.5f);
	backgroundPos = { (float)GetScreenWidth() / 2.0f - background.width / 2.0f * backgroundScale, (float)GetScreenHeight() / 2.0f - background.height / 2.0f * backgroundScale};

	level1Texture = LoadTexture("../../Assets\\Images\\island.png");
	srcRecLevel1 = { 0.0f, 0.0f, (float)level1Texture.width, (float)level1Texture.height };
	destRecLevel1 = { 503.0f, 141.0f, 752.0f - 503.0f, 321.0f - 141.0f };
	destRecColorLevel1 = WHITE;
	originLevel1 = { 0.0f, 0.0f };

	//level2Pos = { 100, 300 };
	//level2Texture = LoadTexture("res/level2.png");
	//level2Frame = LoadTexture("res/levelFrame.png");
	//level2TexturePos = { level2Pos.x + 10, level2Pos.y + 10 };
	//level2TextureScale = 0.5f;

	//level3Pos = { 100, 500 };
	//level3Texture = LoadTexture("res/level3.png");
	//level3Frame = LoadTexture("res/levelFrame.png");
	//level3TexturePos = { level3Pos.x + 10, level3Pos.y + 10 };
	//level3TextureScale = 0.5f;

	backArrow = LoadTexture("..\\..\\Assets\\Icons\\back-arrow.png");
	backArrowPosition = { 50.0f, 50.0f };
	backArrowScale = 0.2f;
}

LevelSelectModel::~LevelSelectModel()
{
}

Texture2D& LevelSelectModel::getBackArrow()
{
	return backArrow;
}

Vector2 LevelSelectModel::getBackArrowPosition()
{
	return backArrowPosition;
}

float LevelSelectModel::getBackArrowScale()
{
	return backArrowScale;
}

Texture2D& LevelSelectModel::getBackground()
{
	return background;
}

Vector2 LevelSelectModel::getBackgroundPos()
{
	return backgroundPos;
}

float LevelSelectModel::getBackgroundScale()
{
	return backgroundScale;
}

Texture2D& LevelSelectModel::getLevel1Texture()
{
	return level1Texture;
}

Rectangle LevelSelectModel::getSrcRecLevel1()
{
	return srcRecLevel1;
}

Rectangle LevelSelectModel::getDestRecLevel1()
{
	return destRecLevel1;
}

Vector2 LevelSelectModel::getOriginLevel1()
{
	return originLevel1;
}

Color LevelSelectModel::getDestRecColorLevel1()
{
	return destRecColorLevel1;
}

void LevelSelectModel::setDestRecColorLevel1(Color color)
{
	destRecColorLevel1 = color;
}

Texture2D& LevelSelectModel::getLevel2Texture()
{
	return level2Texture;
}

Rectangle LevelSelectModel::getSrcRecLevel2()
{
	return srcRecLevel2;
}

Rectangle LevelSelectModel::getDestRecLevel2()
{
	return destRecLevel2;
}

Vector2 LevelSelectModel::getOriginLevel2()
{
	return originLevel2;
}

Texture2D& LevelSelectModel::getLevel3Texture()
{
	return level3Texture;
}

Rectangle LevelSelectModel::getSrcRecLevel3()
{
	return srcRecLevel3;
}

Rectangle LevelSelectModel::getDestRecLevel3()
{
	return destRecLevel3;
}

Vector2 LevelSelectModel::getOriginLevel3()
{
	return originLevel3;
}

