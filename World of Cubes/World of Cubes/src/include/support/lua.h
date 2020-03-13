#pragma once

#include <lua/lua.hpp>
#include <string>
#include <vector>

namespace lua
{
	class LuaState;
	class LuaScript;

	class LuaState
	{
	private:
		lua_State* _ls;

	public:
		LuaState();
		LuaState(const LuaState&) = delete;
		LuaState(LuaState&& ls) noexcept;
		~LuaState();

		LuaState& operator= (const LuaState&) = delete;
		LuaState& operator= (LuaState&& ls) noexcept;

		void openLibs();

		bool pushScript(const LuaScript& script);
		bool executeScript(const LuaScript& script);

		friend class LuaScript;
	};



	class LuaScript
	{
	private:
		std::string _name;
		std::vector<std::vector<char>> _data;

	public:
		LuaScript();
		explicit LuaScript(const std::string& filepath, LuaState* ls = nullptr);
		~LuaScript();

		bool load(const std::string& filepath, LuaState* ls = nullptr);

		bool push(LuaState& ls) const;
		bool execute(LuaState* ls = nullptr) const;

		inline void setName(const std::string& name) { _name = name; }
		inline const std::string& getName() { return _name; }

	private:
		struct ReaderIterator
		{
			const std::vector<std::vector<char>>& data;
			size_t offset;
		};

		static int _writer(lua_State* L, const void* p, size_t sz, void* ud);
		static const char* _reader(lua_State* L, void* data, size_t* size);
	};
}




namespace lua::utils
{
	template<typename _Ty>
	inline _Ty stack_get(lua_State* ls, int index = -1)
	{
		return _Ty{};
	}

	template<>
	inline int32_t stack_get<int32_t>(lua_State* ls, int index)
	{
		if (!lua_isnumber(ls, index))
			return 0;
		return static_cast<int32_t>(lua_tonumber(ls, index));
	}

	template<>
	inline int64_t stack_get<int64_t>(lua_State* ls, int index)
	{
		if (!lua_isnumber(ls, index))
			return 0;
		return static_cast<int64_t>(lua_tonumber(ls, index));
	}

	template<>
	inline uint32_t stack_get<uint32_t>(lua_State* ls, int index)
	{
		if (!lua_isnumber(ls, index))
			return 0;
		return static_cast<uint32_t>(lua_tonumber(ls, index));
	}

	template<>
	inline uint64_t stack_get<uint64_t>(lua_State* ls, int index)
	{
		if (!lua_isnumber(ls, index))
			return 0;
		return static_cast<uint64_t>(lua_tonumber(ls, index));
	}

	template<>
	inline float stack_get<float>(lua_State* ls, int index)
	{
		if (!lua_isnumber(ls, index))
			return 0;
		return static_cast<float>(lua_tonumber(ls, index));
	}

	template<>
	inline double stack_get<double>(lua_State* ls, int index)
	{
		if (!lua_isnumber(ls, index))
			return 0;
		return static_cast<double>(lua_tonumber(ls, index));
	}

	template<>
	inline bool stack_get<bool>(lua_State* ls, int index)
	{
		if (!lua_isboolean(ls, index))
			return false;
		return static_cast<bool>(lua_toboolean(ls, index));
	}

	template<>
	inline std::string stack_get<std::string>(lua_State* ls, int index)
	{
		if (!lua_isstring(ls, index))
			return {};
		return { lua_tostring(ls, index) };
	}
}




namespace lua::utils
{

}
