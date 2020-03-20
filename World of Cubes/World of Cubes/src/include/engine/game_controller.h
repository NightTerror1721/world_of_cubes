#pragma once

#include <support/SDL.h>
#include <support/GL.h>

class GameController
{
private:
	SDL_Window* _window;

public:
	GameController();
	~GameController();
};
