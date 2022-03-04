#pragma once

#include "Vector3.h"
#include "CircleSDF.h"
#include "RectangleSDF.h"

bool CheckCollision(CircleSDF& circle, RectangleSDF& rect)
{
	float circleX = circle.center.x;
	float circleY = circle.center.y;
	float radius = circle.radius;

	float rectX = rect.center.x;
	float rectY = rect.center.y;
	float rectW = rect.size.x;
	float rectH = rect.size.y;

	// cache the circle's center 
	float testX = circleX;
	float testY = circleY;

	// which edge is closest?
	if (circleX < rectX)
	{
		testX = rectX;      // test left edge
	}
	else if (circleX > rectX + rectW)
	{
		testX = rectX + rectW;   // right edge
	}

	if (circleY < rectY)
	{
		testY = rectY;      // top edge
	}
	else if (circleY > rectY + rectH)
	{
		testY = rectY + rectH;   // bottom edge
	}

	// get distance from closest edges
	float distX = circleX - testX;
	float distY = circleY - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	if (distance <= radius)
	{
		return true;
	}

	return false;
}
