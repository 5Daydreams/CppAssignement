#pragma once
#include <SDL/SDL.h>
#include <iostream>

#include "CircleSDF.h"
#include "RectangleSDF.h"
#include "../engine.h"

struct Ball
{
	Vector3 center = { 100.0f, 100.0f, 0.0f };
	Vector3 velocity = { 100.0f, 100.0f, 0.0f };
	float radius = 16.0f;

	CircleSDF collider;

	Ball()
	{
		collider = { center, radius };
	}

	void FlipVelocity(bool flipX, bool flipY)
	{
		if (flipX)
		{
			velocity.x *= -1;
		}

		if (flipY)
		{
			velocity.y *= -1;
		}
	}

	void update()
	{
		center += velocity * deltaTime;
	}

	// This draw call DRAWS CENTERED.
	void draw()
	{
		SDL_SetRenderDrawColor(render, 190, 30, 50, 255);
		for (int w = 0; w < radius * 2; w++)
		{
			for (int h = 0; h < radius * 2; h++)
			{
				int dx = radius - w; // horizontal offset
				int dy = radius - h; // vertical offset
				if ((dx * dx + dy * dy) <= (radius * radius))
				{
					SDL_RenderDrawPoint(render, (int)center.x + dx, (int)center.y + dy);
				}
			}
		}
	}

	bool CheckCollisionSquare(RectangleSDF& rect)
	{
		float rectX = rect.center.x;
		float rectY = rect.center.y;
		float rectW = rect.size.x;
		float rectH = rect.size.y;

		// cache the circle's center 
		float testX = center.x;
		float testY = center.y;

		// which edge is closest?
		if (center.x < rectX)
		{
			testX = rectX;      // test left edge
		}
		else if (center.x > rectX + rectW)
		{
			testX = rectX + rectW;   // right edge
		}

		if (center.y < rectY)
		{
			testY = rectY;      // top edge
		}
		else if (center.y > rectY + rectH)
		{
			testY = rectY + rectH;   // bottom edge
		}

		// get distance from closest edges
		float distX = center.x - testX;
		float distY = center.y - testY;

		float distanceSquared = (distX * distX) + (distY * distY);

		// if the distance is less than the radius, collision!
		if (distanceSquared <= radius * radius)
		{
			return true;
		}

		return false;
	}

};