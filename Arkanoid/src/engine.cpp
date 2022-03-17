#include "engine.h"

SDL_Window* window;
int windowX;
int windowY;

SDL_Renderer* render;

bool keys[SDL_NUM_SCANCODES] = { false };

float deltaTime = 0.0f;