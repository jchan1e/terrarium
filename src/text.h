#include "stdGL.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <string>

#ifndef text_h
#define text_h

void RenderText(std::string message, SDL_Color color, int x, int y, int size, SDL_Window* window);

#endif
