#pragma once
#include <iostream>
#include <SDL/SDL.h>
#include <stdlib.h> 

#include "Vector3.h"
#include "../engine.h"


struct Ball
{
	Vector3 center = { 400.0f, 300.0f, 0.0f };
	float radius = 7.0f;

	Vector3 velocityDir = { 0.04, 0.9, 0.0f };
	float speed = 450.0f;

	bool wentOutOfBounds = false;

	Ball()
	{
		velocityDir.Normalize();
	}

	void Speedup()
	{
		speed += 3.5f;
	}

	void FlipVelocity(bool flipX, bool flipY)
	{
		if (flipX)
		{
			velocityDir.x *= -1;
		}

		if (flipY)
		{
			velocityDir.y *= -1;
		}
	}

	void CollideWithWindow()
	{
		bool lowX = (center.x - radius < 0.0f);
		bool highX = (center.x + radius > (float)windowX);

		bool lowY = (center.y - radius < 0.0f);
		wentOutOfBounds = (center.y + radius > (float)windowY);

		bool flipX = lowX || highX;
		bool flipY = lowY;

		FlipVelocity(flipX, flipY);

		if (lowX)
		{
			center.x = radius;
		}
		else if (highX)
		{
			center.x = windowX - radius;
		}

		if (lowY)
		{
			center.y = radius;
		}
		//else if (wentOutOfBounds)
		//{
		//	center.y = windowY - radius;
		//	wentOutOfBounds = true;
		//}
	}

	void update()
	{
		if (wentOutOfBounds)
		{
			return;
		}

		center += (speed * deltaTime) * velocityDir;

		CollideWithWindow();
	}

	// This draw call DRAWS CENTERED.
	void draw()
	{
		if (wentOutOfBounds)
		{
			return;
		}

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

	void CollideWithPlayer(SDL_Rect rect)
	{
		// cache rect values
		float rectX = rect.x;
		float rectY = rect.y;
		float rectW = rect.w;
		float rectH = rect.h;

		// cache the circle's sweep center 
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
			Speedup();

			float deltaX = (center.x - (rectX + rectW * 0.5f));
			float deltaY = (center.y - (rectY + rectH * 1.3f));

			float paddleAngle = atan2f(deltaY, deltaX) * (180.0f / M_PI);

			velocityDir.SetAngle(paddleAngle);
			FlipVelocity(false, velocityDir.y > 0);
		}
	}

	bool CollideWithBlock(SDL_Rect rect)
	{
		// cache rect values
		float rectX = rect.x;
		float rectY = rect.y;
		float rectW = rect.w;
		float rectH = rect.h;

		// cache the circle's sweep center 
		float sweepX = center.x + (speed * deltaTime * velocityDir.x);
		float sweepY = center.y + (speed * deltaTime * velocityDir.y);

		float testX = sweepX;
		float testY = sweepY;

		// which edge is closest?

		// Check Horizontal
		bool lowX = (center.x < rectX);
		bool highX = (center.x > rectX + rectW);

		if (lowX)
		{
			testX = rectX;      // test left edge
		}
		else if (highX)
		{
			testX = rectX + rectW;   // right edge
		}

		// Check Vertical
		bool lowY = (center.y < rectY);
		bool highY = (center.y > rectY + rectH);

		if (lowY)
		{
			testY = rectY;      // top edge
		}
		else if (highY)
		{
			testY = rectY + rectH;   // bottom edge
		}

		// get distance from closest edges
		float distX = sweepX - testX;
		float distY = sweepY - testY;

		float distanceSquared = (distX * distX) + (distY * distY);

		bool collisionHappens = distanceSquared <= radius * radius;

		// if the distance is less than the radius, collision!
		if (collisionHappens)
		{
			Speedup();

			FlipVelocity(distX, distY);
			center += (deltaTime) * velocityDir;
		}

		return collisionHappens;
	}
};