#pragma once
#include <SDL/SDL.h>

#include "CircleSDF.h"
#include "../engine.h"

struct Ball
{
	Vector3 center = { 10.0f, 10.0f, 0.0f };
	Vector3 velocity = { 10.0f, 10.0f, 0.0f };
	float radius = 64.0f;

	CircleSDF collider;

	Ball(Vector3 pos, Vector3 vel, float rad)
	{
		center = pos;
		velocity = vel;
		radius = rad;
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

	void draw()
	{
		const int diameter = (int)(radius * 2);

		int x = (radius - 1);
		int y = 0;
		int tx = 1;
		int ty = 1;
		int error = (tx - diameter);

		while (x >= y)
		{
			//  Each of the following renders an octant of the circle
			SDL_RenderDrawPoint(render, (int)(center.x - radius/2 + x), (int)(center.y - radius/2 - y));
			SDL_RenderDrawPoint(render, (int)(center.x - radius/2 + x), (int)(center.y - radius/2 + y));
			SDL_RenderDrawPoint(render, (int)(center.x - radius/2 - x), (int)(center.y - radius/2 - y));
			SDL_RenderDrawPoint(render, (int)(center.x - radius/2 - x), (int)(center.y - radius/2 + y));
			SDL_RenderDrawPoint(render, (int)(center.x - radius/2 + y), (int)(center.y - radius/2 - x));
			SDL_RenderDrawPoint(render, (int)(center.x - radius/2 + y), (int)(center.y - radius/2 + x));
			SDL_RenderDrawPoint(render, (int)(center.x - radius/2 - y), (int)(center.y - radius/2 - x));
			SDL_RenderDrawPoint(render, (int)(center.x - radius/2 - y), (int)(center.y - radius/2 + x));

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (tx - diameter);
			}
		}
	}

};