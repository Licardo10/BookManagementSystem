#pragma once
#include <graphics.h>
#include <string>
#include <vector>
#include "Book.h"

const int win_width = 800;
const int win_height = 600;

struct Button
{
	int x, y, w, h;
	string text;
};

extern Button mainButtons[];
extern const int NumberOfmainButton;

extern Button searchButtons[];
extern const int NumberOfsearchButton;

extern Button modifyButtons[];
extern const int NumberOfmodifyButton;

extern Button borrowButtons[];
extern const int NumberOfborrowButton;

extern Button statisticsButtons[];
extern const int NumberOfstatisticsButton;

void DrawMainMenu();

void PrintResult(const string title, const vector<Book>& list);

void PrintStatistics();

bool IsInButton(int mx, int my, const Button& btn);

string InputByConsole(const string& prompt);

void DrawSearchMenu();

void DrawModifyMenu();

void DrawBorrowMenu();

void DrawStatisticsMenu();