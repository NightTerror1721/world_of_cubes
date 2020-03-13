#include "support/lua.h"

#include <fstream>
#include <utility>

lua::LuaState::LuaState() :
	_ls{ luaL_newstate() }
{}
lua::LuaState::LuaState(LuaState&& ls) noexcept :
	_ls{ std::move(ls._ls) }
{
	ls._ls = nullptr;
}
lua::LuaState::~LuaState()
{
	if (_ls)
	{
		lua_close(_ls);
		_ls = nullptr;
	}
}

lua::LuaState& lua::LuaState::operator= (LuaState&& ls) noexcept
{
	this->~LuaState();
	_ls = std::move(ls._ls);
	ls._ls = nullptr;
	return *this;
}

void lua::LuaState::openLibs()
{
	luaL_openlibs(_ls);
}

bool lua::LuaState::pushScript(const LuaScript& script)
{
	return script.push(*this);
}

bool lua::LuaState::executeScript(const lua::LuaScript& script)
{
	return script.execute(this);
}






lua::LuaScript::LuaScript() :
	_name{},
	_data{}
{}
lua::LuaScript::LuaScript(const std::string& filepath, LuaState* ls) :
	LuaScript{}
{
	load(filepath, ls);
}
lua::LuaScript::~LuaScript() {}


static int lua_script_writer_impl(lua_State* L, const void* p, size_t sz, void* ud)
{
	std::vector<char>& buf = *reinterpret_cast<std::vector<char>*>(ud);

	size_t old_size = buf.size();
	buf.resize(old_size + sz);

	std::memcpy(&buf[old_size], p, sz);
	return 0;
}

bool lua::LuaScript::load(const std::string& filepath, LuaState* ls)
{
	lua_State* L;
	if (ls)
		L = ls->_ls;
	else
	{
		L = luaL_newstate();
		luaL_openlibs(L);
	}

	int res = luaL_loadfile(L, filepath.c_str());
	if (res == LUA_OK)
	{
		_data.clear();
		res = lua_dump(L, &_writer, &_data, 0);
		lua_pop(L, 1);
	}

	if (!ls)
	{
		lua_close(L);
	}
	
	return res == LUA_OK;
}

bool lua::LuaScript::push(LuaState& ls) const
{
	ReaderIterator it = { _data, 0U };
	int res = lua_load(ls._ls, &_reader, &it, _name.c_str(), "b");
	return res == LUA_OK;
}

bool lua::LuaScript::execute(LuaState* ls) const
{
	lua_State* L;
	if (ls)
		L = ls->_ls;
	else
	{
		L = luaL_newstate();
		luaL_openlibs(L);
	}

	ReaderIterator it = { _data, 0U };
	int res = lua_load(L, &_reader, &it, _name.c_str(), "b");
	if (res == LUA_OK)
	{
		res = lua_pcall(L, 0, LUA_MULTRET, 0);
	}

	if (!ls)
	{
		lua_close(L);
	}

	return res == LUA_OK;
}

int lua::LuaScript::_writer(lua_State* L, const void* p, size_t sz, void* ud)
{
	std::vector<std::vector<char>>& script_data = *reinterpret_cast<std::vector<std::vector<char>>*>(ud);
	std::vector<char>& script_part = script_data.emplace_back(sz);

	script_part.resize(sz);
	std::memcpy(&script_part[0], p, sz);
	return 0;
}

const char* lua::LuaScript::_reader(lua_State* L, void* data, size_t* size)
{
	ReaderIterator& it = *reinterpret_cast<ReaderIterator*>(data);

	if (it.offset < it.data.size())
	{
		const std::vector<char>& script_part = it.data[it.offset++];

		*size = script_part.size();
		return script_part.data();
	}

	*size = 0;
	return nullptr;
}

