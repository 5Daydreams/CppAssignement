#include "player.h"
#include "engine.h"
#include "game.h"

void Player::update()
{
	float direction = 0;

	if (keys[SDL_SCANCODE_D])
	{
		direction = +1;
	}
	if (keys[SDL_SCANCODE_A])
	{
		direction = -1;
	}

	x += direction * speed * deltaTime;
	paddleRect = { (int)(x - w / 2), (int)(y - h / 2), (int)w, (int)h };

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

	SDL_SetRenderDrawColor(render, 30, 210, 190, 255);
	SDL_RenderFillRect(render, &paddleRect);
}

Player::Player()
{
	paddleRect = { (int)(x - w/2), (int)(y - h/2), (int)w, (int)h };
}