// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

// Headers for CppUnitTest
#include "CppUnitTest.h"

// TODO: reference additional headers your program requires here
extern "C" {
	__declspec(dllimport) char* GetTeam();
	__declspec(dllimport) bool SetMaze(const int** data, int width, int height);
	__declspec(dllimport) int** GetMaze(int& width, int& height);
	__declspec(dllimport) bool GetNextPosition(int& xpos, int& ypos);
	__declspec(dllimport) bool SetStart(int xpos, int ypos);
	__declspec(dllimport) bool GetStart(int& xpos, int& ypos);
	__declspec(dllimport) bool SetEnd(int xpos, int ypos);
	__declspec(dllimport) bool GetEnd(int& xpos, int& ypos);
}
