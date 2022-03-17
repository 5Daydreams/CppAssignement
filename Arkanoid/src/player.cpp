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

	paddleRect.x = x; // updating paddle position
	innerRect.x = x + 2; // inner paddle has a small offset
}

void Player::draw()
{
	// Draw outline
	SDL_SetRenderDrawColor(render, 90, 170, 210, 255);
	SDL_RenderFillRect(render, &paddleRect);

	// Draw the inside of paddle
	SDL_SetRenderDrawColor(render, 30, 110, 160, 255);
	SDL_RenderFillRect(render, &innerRect);
}

Player::Player()
{
	paddleRect = { (int)(x - w / 2), (int)(y - h / 2), (int)w, (int)h };
	int innerW = w - 4;
	int innerH = h - 4;
	innerRect = { (int)(x - innerW / 2), (int)(y - innerH / 2), (int)innerW, (int)innerH };
}