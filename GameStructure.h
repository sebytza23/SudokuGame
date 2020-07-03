#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include <sstream>
#include <iterator>
#include "resource.h"

using namespace std;

namespace GameStructure
{
	#define unassigned_number 0

	void SetDigitToTextBox(HWND wnd, int x, string data);
	bool CheckNumberSafe(int matrix[9][9], int row, int column, int number);
	bool CheckLocation(int matrix[9][9], int &row, int &column);
	bool SolveTheGame(int matrix[9][9]);
	bool NumberInRow(int matrix[9][9], int row, int number);
	bool NumberInColumn(int matrix[9][9], int column, int number);
	bool NumberInBox(int matrix[9][9], int start_row, int start_column, int number);

	enum
	{
		GAME_EASY_MODE = 0,
		GAME_MEDIUM_MODE = 1,
		GAME_HARD_MODE = 2
	};
	//Sistem Folosit vizual Windows API
};
