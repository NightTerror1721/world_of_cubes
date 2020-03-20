#pragma once

#include <sdl/SDL.h>
#include <string>
#include <vector>


namespace sdl
{
	bool is_initiated();

	bool initiate();

	void quit();
}


namespace sdl
{
	enum class PixelFormat : Uint32
	{
        UNKNOWN = SDL_PIXELFORMAT_UNKNOWN,
        INDEX1LSB = SDL_PIXELFORMAT_INDEX1LSB,
        INDEX1MSB = SDL_PIXELFORMAT_INDEX1MSB,
        INDEX4LSB = SDL_PIXELFORMAT_INDEX4LSB,
        INDEX4MSB = SDL_PIXELFORMAT_INDEX4MSB,
        INDEX8 = SDL_PIXELFORMAT_INDEX8,
        RGB332 = SDL_PIXELFORMAT_RGB332,
        RGB444 = SDL_PIXELFORMAT_RGB444,
        BGR444 = SDL_PIXELFORMAT_BGR444,
        RGB555 = SDL_PIXELFORMAT_RGB555,
        BGR555 = SDL_PIXELFORMAT_BGR555,
        ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
        RGBA4444 = SDL_PIXELFORMAT_RGBA4444,
        ABGR4444 = SDL_PIXELFORMAT_ABGR4444,
        BGRA4444 = SDL_PIXELFORMAT_BGRA4444,
        ARGB1555 = SDL_PIXELFORMAT_ARGB1555,
        RGBA5551 = SDL_PIXELFORMAT_RGBA5551,
        ABGR1555 = SDL_PIXELFORMAT_ABGR1555,
        BGRA5551 = SDL_PIXELFORMAT_BGRA5551,
        RGB565 = SDL_PIXELFORMAT_RGB565,
        BGR565 = SDL_PIXELFORMAT_BGR565,
        RGB24 = SDL_PIXELFORMAT_RGB24,
        BGR24 = SDL_PIXELFORMAT_BGR24,
        RGB888 = SDL_PIXELFORMAT_RGB888,
        RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
        BGR888 = SDL_PIXELFORMAT_BGR888,
        BGRX8888 = SDL_PIXELFORMAT_BGRX8888,
        ARGB8888 = SDL_PIXELFORMAT_ARGB8888,
        RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
        ABGR8888 = SDL_PIXELFORMAT_ABGR8888,
        BGRA8888 = SDL_PIXELFORMAT_BGRA8888,
        ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,

        /* Aliases for RGBA byte arrays of color data, for the current platform */
        RGBA32 = SDL_PIXELFORMAT_RGBA32,
        ARGB32 = SDL_PIXELFORMAT_ARGB32,
        BGRA32 = SDL_PIXELFORMAT_BGRA32,
        ABGR32 = SDL_PIXELFORMAT_ABGR32,

        YV12 = SDL_PIXELFORMAT_YV12,
        IYUV = SDL_PIXELFORMAT_IYUV,
        YUY2 = SDL_PIXELFORMAT_YUY2,
        UYVY = SDL_PIXELFORMAT_UYVY,
        YVYU = SDL_PIXELFORMAT_YVYU,
        NV12 = SDL_PIXELFORMAT_NV12,
        NV21 = SDL_PIXELFORMAT_NV21,
        EXTERNAL_OES = SDL_PIXELFORMAT_EXTERNAL_OES
	};
}


namespace sdl
{
	struct DisplayMode
	{
		unsigned int width;
		unsigned int height;
        PixelFormat format;
		unsigned int framerate;

		DisplayMode() = default;
		DisplayMode(const DisplayMode&) = default;
		DisplayMode(DisplayMode&&) = default;

		DisplayMode& operator= (const DisplayMode&) = default;
		DisplayMode& operator= (DisplayMode&&) = default;
	};

	std::vector<DisplayMode> GetAllDisplayModes();

	SDL_Window* CreateWindow(const std::string& title, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	SDL_GLContext CreateContext(SDL_Window* window);
}
