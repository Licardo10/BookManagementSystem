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

void DrawMainMenu();		// 绘制主菜单界面

void PrintResult(const string title, const vector<Book>& list);		// 打印查询结果

void PrintStatistics();		// 打印统计信息

bool IsInButton(int mx, int my, const Button& btn);		// 判断鼠标坐标是否在按钮范围内

string InputByConsole(const string& prompt);			// 从控制台输入字符串

void DrawSearchMenu();			// 绘制查找界面

void DrawModifyMenu();			// 绘制修改界面

void DrawBorrowMenu();			// 绘制借阅界面

void DrawStatisticsMenu();		// 绘制统计界面