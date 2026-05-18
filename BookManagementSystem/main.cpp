/*
这是一个基于C++ EasyX的图书管理系统，实现了图书的查找、修改、借阅和统计功能，并提供了一个图形化界面。
已上传至GitHub，https://github.com/Licardo10/BookManagementSystem
*/

#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <iostream>
#include <string>
#include "Book.h"
#include "Graphics.h"
using namespace std;

const wstring DataFile = L"BookManagementSystem\\books.txt";

// 初始化数据：优先从源码目录加载，否则从.exe同级目录加载
static bool InitData()
{
	// 在文件目录中加载数据
	if (LoadDataFromFile(books, L"BookManagementSystem\\books.txt"))
		return true;
	// 在.exe文件目录中加载数据
	if (LoadDataFromFile(books, L"books.txt"))
		return true;
	return false;
}

int main()
{
	// 初始化窗口
	initgraph(win_width, win_height);
	setbkcolor(RGB(35, 35, 45));

	// 获取窗口地址并设置标题
	HWND hwnd = GetHWnd();
	SetWindowTextW(hwnd, L"图书管理系统");

	InitData();

	int page = 0; // 0=主菜单	1=查找界面	2=修改界面	3=借阅界面	4=信息界面

	DrawMainMenu();

	// 消息循环
	ExMessage msg = {0};
	while (true)
	{
		// 监测鼠标和键盘事件
		if (peekmessage(&msg, EM_MOUSE | EM_KEY))
		{
			// 按ESC退出
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
			{
				closegraph();
				return 0;
			}
			// 鼠标点击事件
			if (msg.message == WM_LBUTTONDOWN)
			{
				int mx = msg.x;
				int my = msg.y;

				// 判断是否需要重绘界面
				bool Redraw = false;

				if (page == 0)
				{
					for (int i = 0; i < NumberOfmainButton; i++)
					{
						if (IsInButton(mx, my, mainButtons[i]))
						{
							switch (i)
							{
							case 0:
							{
								page = 1;
								DrawSearchMenu();
								break;
							}
							case 1:
							{
								page = 2;
								DrawModifyMenu();
								break;
							}
							case 2:
							{
								page = 3;
								DrawBorrowMenu();
								break;
							}
							case 3:
							{
								page = 4;
								DrawStatisticsMenu();
								break;
							}
							case 4:
							{
								closegraph();
								return 0;
								break;
							}
							}
						}
					}
				}
				else if (page == 1)
				{
					for (int i = 0; i < NumberOfsearchButton; i++)
					{
						if (IsInButton(mx, my, searchButtons[i]))
						{
							switch (i)
							{
							case 0:
							{ // 按书名查找
								wstring name = InputByBox(L"请输入书名:");
								vector<Book> c0 = FuzzySearchByName(books, name);
								PrintResult(L"结果为:", c0);
								break;
							}
							case 1:
							{ // 按出版社查找
								wstring name = InputByBox(L"请输入出版社:");
								vector<Book> c1 = FuzzySearchByPublisher(books, name);
								PrintResult(L"结果为:", c1);
								break;
							}
							case 2:
							{ // 组合查找
								wstring name = InputByBox(L"请输入关键字(以空格分隔):");
								vector<Book> c2 = CombinedSearchByName(books, name);
								PrintResult(L"结果为:", c2);
								break;
							}
							case 3:
							{ // 显示所有图书
								vector<Book> c3 = GetAllBooks(books);
								PrintResult(L"结果为:", c3);
								break;
							}
							case 4:
							{ // 返回主菜单
								page = 0;
								break;
							}
							}
							Redraw = true;
							break;
						}
					}
				}
				else if (page == 2)
				{
					for (int i = 0; i < NumberOfmodifyButton; i++)
					{
						if (IsInButton(mx, my, modifyButtons[i]))
						{
							switch (i)
							{
							case 0:
							{ // 按ISBN修改图书
								wstring isbn = InputByBox(L"ISBN:");
								Book *c0 = SearchBookByISBN(books, isbn);
								if (c0 == NULL)
								{
									MessageBoxW(hwnd, L"未找到该ISBN！", L"错误", MB_OK);
									break;
								}

								wstring input;
								input = InputByBox(L"新书名 (留空不变): ");
								if (!input.empty())
									c0->name = input;

								input = InputByBox(L"新作者 (留空不变): ");
								if (!input.empty())
									c0->author = input;

								input = InputByBox(L"新出版社 (留空不变): ");
								if (!input.empty())
									c0->publisher = input;

								input = InputByBox(L"新出版日期 (留空不变): ");
								if (!input.empty())
									c0->pubdate = input;

								input = InputByBox(L"新价格 (留空不变): ");
								if (!input.empty())
									c0->price = _wtof(input.c_str());

								SaveDataToFile(books, DataFile);
								break;
							}
							case 1:
							{ // 按书名修改
								wstring name = InputByBox(L"请输入原书名:");
								Book *c1 = SearchBookByName(books, name);
								if (c1 == NULL)
								{
									MessageBoxW(hwnd, L"未找到该书名！", L"错误", MB_OK);
									break;
								}

								wstring input;
								input = InputByBox(L"新书名 (留空不变): ");
								if (!input.empty())
									c1->name = input;

								input = InputByBox(L"新作者 (留空不变): ");
								if (!input.empty())
									c1->author = input;

								input = InputByBox(L"新出版社 (留空不变): ");
								if (!input.empty())
									c1->publisher = input;

								input = InputByBox(L"新出版日期 (留空不变): ");
								if (!input.empty())
									c1->pubdate = input;

								input = InputByBox(L"新价格 (留空不变): ");
								if (!input.empty())
									c1->price = _wtof(input.c_str());

								SaveDataToFile(books, DataFile);
								break;
							}
							case 2:
							{ // 添加新书
								Book newbook;
								wstring input;

								input = InputByBox(L"ISBN:");
								newbook.ISBN = input;
								newbook.name = InputByBox(L"书名: ");
								newbook.author = InputByBox(L"作者: ");
								newbook.publisher = InputByBox(L"出版社: ");
								newbook.pubdate = InputByBox(L"出版日期 (如 2026-01-01): ");
								input = InputByBox(L"价格: ");
								newbook.price = _wtof(input.c_str());
								newbook.state = 0;

								AddBook(books, newbook);
								SaveDataToFile(books, DataFile);
								break;
							}
							case 3:
							{ // 按ISBN删除
								wstring isbn = InputByBox(L"请输入:");
								if (DeleteBookByISBN(books, isbn))
								{
									SaveDataToFile(books, DataFile);
									MessageBoxW(hwnd, L"删除成功!", L"提示", MB_OK);
								}
								else
									MessageBoxW(hwnd, L"未找到该图书！", L"错误", MB_OK);
								break;
							}
							case 4:
							{ // 按书名删除
								wstring name = InputByBox(L"请输入:");
								if (DeleteBookByName(books, name))
								{
									SaveDataToFile(books, DataFile);
									MessageBoxW(hwnd, L"删除成功!", L"提示", MB_OK);
								}
								else
									MessageBoxW(hwnd, L"未找到该图书！", L"错误", MB_OK);
								break;
							}
							case 5:
							{
								page = 0;
								break;
							}
							}
							Redraw = true;
							break;
						}
					}
				}
				else if (page == 3)
				{
					for (int i = 0; i < NumberOfborrowButton; i++)
					{
						if (IsInButton(mx, my, borrowButtons[i]))
						{
							switch (i)
							{
							case 0:
							{ // 借出
								wstring isbn = InputByBox(L"请输入ISBN:");
								Book *book = SearchBookByISBN(books, isbn);
								if (!book)
									MessageBoxW(hwnd, L"未找到该ISBN！", L"错误", MB_OK);
								else if (book->state == 1)
									MessageBoxW(hwnd, L"该书已借出！", L"提示", MB_OK);
								else
								{
									BorrowByISBN(books, isbn);
									SaveDataToFile(books, DataFile);
									MessageBoxW(hwnd, L"借出成功！", L"提示", MB_OK);
								}
								break;
							}
							case 1:
							{ // 归还
								wstring isbn = InputByBox(L"请输入ISBN:");
								Book *book = SearchBookByISBN(books, isbn);
								if (!book)
									MessageBoxW(hwnd, L"未找到", L"错误", MB_OK);
								else if (book->state == 0)
									MessageBoxW(hwnd, L"该书未被借出", L"提示", MB_OK);
								else
								{
									ReturnByISBN(books, isbn);
									SaveDataToFile(books, DataFile);
									MessageBoxW(hwnd, L"归还成功", L"提示", MB_OK);
								}
								break;
							}
							case 2:
								page = 0;
								break;
							}
							Redraw = true;
							break;
						}
					}
				}
				else if (page == 4)
				{
					for (int i = 0; i < NumberOfstatisticsButton; i++)
					{
						if (IsInButton(mx, my, statisticsButtons[i]))
						{
							switch (i)
							{
							case 0:
							{ // 查看所有图书
								vector<Book> c0 = GetAllBooks(books);
								PrintResult(L"所有图书", c0);
								break;
							}
							case 1:
							{ // 统计信息
								PrintStatistics();
								break;
							}
							case 2:
							{ // 返回
								page = 0;
								break;
							}
							}
							Redraw = true;
							break;
						}
					}
				}

				if (Redraw)
				{
					if (page == 0)
						DrawMainMenu();
					else if (page == 1)
						DrawSearchMenu();
					else if (page == 2)
						DrawModifyMenu();
					else if (page == 3)
						DrawBorrowMenu();
					else if (page == 4)
						DrawStatisticsMenu();
				}
			}
		}
	}
	return 0;
}