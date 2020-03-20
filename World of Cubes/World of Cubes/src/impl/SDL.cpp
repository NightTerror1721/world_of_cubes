#include <support/SDL.h>

#include <iostream>
#include <utility>


namespace sdl
{
	static bool _SDL_Init_State = false;
}


bool sdl::is_initiated() { return _SDL_Init_State; }

bool sdl::initiate()
{
	if (_SDL_Init_State)
		return true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL Initiation error: " << SDL_GetError() << std::endl;
		return false;
	}

	_SDL_Init_State = true;
	return true;
}

void sdl::quit()
{
	if (!_SDL_Init_State)
		return;

	SDL_Quit();
	_SDL_Init_State = false;
}




std::vector<sdl::DisplayMode> sdl::GetAllDisplayModes()
{
	int count = SDL_GetNumDisplayModes(0);
	if (count < 1)
	{
		std::cerr << "SDL videoMode error: " << SDL_GetError() << std::endl;
		return {};
	}

	std::vector<sdl::DisplayMode> modes;
	SDL_DisplayMode sdlMode;
	sdl::DisplayMode mode;

	for (int i = 0; i < count; ++i)
	{
		if (SDL_GetDisplayMode(0, i, &sdlMode) != 0)
		{
			std::cerr << "SDL videoMode error: " << SDL_GetError() << std::endl;
			return {};
		}
		
		mode.width = sdlMode.w;
		mode.height = sdlMode.h;
		mode.framerate = sdlMode.refresh_rate;
		mode.format = static_cast<sdl::PixelFormat>(sdlMode.format);
		modes.push_back(mode);
	}

	return std::move(modes);
}

SDL_Window* sdl::CreateWindow(const std::string& title, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	if (!initiate())
		return nullptr;

	//set attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	//antialiasing (disable this lines if it goes too slow)
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8); //increase to have smoother polygons

	SDL_Window* win = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!win)
	{
		std::cerr << "SDL Window creation error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	return win;
}

SDL_GLContext sdl::CreateContext(SDL_Window* window)
{
	if (!initiate() || !window)
		return nullptr;

	return SDL_GL_CreateContext(window);
}
