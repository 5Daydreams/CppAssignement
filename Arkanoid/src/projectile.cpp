#include "projectile.h"
#include "engine.h"

void Projectile::update()
{
	if (!alive)
	{
		return;
	}

	float speed = 400.0f *deltaTime;
	x += speed;
}

void Projectile::draw()
{
	if (!alive)
	{
		return;
	}

	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
	SDL_Rect rect = { (int)x, (int)y, 16, 16 };

	SDL_RenderFillRect(render, &rect);
}
