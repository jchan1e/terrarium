#ifndef text_h
#define text_h

#include "stdGL.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <string>

void RenderText(std::string message, SDL_Color color, int x, int y, int size, SDL_Window* window);

#endif
