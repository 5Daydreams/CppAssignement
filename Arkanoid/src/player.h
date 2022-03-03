#pragma once
#include "SDL/SDL.h"

struct Player
{
	float x = 100;
	float y = 500;

	float speed = 500;
	float w = 64;
	float h = 16;

	SDL_Rect paddleRect;

	Player();

	void update();
	void draw();
};
