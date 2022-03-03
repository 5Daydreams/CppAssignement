#pragma once

#include "Vector3.h"

struct SimpleObject2D
{
	Vector3 position = { 0.0f, 0.0f, 0.0f };
	float rotation = 0;

	void draw();
};