#include <iostream>

#include "support/vectors.h"
#include "support/matrix44.h"
#include "support/color.h"
#include "support/SDL.h"

#include <sfml/Graphics/Shader.hpp>


int main(int argc, char** argv)
{
	vec2 v0;
	vec2u v1;

	v0.set(0.7f, .36f);
	v1 = static_cast<vec2u>(v0);
	vec2i v2 = static_cast<vec2i>(v0);

	vec4 vvv = { 5, 6, 7, 8 };
	
	v1 = static_cast<vec2u>(vvv);

	size_t s = sizeof(mat4);

	vec3f vcol = static_cast<vec3f>(Color::BLUE);

	sdl::initiate();

	/*for (const sdl::DisplayMode& mode : sdl::GetAllDisplayModes())
	{
		std::cout << "[w=" << mode.width << "; h=" << mode.height << "; f=" << mode.format << "; fr=" << mode.framerate << "]" << std::endl;
	}*/

	sdl::quit();

	/*lua::LuaState state;
	lua::LuaScript script;

	state.openLibs();
	
	//state.loadScript("test-scripts/test.lua");
	script.load("test-scripts/test.lua");
	script.execute(&state);*/

	//SDL_Event e;



	return 0;
}
