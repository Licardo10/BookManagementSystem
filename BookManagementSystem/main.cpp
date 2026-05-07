#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <iostream>
#include <string>
#include "Book.h"
#include "Graphics.h"
using namespace std;

const string DataFile = "books.txt";

static bool InitData()
{
	if (LoadBooksFromFile(books, DataFile))
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

				for (int i = 0; i < NumberOfButton; i++)
				{
					if (IsInButton(mx, my, mainButtons[i]))
					{
						switch (i) 
						{
							case 0://查看所有图书
							{
								vector<Book> c1 = GetAllBooks(books);
								ShowResultList("所有图书", c1);
								break;
							}
							case 1://按书名模糊查找
							{
								string name = ConsoleInput("请输入关键字:");
								if (!name.empty())
								{
									vector<Book> c2 = FuzzySearchBookByName(books, name);
									ShowResultList("结果为:", c2);
								}
								break;
							}
							case 2:
							{
								string name = ConsoleInput("请输入关键字(以空格分隔):");
								vector<Book> c3 = CombinedSearchByName(books, name);
								ShowResultList("结果为:", c3);
								break;
							}
							case 3:
							{
								string name = ConsoleInput("请输入关键字:");
								vector<Book> c4 = FuzzySearchByPublisher(books, name);
								ShowResultList("结果为:", c4);
								break;
							}
							case 4:
							{
								Book newbook;
								string input;
								input = ConsoleInput("ISBN:"); 
								if (input.empty()) 
									break;
								newbook.ISBN = input;
								newbook.name = ConsoleInput("书名: ");
								newbook.author = ConsoleInput("作者: ");
								newbook.publisher = ConsoleInput("出版社: ");
								newbook.pubdate = ConsoleInput("出版日期 (如 2023-01-01): ");
								input = ConsoleInput("价格: ");
								newbook.price = atof(input.c_str());
								newbook.state = 0;
								AddBook(books, newbook);
								SaveBooksToFile(books, DataFile);
								break;
							}
							case 5:
							{
								string isbn = ConsoleInput("ISBN:");
								Book* c6 = SearchBookByISBN(books, isbn);
								string input;
								input = ConsoleInput("新书名 (留空不变): ");
								if (!input.empty()) c6->name = input;
								input = ConsoleInput("新作者 (留空不变): ");
								if (!input.empty()) c6->author = input;
								input = ConsoleInput("新出版社 (留空不变): ");
								if (!input.empty()) c6->publisher = input;
								input = ConsoleInput("新出版日期 (留空不变): ");
								if (!input.empty()) c6->pubdate = input;
								input = ConsoleInput("新价格 (留空不变): ");
								if (!input.empty()) c6->price = atof(input.c_str());
								SaveBooksToFile(books, DataFile);
								break;
							}
							case 6:
							{
								string isbn = ConsoleInput("ISBN:");
								if (DeleteBookByISBN(books, isbn))
								{
									SaveBooksToFile(books, DataFile);
									MessageBoxA(hwnd, "删除成功!", "提示", MB_OK);
								}
								else
								{
									MessageBoxA(hwnd, "未找到该ISBN的图书！", "错误", MB_OK);
								}
								break;
							}
							case 7:
							{
								ShowStatistics();
								break;
							}
							case 8:
							{
								closegraph();
								return 0;
							}
						}
						if (i != 8)
							DrawMainMenu();
					}
				}
			}
		}
	}
	return 0;
}