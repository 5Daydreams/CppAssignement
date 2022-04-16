#pragma once
#include <SDL/SDL.h>

// feedback: similar comment as in game.h. Use OOP and classes to make more structured code.

extern SDL_Window* window;
extern int windowX;
extern int windowY;

extern SDL_Renderer* render;

// Array of bools for key inputs  
// where scancodes are a numerical mapping of keys as opposed to mapping them by the key's string value
extern bool keys[SDL_NUM_SCANCODES];

extern float deltaTime;