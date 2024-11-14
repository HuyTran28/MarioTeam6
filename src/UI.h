#pragma once

#include <raylib.h>
#include <string>
#include <vector>
#include <raymath.h>


class UI
{
public:
	static void drawButton(Rectangle& button, Color buttonColor, Color textColor, const std::string& text, Vector2 pos);
	static void drawText(const std::string& text, Vector2 pos, int fontSize, Color color);
	static void checkButtonHover(Rectangle& button, Color& buttonColor, Color& textColor, const std::string& text);
	static void transformBoundingBox(BoundingBox& box, Vector3 position, Vector3 scale, Vector3 rotation);
	static Vector3 RotateVector3(Vector3 v, Vector3 axis, float angle) {
		Matrix rotationMatrix = MatrixRotate(axis, angle);
		return Vector3Transform(v, rotationMatrix);
	}
    static BoundingBox ComputeBoundingBoxFromVertices(const std::vector<Vector3>& vertices);
    static BoundingBox RotateBoundingBox(BoundingBox box, Vector3 axis, float angle);

    static std::vector<Vector3> GetBoundingBoxVertices(BoundingBox box);
};