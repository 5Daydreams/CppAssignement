#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "engine.h"
#include "player.h"
#include "game.h"

static bool APPLICATION_IS_RUNNING;

void Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// Title, x, y, width, height, flags
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	APPLICATION_IS_RUNNING = true;

}

void InputLoop()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
		{
			APPLICATION_IS_RUNNING = false;
			break;
		}
		case SDL_KEYDOWN:
		{
			int scancode = event.key.keysym.scancode;
			if (scancode == SDL_SCANCODE_ESCAPE)
			{
				APPLICATION_IS_RUNNING = false;
			}

			keys[scancode] = true;

			break;
		}
		case SDL_KEYUP:
		{
			int scancode = event.key.keysym.scancode;
			keys[scancode] = false;

			break;
		}

		}
	}
}

void LogicLoop()
{
	player.update();
	ball.update();

	// Debugs for the ball
	//std::cout << deltaTime << " centerPos = ";
	//std::cout << ball.center.x << "," << ball.center.y << "," << ball.center.z << std::endl;

	projectile.update();
}

void RenderLoop()
{
	SDL_SetRenderDrawColor(render, 20, 20, 30, 255); // #FF00FFFF
	SDL_RenderClear(render);

	player.draw();
	ball.draw();
	projectile.draw();

	SDL_RenderPresent(render);
}

int main()
{
	Initialize();

	Uint64 prevTicks = SDL_GetPerformanceCounter();

	// To keep the program running:
	while (APPLICATION_IS_RUNNING)
	{
		// Get kernel ticks
		Uint64 ticks = SDL_GetPerformanceCounter();
		Uint64 deltaTicks = ticks - prevTicks;
		prevTicks = ticks;
		deltaTime = (float)deltaTicks / SDL_GetPerformanceFrequency();

		InputLoop();
		LogicLoop();
		RenderLoop();

		SDL_Delay(16);
	}
}