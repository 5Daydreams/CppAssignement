#pragma once
#include "Vector3.h"

class CircleCollider
{
public:
	Vector3 center;
	float radius;

	template<typename T>
	bool CheckCollision(T other);

	bool CheckCollision(const CircleCollider& other)
	{
		return VectorDistance(other.center, center) <= radius + other.radius;
	}
};