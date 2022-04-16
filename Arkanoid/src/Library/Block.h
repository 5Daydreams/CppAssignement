#pragma once
#include <iostream>
#include <SDL/SDL.h>
#include <stdlib.h> 

#include "Vector3.h"
#include "../engine.h"

// feedback: is there a particualr reason this struct is defined in the header file? Common approach is to have declaration in header
// and definition in .cpp file.

struct Block
{
private:
	SDL_Rect blockRect;

public:
	Vector3 center = { 0.0f, 0.0f, 0.0f };
	Vector3 size = { 100.0f, 20.0f, 0.0f };
	int life = 3;
	int maxLife;
	bool isAlive = true;

	Block()
	{
		maxLife = life;
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

		maxLife = life;
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

		int r = 30 + (maxLife - life) * 20;
		int g = 80 + maxLife * 15 - (maxLife - life) * 15;
		int b = 50 - (maxLife - life) * 5;

		SDL_SetRenderDrawColor(render, r , g, b, 255);
		SDL_RenderFillRect(render, &blockRect);
	}
};