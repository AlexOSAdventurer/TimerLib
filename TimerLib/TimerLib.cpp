// TimerLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "TimerLib.h"


extern "C" {

	typedef struct TimerLibTimer {
		__int64 last;
		double freq;
		LARGE_INTEGER tint;
		bool running;
		double total;
	} TimerLibTimer;

	static int __index(lua_State *L) {
		TimerLibTimer* timer = (TimerLibTimer*)luaL_checkudata(L, 1, "TimerLibTimer");

		luaL_getmetatable(L, "TimerLibTimer");
		lua_pushvalue(L, 2);
		lua_rawget(L, -2);

		return 1;
	}

	static void set_timer_metatable(lua_State *L, int index) {
		luaL_getmetatable(L, "TimerLibTimer");
		lua_setmetatable(L, index - 1);
	}

	static int create(lua_State *L) {
		double freq = luaL_checknumber(L, 1);
		TimerLibTimer* timer = (TimerLibTimer*)lua_newuserdata(L, sizeof(TimerLibTimer));
		memset(timer, 0, sizeof(TimerLibTimer));
		set_timer_metatable(L, -1);
		if (!QueryPerformanceFrequency(&(timer->tint))) {
			luaL_error(L, "Counter creation failed: QueryPerformanceFrequency failed!");
		};
		timer->freq = double(timer->tint.QuadPart) / freq;
		timer->running = false;
		return 1;
	}

	static int start(lua_State *L) {
		TimerLibTimer* timer = (TimerLibTimer*)luaL_checkudata(L, 1, "TimerLibTimer");
		QueryPerformanceCounter(&(timer->tint));
		timer->last = timer->tint.QuadPart;
		timer->running = true;

		return 0;
	}

	static void update_timer(TimerLibTimer* timer) {
		if (timer->running) {
			QueryPerformanceCounter(&(timer->tint));
			double res = double(timer->tint.QuadPart - timer->last) / timer->freq;
			timer->total = timer->total + res;
			timer->last = timer->tint.QuadPart;
		};
	}


	static int getcount(lua_State *L) {
		TimerLibTimer* timer = (TimerLibTimer*)luaL_checkudata(L, 1, "TimerLibTimer");
		update_timer(timer);
		lua_pushnumber(L, timer->total);

		return 1;
	}

	static int stop(lua_State *L) {
		TimerLibTimer* timer = (TimerLibTimer*)luaL_checkudata(L, 1, "TimerLibTimer");
		update_timer(timer);
		timer->running = false;

		return 0;
	}

	static int reset(lua_State *L) {
		TimerLibTimer* timer = (TimerLibTimer*)luaL_checkudata(L, 1, "TimerLibTimer");
		timer->total = 0;
		timer->running = false;
		return 0;
	}

	static const struct luaL_reg timerlib[] = {
		{ "create", create },
		{ "getcount", getcount},
		{ "reset", reset},
		{ "start", start},
		{ "stop",  stop},
		{ NULL, NULL }
	};


	TIMERLIB_API int luaopen_TimerLib(lua_State *L) {
		luaL_newmetatable(L, "TimerLibTimer");
		lua_pushcfunction(L, __index);
		lua_setfield(L, -2, "__index");
		lua_pushcfunction(L, getcount);
		lua_setfield(L, -2, "getcount");
		lua_pushcfunction(L, reset);
		lua_setfield(L, -2, "reset");
		lua_pushcfunction(L, start);
		lua_setfield(L, -2, "start");
		lua_pushcfunction(L, stop);
		lua_setfield(L, -2, "stop");
		lua_pop(L, 1);
		luaL_openlib(L, "timerlib", timerlib, 0);
		return 1;
	}

}