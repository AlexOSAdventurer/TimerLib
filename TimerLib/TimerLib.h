// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the TIMERLIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// TIMERLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef TIMERLIB_EXPORTS
#define TIMERLIB_API __declspec(dllexport)
#else
#define TIMERLIB_API __declspec(dllimport)
#endif

#include <lua.hpp>
#include <lauxlib.h>

extern "C" {
	#include <stdio.h>
	FILE __iob_func[3] = { *stdin, *stdout, *stderr };
};
