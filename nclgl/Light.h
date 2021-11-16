#pragma once

#include "Vector3.h"
#include "Vector4.h"

class Light
{
public:
	Light() {};
	Light(const Vector3& position, const Vector4& colour, float radius)
	{
		this->position = position;
		this->colour = colour;
		this->radius = radius;
	}
	~Light(void) {};

	Vector3 GetPosition() const { return position; };
	void SetPosition(const Vector3& val) { position = val; };

	Vector4 GetColour() const { return colour; };
	void SetColour(const Vector4& val) { colour = val; };

	float GetRadius() const { return radius; };
	void SetRadius(float val) { radius = val; };

protected:
	Vector3 position;
	Vector4 colour;
	float radius;
};