#include "UI.h"

void UI::drawButton(Rectangle& button, Color buttonColor, Color textColor, const std::string& text, Vector2 pos)
{
	button.x = pos.x;
	button.y = pos.y;
	DrawRectangleRec(button, buttonColor);
	DrawText(text.c_str(), pos.x, pos.y, 20, textColor);
}

void UI::drawText(const std::string& text, Vector2 pos, int fontSize, Color color)
{
	DrawText(text.c_str(), pos.x, pos.y, fontSize, color);
}

void UI::checkButtonHover(Rectangle& button, Color& buttonColor, Color& textColor, const std::string& text)
{
	if (CheckCollisionPointRec(GetMousePosition(), button))
	{
		buttonColor = RED;
		textColor = WHITE;
	}
	else
	{
		buttonColor = WHITE;
		textColor = RED;
	}
}

void UI::transformBoundingBox(BoundingBox& box, Vector3 position, Vector3 scale, Vector3 rotation)
{
	Matrix transform = MatrixIdentity();
	Matrix translation = MatrixTranslate(position.x, position.y, position.z);
	Matrix scaling = MatrixScale(scale.x, scale.y, scale.z);
	Matrix rotationX = MatrixRotateX(rotation.x);
	Matrix rotationY = MatrixRotateY(rotation.y);
	Matrix rotationZ = MatrixRotateZ(rotation.z);
	Matrix rotationMatrix = MatrixMultiply(MatrixMultiply(rotationX, rotationY), rotationZ);
	transform = MatrixMultiply(transform, translation);
	transform = MatrixMultiply(transform, scaling);
	transform = MatrixMultiply(transform, rotationMatrix);
	box.min = Vector3Transform(box.min, transform);
	box.max = Vector3Transform(box.max, transform);
}

std::vector<Vector3> UI::GetBoundingBoxVertices(BoundingBox box) {
    std::vector<Vector3> vertices(8);
    vertices[0] = box.min;
    vertices[1] = Vector3{ box.min.x, box.min.y, box.max.z };
    vertices[2] = Vector3{ box.min.x, box.max.y, box.min.z };
    vertices[3] = Vector3{ box.min.x, box.max.y, box.max.z };
    vertices[4] = Vector3{ box.max.x, box.min.y, box.min.z };
    vertices[5] = Vector3{ box.max.x, box.min.y, box.max.z };
    vertices[6] = Vector3{ box.max.x, box.max.y, box.min.z };
    vertices[7] = box.max;
    return vertices;
}

BoundingBox UI::ComputeBoundingBoxFromVertices(const std::vector<Vector3>& vertices) {
    Vector3 min = vertices[0];
    Vector3 max = vertices[0];
    for (const auto& vertex : vertices) {
        if (vertex.x < min.x) min.x = vertex.x;
        if (vertex.y < min.y) min.y = vertex.y;
        if (vertex.z < min.z) min.z = vertex.z;
        if (vertex.x > max.x) max.x = vertex.x;
        if (vertex.y > max.y) max.y = vertex.y;
        if (vertex.z > max.z) max.z = vertex.z;
    }
    return BoundingBox{ min, max };
}

BoundingBox UI::RotateBoundingBox(BoundingBox box, Vector3 axis, float angle) {
    std::vector<Vector3> vertices = GetBoundingBoxVertices(box);
    for (auto& vertex : vertices) {
        vertex = RotateVector3(vertex, axis, angle);
    }
    return ComputeBoundingBoxFromVertices(vertices);
}