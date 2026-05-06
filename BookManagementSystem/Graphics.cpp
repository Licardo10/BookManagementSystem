#define _CRT_SECURE_NO_WARNINGS
#include "Graphics.h"
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <windows.h>

Button mainButtons[] =
{
    { 100, 150, 280, 40, "1. 查看所有图书" },
    { 100, 200, 280, 40, "2. 按书名模糊查找" },
    { 100, 250, 280, 40, "3. 组合查询 (如 设计+教程)" },
    { 100, 300, 280, 40, "4. 按出版社查找" },
    { 100, 350, 280, 40, "5. 添加新书" },
    { 430, 150, 280, 40, "6. 修改图书 (按ISBN)" },
    { 430, 200, 280, 40, "7. 删除图书 (按ISBN)" },
    { 430, 250, 280, 40, "8. 统计信息" },
    { 430, 350, 280, 40, "9. 退出系统" }
};

const int Button_count = sizeof(mainButtons) / sizeof(mainButtons[0]);

void DrawMainMenu()
{
    cleardevice();

    settextstyle(36, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(250, 50, "图书管理系统");

    settextstyle(18, 0,"微软雅黑");
    settextcolor(RGB(200, 200, 200));
    outtextxy(200, 100, "请点击下方按钮选择功能");

    for (int i = 0; i < Button_count; i++)
    {
        Button btn = mainButtons[i];

        setfillcolor(RGB(60, 130, 200));
        setlinecolor(RGB(255, 255, 255));

        fillroundrect(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, 10, 10);
        setbkmode(TRANSPARENT);

        settextstyle(18, 0, "微软雅黑");
        settextcolor(RGB(255, 255, 255));

        int tw = textwidth(btn.text.c_str());
        int th = textheight(btn.text.c_str());
        //字符居中
        outtextxy(btn.x + (btn.w - tw) / 2, btn.y + (btn.h - th) / 2, 
            btn.text.c_str());
    }
}

void ShowResultList(const string title, const vector<Book>& list)
{
    cleardevice();

    settextstyle(24, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(50, 20, title.c_str());

    settextstyle(16, 0, "微软雅黑");
    settextcolor(RGB(220, 220, 220));

    int y = 70;

    if (list.empty())
        outtextxy(50, y, "没有找到相关图书");
    else
    {
        char line[256];
        for (auto it = list.begin(); it != list.end(); it++)
        {
            sprintf_s(line, "ISBN:%-20s 书名:%-30s 作者:%-10s 出版社:%-20s 价格:%.2f",
                it->ISBN.c_str(), it->name.c_str(), it->author.c_str(),
                it->publisher.c_str(), it->price);

            outtextxy(50, y, line);
            y += 25;

            if (y > win_height - 40) 
            {
                outtextxy(50, y, "...(更多内容，按任意键返回)");
                break;
            }
        }
    }

    settextstyle(18, 0, "微软雅黑");
    settextcolor(RGB(200, 200, 200));
    outtextxy(300, win_height - 40, "按任意键返回主菜单");
    (void)_getch();
}

void ShowStatistics()
{
    cleardevice();

    settextstyle(24, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(50, 20, "统计信息");

    settextstyle(18, 0, "微软雅黑");
    settextcolor(RGB(220, 220, 220));
    int y = 70;
    char buf[128] = { 0 };

    sprintf_s(buf, "图书总数:%d本", TotalBooks(books));
    outtextxy(50, y, buf);
    y += 30;

    vector<string> presses;
    for (auto it = books.begin(); it != books.end(); it++)
    {
        bool repeated = 0;
        for (auto i = presses.begin(); i != presses.end(); i++) {
            if (*i == it->publisher)
            {
                repeated = 1;
                break;
            }
        }
        if (!repeated)
            presses.push_back(it->publisher);
    }
    sprintf_s(buf, "出版社数量:%d个", (int)presses.size());
    outtextxy(50, y, buf);
    y += 30;

    outtextxy(50, y, "各出版社图书数量:%d本");
    y += 25;
    for (const auto& p : presses)
    {
        sprintf_s(buf, "%s:%d本", p.c_str(), CountBooksByPublisher(books, p));
        outtextxy(50, y, buf);
        y += 22;
    }

    y += 10;
    outtextxy(50, y, "图书价格区间统计");
    y += 25;

    sprintf_s(buf, "0-20元:%d本", CountBooksByPriceRange(books, 0, 20));
    outtextxy(50, y, buf);
    y += 22;

    sprintf_s(buf, "20-40元:%d本", CountBooksByPriceRange(books, 20, 40)); 
    outtextxy(50, y, buf);
    y += 22;

    sprintf_s(buf, "40-60元:%d本", CountBooksByPriceRange(books, 40, 60));
    outtextxy(50, y, buf);
    y += 22;

    sprintf_s(buf, "60元以上:%d本", CountBooksByPriceRange(books, 60, 10000));
    outtextxy(50, y, buf);

    outtextxy(300, win_height - 40, "按任意键返回主菜单");
    (void)_getch();
}

bool IsInButton(int mx, int my, const Button& btn)
{
    if (mx >= btn.x && mx <= btn.x + btn.w && my >= btn.y && my <= btn.y + btn.h)
        return true;
    else
        return false;
}

string ConsoleInput(const string& prompt)
{
    HWND hwnd = GetHWnd();
    if (hwnd)
        ShowWindow(hwnd, SW_MINIMIZE);

    system("cls");

    printf("%s", prompt.c_str());

    char buf[256] = { 0 };
    fgets(buf, sizeof(buf), stdin);
    string result(buf);

    while (!result.empty() && (result.back() == '\n' || result.back() == '\r'))
    {
        result.pop_back();
    }
    if (hwnd)
        ShowWindow(hwnd, SW_RESTORE);
    return result;
}