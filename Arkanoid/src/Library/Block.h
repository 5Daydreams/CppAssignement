#pragma once
#include <iostream>
#include <SDL/SDL.h>
#include <stdlib.h> 

#include "Vector3.h"
#include "../engine.h"


struct Block
{
	Vector3 center = { 0.0f, 0.0f, 0.0f };
	Vector3 size = { 100.0f, 20.0f, 0.0f };
	int life = 3;

	SDL_Rect blockRect;

	Block()
	{
		blockRect = {
			(int)(center.x - size.x * 0.5f),
			(int)(center.y - size.y * 0.5f),
			(int)(size.x),
			(int)(size.y)
		};
	}

	Block(Vector3 _center, Vector3 _size)
	{
		center = _center;
		size = _size;

		blockRect = {
			(int)(center.x - size.x * 0.5f),
			(int)(center.y - size.y * 0.5f),
			(int)(size.x),
			(int)(size.y)
		};
	}

	void draw()
	{
		SDL_SetRenderDrawColor(render, 230, 210, 40, 255);
		SDL_RenderFillRect(render, &blockRect);
	}

	bool CheckCollisionOnBlock(SDL_Rect rect, bool isPlayer)
	{
		// cache rect values
		float rectX = rect.x;
		float rectY = rect.y;
		float rectW = rect.w;
		float rectH = rect.h;

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
			if (!isPlayer)
			{
				FlipVelocity(distX, distY);
			}
			else
			{
				speed += 8.0f;

				float deltaX = (center.x - (rectX + rectW * 0.5f));
				float deltaY = (center.y - (rectY + rectH * 1.3f));

				float paddleAngle = atan2f(deltaY, deltaX) * (180.0f / M_PI);

				velocityDir.SetAngle(paddleAngle);
				FlipVelocity(false, velocityDir.y > 0);
			}
			return true;
		}

		return false;
	}
};