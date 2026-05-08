#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <iostream>
#include <string>
#include "Book.h"
#include "Graphics.h"
using namespace std;

const string DataFile = "books.txt";

//初始化数据
static bool InitData()
{
	if (LoadDataFromFile(books, DataFile))
		return true;
	else
		return false;
}

int	main()
{
	initgraph(win_width, win_height);
	setbkcolor(RGB(35, 35, 45));
	HWND hwnd = GetHWnd();
	SetWindowTextA(hwnd, "图书管理系统");

	InitData();

	int page = 0;	//0=主菜单	1=查找界面	2=修改界面	3=借阅界面	4=信息界面

	DrawMainMenu();

	ExMessage msg = { 0 };
	while (true)
	{
		if (peekmessage(&msg, EM_MOUSE | EM_KEY))
		{
			//按ESC退出
			if (msg.message == WM_KEYDOWN && msg.vkcode == VK_ESCAPE)
			{
				closegraph();
				return 0;
			}
			//
			if (msg.message == WM_LBUTTONDOWN)
			{
				int mx = msg.x;
				int my = msg.y;
				bool Redraw = false;

				//主菜单
				if(page==0)
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
							{
								string name = InputByConsole("请输入书名:");
								vector<Book> c0 = FuzzySearchByName(books, name);
								PrintResult("结果为:",c0);
								break;
							}
							case 1:
							{
								string name = InputByConsole("请输入出版社:");
								vector<Book> c1 = FuzzySearchByPublisher(books, name);
								PrintResult("结果为:", c1);
								break;
							}
							case 2:
							{
								string name = InputByConsole("请输入关键字(以空格分隔):");
								vector<Book> c2 = CombinedSearchByName(books, name);
								PrintResult("结果为:", c2);
								break;
							}
							case 3:
							{
								vector<Book> c3 = GetAllBooks(books);
								PrintResult("结果为:", c3);
								break;
							}
							case 4:
							{
								page = 0;
								break;
							}
							}
							Redraw = true;
							//break;
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
							case 0://按ISBN修改图书
							{
								string isbn = InputByConsole("ISBN:");
								Book* c0 = SearchBookByISBN(books, isbn);

								string input;
								input = InputByConsole("新书名 (留空不变): ");
								if (!input.empty()) 
									c0->name = input;

								input = InputByConsole("新作者 (留空不变): ");
								if (!input.empty()) 
									c0->author = input;

								input = InputByConsole("新出版社 (留空不变): ");
								if (!input.empty()) 
									c0->publisher = input;

								input = InputByConsole("新出版日期 (留空不变): ");
								if (!input.empty()) 
									c0->pubdate = input;

								input = InputByConsole("新价格 (留空不变): ");
								if (!input.empty()) 
									c0->price = atof(input.c_str());

								SaveDataToFile(books, DataFile);
								break;
							}
							case 1://按书名修改
							{
								string name = InputByConsole("请输入原书名:");
								Book* c1 = SearchBookByName(books, name);

								string input;
								input = InputByConsole("新书名 (留空不变): ");
								if (!input.empty())
									c1->name = input;

								input = InputByConsole("新作者 (留空不变): ");
								if (!input.empty())
									c1->author = input;

								input = InputByConsole("新出版社 (留空不变): ");
								if (!input.empty())
									c1->publisher = input;

								input = InputByConsole("新出版日期 (留空不变): ");
								if (!input.empty())
									c1->pubdate = input;

								input = InputByConsole("新价格 (留空不变): ");
								if (!input.empty())
									c1->price = atof(input.c_str());

								SaveDataToFile(books, DataFile);
								break;
							}
							case 2://添加新书
							{
								Book newbook;
								string input;

								input = InputByConsole("ISBN:");
								newbook.ISBN = input;
								newbook.name = InputByConsole("书名: ");
								newbook.author = InputByConsole("作者: ");
								newbook.publisher = InputByConsole("出版社: ");
								newbook.pubdate = InputByConsole("出版日期 (如 2026-01-01): ");
								input = InputByConsole("价格: ");
								newbook.price = atof(input.c_str());
								newbook.state = 0;

								AddBook(books, newbook);
								SaveDataToFile(books, DataFile);
								break;
							}
							case 3://按ISBN删除
							{
								string isbn = InputByConsole("请输入:");
								if (DeleteBookByISBN(books, isbn))
								{
									SaveDataToFile(books, DataFile);
									MessageBoxA(hwnd, "删除成功!", "提示", MB_OK);
								}
								else
									MessageBoxA(hwnd, "未找到该图书！", "错误", MB_OK);
								break;
							}
							case 4://按书名删除
							{
								string name = InputByConsole("请输入:");
								if (DeleteBookByName(books, name))
								{
									SaveDataToFile(books, DataFile);
									MessageBoxA(hwnd, "删除成功!", "提示", MB_OK);
								}
								else
									MessageBoxA(hwnd, "未找到该图书！", "错误", MB_OK);
								break;
							}
							case 5:
							{
								page = 0;
								break;
							}
							}
							Redraw = true;
							//break;
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
							case 0: //借出
							{
								string isbn = InputByConsole("请输入ISBN:");
								Book* book = SearchBookByISBN(books, isbn);
								if (!book)
									MessageBoxA(hwnd, "未找到该ISBN！", "错误", MB_OK);
								else if (book->state == 1)
									MessageBoxA(hwnd, "该书已借出！", "提示", MB_OK);
								else
								{
									BorrowByISBN(books, isbn);
									SaveDataToFile(books, DataFile);
									MessageBoxA(hwnd, "借出成功！", "提示", MB_OK);
								}
								break;
							}
							case 1: // 归还
							{
								string isbn = InputByConsole("请输入ISBN:");
								Book* book = SearchBookByISBN(books, isbn);
								if (!book)
									MessageBoxA(hwnd, "未找到", "错误", MB_OK);
								else if (book->state == 0)
									MessageBoxA(hwnd, "该书未被借出", "提示", MB_OK);
								else
								{
									ReturnByISBN(books, isbn);
									SaveDataToFile(books, DataFile);
									MessageBoxA(hwnd, "归还成功", "提示", MB_OK);
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
							case 0: // 查看所有图书
							{
								vector<Book> c0 = GetAllBooks(books);
								PrintResult("所有图书", c0);
								break;
							}
							case 1: // 统计信息
								PrintStatistics();
								break;
							case 2: // 返回
								page = 0;
								break;
							}
							Redraw = true;
							break;
						}
					}
				}

				if (Redraw)
				{
					if (page == 0) DrawMainMenu();
					else if (page == 1) DrawSearchMenu();
					else if (page == 2) DrawModifyMenu();
					else if (page == 3) DrawBorrowMenu();
					else if (page == 4) DrawStatisticsMenu();
				}
			}
		}
	}
	return 0;
}