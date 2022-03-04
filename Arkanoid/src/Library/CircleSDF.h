#pragma once
#include "Vector3.h"

struct CircleSDF
{
	Vector3 center;
	float radius;

	float GetValue(const Vector3 position)
	{
		return VectorLength(position - center) - radius;
	}
};