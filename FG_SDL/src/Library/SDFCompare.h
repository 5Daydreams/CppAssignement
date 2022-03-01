#pragma once

#include "Vector3.h"

bool CheckCollision(const CircleCollider& other)
{
	return VectorDistance(other.center, center) <= radius + other.radius;
}