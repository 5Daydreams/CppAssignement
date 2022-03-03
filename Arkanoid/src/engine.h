#pragma once
#include <SDL/SDL.h>

extern SDL_Window* window;
extern SDL_Renderer* render;

// Array of bools for key inputs  
// where scancodes are a numerical mapping of keys as opposed to mapping them by the key's string value
extern bool keys[SDL_NUM_SCANCODES];

extern float deltaTime;