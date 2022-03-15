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

	windowX = 800;
	windowY = 600;

	// Title, x, y, width, height, flags
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowX, windowY, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	APPLICATION_IS_RUNNING = true;

	Vector3 blockSize{ 60,20,0 };
	Vector3 startingOffset{ 105,30,0 };
	Vector3 blockSpacing{ 5,5,0 };

	for (int j = 0; j < BLOCK_COL_SIZE; j++)
	{
		for (int i = 0; i < BLOCK_ROW_SIZE; i++)
		{
			Vector3 blockPos = {
				startingOffset.x + (blockSize.x + blockSpacing.x) * i ,
				startingOffset.y + (blockSize.y + blockSpacing.y) * j ,
				0.0f
			};

			blocks[BLOCK_ROW_SIZE * j + i] = Block(blockPos, blockSize);
		}
	}
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
	ball.CheckCollisionOnBlock(player.paddleRect, true);

	for (int j = 0; j < BLOCK_COL_SIZE; j++)
	{
		for (int i = 0; i < BLOCK_ROW_SIZE; i++)
		{
			ball.CheckCollisionOnBlock(blocks[BLOCK_ROW_SIZE * j + i].blockRect, false);
		}
	}

	// Debugs for the ball
	//std::cout << deltaTime << " centerPos = ";
	//std::cout << ball.center.x << "," << ball.center.y << "," << ball.center.z << std::endl;
}

void RenderLoop()
{
	SDL_SetRenderDrawColor(render, 20, 20, 30, 255); // #FF00FFFF
	SDL_RenderClear(render);

	player.draw();
	ball.draw();

	for (int j = 0; j < BLOCK_COL_SIZE; j++)
	{
		for (int i = 0; i < BLOCK_ROW_SIZE; i++)
		{
			blocks[BLOCK_ROW_SIZE * j + i].draw();
		}
	}

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