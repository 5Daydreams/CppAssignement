#pragma once
#include <iostream>
#include <SDL/SDL.h>
#include <stdlib.h> 

#include "Vector3.h"
#include "../engine.h"


struct Block
{
private:
	SDL_Rect blockRect;

public:
	Vector3 center = { 0.0f, 0.0f, 0.0f };
	Vector3 size = { 100.0f, 20.0f, 0.0f };
	int life = 1;
	bool isAlive = true;

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

	SDL_Rect GetBlockRect()
	{
		if (!isAlive)
		{
			return SDL_Rect{ -10, -10, 1, 1 };
		}

		return blockRect;
	}

	void takeDamage()
	{
		life--;
		if (life <= 0)
		{
			isAlive = false;
		}
	}

	void draw()
	{
		if (!isAlive)
		{
			return;
		}

		SDL_SetRenderDrawColor(render, 230, 210, 40, 255);
		SDL_RenderFillRect(render, &blockRect);
	}
};