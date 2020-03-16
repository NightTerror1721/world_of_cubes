#include <iostream>

#include "support/vectors.h"
#include "support/matrix44.h"

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


	/*lua::LuaState state;
	lua::LuaScript script;

	state.openLibs();
	
	//state.loadScript("test-scripts/test.lua");
	script.load("test-scripts/test.lua");
	script.execute(&state);*/



	return 0;
}
