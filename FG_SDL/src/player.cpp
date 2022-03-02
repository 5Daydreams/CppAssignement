#include "player.h"
#include "engine.h"
#include "game.h"

void Player::update()
{
	float speed = 200 * deltaTime;

	if (keys[SDL_SCANCODE_D])
	{
		x += speed;
	}
	if (keys[SDL_SCANCODE_A])
	{
		x -= speed;
	}
	if (keys[SDL_SCANCODE_W])
	{
		y -= speed;
	}
	if (keys[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (keys[SDL_SCANCODE_SPACE])
	{
		projectile.alive = true;
		projectile.x = x;
		projectile.y = y;
	}
}

void Player::draw()
{
	// SDL_SetRenderDrawColor(render, rand() & 0xFF, rand() & 0xFF, rand() & 0xFF, 255);
	// SDL_SetRenderDrawColor(render, 200, 0, 20, 255);

	SDL_SetRenderDrawColor(render, 150, 25, 40, 255);
	SDL_Rect rect = { (int)x , (int)y , 32 ,32 };
	SDL_RenderFillRect(render, &rect);
}