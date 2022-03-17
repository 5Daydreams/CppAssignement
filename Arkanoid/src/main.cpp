#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>

#include "engine.h"
#include "player.h"
#include "game.h"

static bool APPLICATION_IS_RUNNING;

void InitializeGame()
{
	Ball firstBall = Ball();
	balls.push_back(firstBall);

	// Initializing blocks
	Vector3 blockSize{ 75,25,0 };
	Vector3 startingOffset{ 50,30,0 };
	Vector3 blockSpacing{ 2,2,0 };

	for (int j = 0; j < BLOCK_COL_SIZE; j++)
	{
		for (int i = 0; i < BLOCK_ROW_SIZE; i++)
		{
			Vector3 blockPos = {
				startingOffset.x + (blockSize.x + blockSpacing.x) * i ,
				startingOffset.y + (blockSize.y + blockSpacing.y) * j ,
				0.0f
			};

			int lifeTrick = (i + j) % 2;

			blocks[BLOCK_ROW_SIZE * j + i] = Block(blockPos, blockSize);
			blocks[BLOCK_ROW_SIZE * j + i].life = (BLOCK_COL_SIZE - j) / 2 + lifeTrick * 2 + 1;
			blocks[BLOCK_ROW_SIZE * j + i].maxLife = (BLOCK_COL_SIZE - j) / 2 + lifeTrick * 2 + 1;
		}
	}

	resetAvailable = false;
}

void InitializeEngine()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	windowX = 800;
	windowY = 600;

	// Title, x, y, width, height, flags
	window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowX, windowY, 0);
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	APPLICATION_IS_RUNNING = true;

	InitializeGame();
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

	if (keys[SDL_SCANCODE_R] && resetAvailable)
	{
		player.x = windowX / 2 - player.w / 2;
		InitializeGame();
	}
}

void LogicLoop()
{
	player.update();

	if (balls.size() <= 0)
	{
		resetAvailable = true;
		return;
	}

	for (int ball = balls.size() - 1; ball >= 0; ball--)
	{
		balls[ball].CollideWithPlayer(player.paddleRect);

		for (int j = 0; j < BLOCK_COL_SIZE; j++)
		{
			for (int i = 0; i < BLOCK_ROW_SIZE; i++)
			{
				SDL_Rect currBlockRect = blocks[BLOCK_ROW_SIZE * j + i].GetBlockRect();
				if (balls[ball].CollideWithBlock(currBlockRect))
				{
					blocks[BLOCK_ROW_SIZE * j + i].takeDamage();

					bool blockIsDead = !blocks[BLOCK_ROW_SIZE * j + i].isAlive;
					bool luckyPosition = ((i + j) % 7) == 0;

					if ((blockIsDead) && (luckyPosition))
					{
						Ball newBall = Ball();
						newBall.center = balls[ball].center;
						newBall.velocityDir = balls[ball].velocityDir;
						newBall.speed = balls[ball].speed * 0.9f;
						balls.push_back(newBall);
					}
				}
			}
		}

		balls[ball].update();

		if (balls[ball].wentOutOfBounds)
		{
			balls.erase(balls.begin() + ball);
		}
	}
}

void RenderLoop()
{
	SDL_SetRenderDrawColor(render, 20, 20, 30, 255); // #FF00FFFF
	SDL_RenderClear(render);

	player.draw();

	for (int ball = 0; ball < balls.size(); ball++)
	{
		balls[ball].draw();
	}

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
	InitializeEngine();

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