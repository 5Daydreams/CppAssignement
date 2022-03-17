#pragma once
#include "SDL/SDL.h"

struct Player
{
	float x = 360;
	float y = 550;

	float speed = 700;
	float w = 64;
	float h = 16;

	SDL_Rect paddleRect;
	SDL_Rect innerRect;

	Player();

	void update();
	void draw();
};
