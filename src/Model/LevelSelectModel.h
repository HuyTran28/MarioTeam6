#pragma once

#include "StateModel.h"
#include <string>
#include <raylib.h>
#include <vector>

class LevelSelectModel : public StateModel
{
private:
	Texture2D background;
	float backgroundScale;
	Vector2 backgroundPos;

	Texture2D level1Texture;
	Rectangle srcRecLevel1;
	Rectangle destRecLevel1;
	Vector2 originLevel1;
	Color destRecColorLevel1;

	Texture2D level2Texture;
	Rectangle srcRecLevel2;
	Rectangle destRecLevel2;
	Vector2 originLevel2;
	
	Texture2D level3Texture;
	Rectangle srcRecLevel3;
	Rectangle destRecLevel3;
	Vector2 originLevel3;

	Texture2D backArrow;
	Vector2 backArrowPosition;
	float backArrowScale;

public:
	LevelSelectModel();
	~LevelSelectModel();

	Texture2D& getBackground();
	Vector2 getBackgroundPos();
	float getBackgroundScale();

	Texture2D& getLevel1Texture();
	Rectangle getSrcRecLevel1();
	Rectangle getDestRecLevel1();
	Vector2 getOriginLevel1();
	Color getDestRecColorLevel1();
	void setDestRecColorLevel1(Color color);

	Texture2D& getLevel2Texture();
	Rectangle getSrcRecLevel2();
	Rectangle getDestRecLevel2();
	Vector2 getOriginLevel2();


	Texture2D& getLevel3Texture();
	Rectangle getSrcRecLevel3();
	Rectangle getDestRecLevel3();
	Vector2 getOriginLevel3();

	Texture2D& getBackArrow();
	Vector2 getBackArrowPosition();
	float getBackArrowScale();

};
