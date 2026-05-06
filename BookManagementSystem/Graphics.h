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
extern const int Button_count;

void DrawMainMenu();

void ShowResultList(const string title, const vector<Book>& list);

void ShowStatistics();

bool IsInButton(int mx, int my, const Button& btn);

string ConsoleInput(const string& prompt);