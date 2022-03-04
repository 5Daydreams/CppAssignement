#pragma once
#include <algorithm>
#include "Vector3.h"

struct RectangleSDF
{
	Vector3 center;
	Vector3 size;

	float GetValue(const Vector3 position)
	{
		Vector3 sdfDist = VectorAbs(position - center) - VectorAbs(size);

		Vector3 sdfVec =
		{
			std::max(sdfDist.x,0.0f),
			std::max(sdfDist.y,0.0f),
			std::max(sdfDist.z,0.0f)
		};

		return  VectorLength(sdfVec) + std::min(std::max(sdfDist.x, sdfDist.y), 0.0f);
	}
};