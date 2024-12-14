#include "Button.h"

Button::Button() : text(""), texture(Texture2D()), srcRec(Rectangle()), dstRec(Rectangle()), origin(Vector2()), rotationAngle(0), color(WHITE)
{
	textColor = WHITE;
	textSize = 20;
	textPosition = { 0.0f, 0.0f };
}

Button::Button(std::string text, Texture2D texture, Rectangle srcRec, Rectangle dstRec, Vector2 origin, float rotationAngle, Color color) : text(text), texture(texture),
srcRec(srcRec), dstRec(dstRec), origin(origin), rotationAngle(rotationAngle), color(color)
{
	textColor = WHITE;
	textSize = 20;
	textPosition = { 0.0f, 0.0f };
}

Button::Button(std::string text, Texture2D texture, Rectangle srcRec, Rectangle dstRec, Vector2 origin, float rotationAngle, Color color, Color textColor, int textSize, Vector2 textPosition) : Button(text, texture, srcRec, dstRec, origin, rotationAngle, color)
{
	this->textColor = textColor;
	this->textSize = textSize;
	this->textPosition = textPosition;
	this->hasText = true;
}

Button::~Button()
{

}

void Button::draw()
{
	if (hasText)
		DrawText(text.c_str(), textPosition.x, textPosition.y, textSize, textColor);
	DrawTexturePro(texture, srcRec, dstRec, origin, rotationAngle, color);
}

std::string Button::getText()
{
	return text;
}

Texture2D Button::getTexture()
{
	return texture;
}

Rectangle Button::getSrcRec()
{
	return srcRec;
}

Rectangle Button::getDstRec()
{
	return dstRec;
}

Vector2 Button::getOrigin()
{
	return origin;
}

float Button::getRotationAngle()
{
	return rotationAngle;
}

Color Button::getColor()
{
	return color;
}

void Button::setColor(Color color)
{
	this->color = color;
}

void Button::setDstRec(Rectangle dstRec)
{
	this->dstRec = dstRec;
}

void Button::setRotationAngle(float rotationAngle)
{
	this->rotationAngle = rotationAngle;
}

void Button::setOrigin(Vector2 origin)
{
	this->origin = origin;
}

void Button::setSrcRec(Rectangle srcRec)
{
	this->srcRec = srcRec;
}

void Button::setTexture(Texture2D texture)
{
	this->texture = texture;
}

void Button::setText(std::string text)
{
	this->text = text;
}

bool Button::isClicked(Vector2 mousePosition)
{
	if (CheckCollisionPointRec(mousePosition, dstRec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		return true;
	}
	return false;
}

bool Button::isHovered(Vector2 mousePosition)
{
	if (CheckCollisionPointRec(mousePosition, dstRec))
	{
		return true;
	}
	return false;
}




