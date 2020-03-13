#include <iostream>

#include "support/lua.h"
#include "support/vectors.h"

int main(int argc, char** argv)
{
	vec2 v0;
	vec2u v1;

	v0.set(0.7, .36);
	v1 = static_cast<vec2u>(v0);
	vec2i v2 = static_cast<vec2i>(v0);


	lua::LuaState state;
	lua::LuaScript script;

	state.openLibs();
	
	//state.loadScript("test-scripts/test.lua");
	script.load("test-scripts/test.lua");
	script.execute(&state);



	return 0;
}
