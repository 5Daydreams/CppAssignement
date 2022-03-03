#include "engine.h"

SDL_Window* window;
SDL_Renderer* render;

bool keys[SDL_NUM_SCANCODES] = { false };

float deltaTime = 0.0f;
