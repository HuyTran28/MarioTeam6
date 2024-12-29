#pragma once

#include <string>
#include <raylib.h>

class Button
{
private:
	std::string text;
	Color textColor;
	int textSize;
	Vector2 textPosition;

	Texture2D texture;
	Rectangle srcRec;
	Rectangle dstRec;
	Vector2 origin;
	float rotationAngle;
	Color color;
	bool hasText = false;
public:
	Button();
	Button(std::string text, Rectangle dstRec, Color color);
	Button(std::string text, Texture2D texture, Rectangle srcRec, Rectangle dstRec, Vector2 origin, float rotationAngle, Color color);
	Button(std::string text, Texture2D texture, Rectangle srcRec, Rectangle dstRec, Vector2 origin, float rotationAngle, Color color, Color textColor, int textSize, Vector2 textPosition);
	~Button();

	std::string getText();
	Texture2D getTexture();
	Rectangle getSrcRec();
	Rectangle getDstRec();
	Vector2 getOrigin();
	float getRotationAngle();
	Color getColor();
	void setColor(Color color);
	void setDstRec(Rectangle dstRec);
	void setRotationAngle(float rotationAngle);
	void setOrigin(Vector2 origin);
	void setSrcRec(Rectangle srcRec);
	void setTexture(Texture2D texture);
	void setText(std::string text);

	bool isClicked(Vector2 mousePosition);
	bool isHovered(Vector2 mousePosition);
	void draw();
};