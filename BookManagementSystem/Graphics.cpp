#define _CRT_SECURE_NO_WARNINGS
#include "Graphics.h"
#include <conio.h>
#include <sstream>
#include <iomanip>
#include <windows.h>

Button mainButtons[] =
{
    { 100, 150, 280, 40, "1. 查找图书" },
    { 100, 220, 280, 40, "2. 修改图书" },
    { 100, 290, 280, 40, "3. 借阅图书" },
    { 100, 360, 280, 40, "4. 信息显示" },
    { 430, 350, 280, 40, "5. 退出系统" }
};

const int NumberOfmainButton = sizeof(mainButtons) / sizeof(mainButtons[0]);

Button searchButtons[] = {
    { 100, 150, 280, 40, "1. 按书名查找" },
    { 100, 200, 280, 40, "2. 按出版社查找" },
    { 100, 250, 280, 40, "3. 组合查询" },
    { 430, 150, 280, 40, "4. 查看所有图书" },
    { 430, 350, 280, 40, "5. 返回主菜单" }
};

const int NumberOfsearchButton = sizeof(searchButtons) / sizeof(searchButtons[0]);

Button modifyButtons[] = 
{
    { 100, 150, 280, 40, "1. 按ISBN修改" },
    { 100, 200, 280, 40, "2. 按书名修改" },
    { 100, 250, 280, 40, "3. 添加新书" },
    { 430, 150, 280, 40, "4. 删除图书(ISBN)" },
    { 430, 200, 280, 40, "5. 删除图书(书名)" },
    { 430, 350, 280, 40, "6. 返回主菜单" }
};

const int NumberOfmodifyButton = sizeof(modifyButtons) / sizeof(modifyButtons[0]);

Button borrowButtons[] = {
    { 100, 150, 280, 40, "1. 借出图书(按ISBN)" },
    { 100, 200, 280, 40, "2. 归还图书(按ISBN)" },
    { 430, 350, 280, 40, "3. 返回主菜单" }
};

const int NumberOfborrowButton = sizeof(borrowButtons) / sizeof(borrowButtons[0]);

Button statisticsButtons[] = {
    { 100, 150, 280, 40, "1. 查看所有图书" },
    { 100, 200, 280, 40, "2. 统计信息" },
    { 430, 350, 280, 40, "3. 返回主菜单" }
};

const int NumberOfstatisticsButton = sizeof(statisticsButtons) / sizeof(statisticsButtons[0]);

void DrawMainMenu()
{
	// 清空屏幕
    cleardevice();

    settextstyle(36, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(250, 50, "图书管理系统");

    settextstyle(18, 0,"微软雅黑");
    settextcolor(RGB(200, 200, 200));
    outtextxy(200, 100, "请点击下方按钮选择功能");

	// 绘制按钮
    for (int i = 0; i < NumberOfmainButton; i++)
    {
        Button btn = mainButtons[i];

        setfillcolor(RGB(60, 130, 200));
        setlinecolor(RGB(255, 255, 255));

        fillroundrect(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, 10, 10);
		setbkmode(TRANSPARENT);     // 设置背景透明，避免文本覆盖按钮的背景颜色

        settextstyle(18, 0, "微软雅黑");
        settextcolor(RGB(255, 255, 255));

        int tw = textwidth(btn.text.c_str());
        int th = textheight(btn.text.c_str());
        //字符居中
        outtextxy(btn.x + (btn.w - tw) / 2, btn.y + (btn.h - th) / 2, 
            btn.text.c_str());
    }
}

void DrawSearchMenu()
{
    cleardevice();

    settextstyle(28, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(250, 30, "查找图书");

    for (int i = 0; i < NumberOfsearchButton; i++)
    {
        Button btn = searchButtons[i];

        setfillcolor(RGB(60, 130, 200));
        setlinecolor(RGB(255, 255, 255));
        fillroundrect(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, 10, 10);

        setbkmode(TRANSPARENT);
        settextstyle(18, 0, "微软雅黑");
        settextcolor(RGB(255, 255, 255));

        int tw = textwidth(btn.text.c_str());
        int th = textheight(btn.text.c_str());
        outtextxy(btn.x + (btn.w - tw) / 2, btn.y + (btn.h - th) / 2,
            btn.text.c_str());
    }
}

void DrawModifyMenu()
{
    cleardevice();

    settextstyle(28, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(250, 30, "修改图书");

    for (int i = 0; i < NumberOfmodifyButton; i++)
    {
        Button btn = modifyButtons[i];

        setfillcolor(RGB(60, 130, 200));
        setlinecolor(RGB(255, 255, 255));
        fillroundrect(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, 10, 10);

        setbkmode(TRANSPARENT);
        settextstyle(18, 0, "微软雅黑");
        settextcolor(RGB(255, 255, 255));
        int tw = textwidth(btn.text.c_str());
        int th = textheight(btn.text.c_str());
        outtextxy(btn.x + (btn.w - tw) / 2, btn.y + (btn.h - th) / 2,
            btn.text.c_str());
    }
}

void DrawBorrowMenu()
{
    cleardevice();

    settextstyle(28, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(250, 30, "借阅图书");

    for (int i = 0; i < NumberOfborrowButton; i++)
    {
        Button btn = borrowButtons[i];

        setfillcolor(RGB(60, 130, 200));
        setlinecolor(RGB(255, 255, 255));
        fillroundrect(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, 10, 10);

        setbkmode(TRANSPARENT);
        settextstyle(18, 0, "微软雅黑");
        settextcolor(RGB(255, 255, 255));

        int tw = textwidth(btn.text.c_str());
        int th = textheight(btn.text.c_str());
        outtextxy(btn.x + (btn.w - tw) / 2, btn.y + (btn.h - th) / 2,
            btn.text.c_str());
    }
}

void DrawStatisticsMenu()
{
    cleardevice();

    settextstyle(28, 0, "微软雅黑");
    settextcolor(RGB(255, 255, 255));
    outtextxy(250, 30, "信息统计");

    for (int i = 0; i < NumberOfstatisticsButton; i++)
    {
        Button btn = statisticsButtons[i];

        setfillcolor(RGB(60, 130, 200));
        setlinecolor(RGB(255, 255, 255));
        fillroundrect(btn.x, btn.y, btn.x + btn.w, btn.y + btn.h, 10, 10);

        setbkmode(TRANSPARENT);
        settextstyle(18, 0, "微软雅黑");
        settextcolor(RGB(255, 255, 255));

        int tw = textwidth(btn.text.c_str());
        int th = textheight(btn.text.c_str());
        outtextxy(btn.x + (btn.w - tw) / 2, btn.y + (btn.h - th) / 2,
            btn.text.c_str());
    }
}

void PrintResult(const string text, const vector<Book>& list)
{
    const int Ystart = 70;          // 第一行起始Y值
    const int lineHeight = 25;      
    const int maxLines = 20;        // 每屏最多显示的行数
    int total = (int)list.size();

	if (total == 0)     // 列表为空
    {
        cleardevice();

        settextstyle(24, 0, "微软雅黑");
        settextcolor(RGB(255, 255, 255));
        outtextxy(50, 20, text.c_str());

        settextstyle(16, 0, "微软雅黑");
        settextcolor(RGB(220, 220, 220));
        outtextxy(50, Ystart, "没有找到图书");

        settextstyle(18, 0, "微软雅黑");
        outtextxy(300, win_height - 40, "按任意键返回");

        (void)_getch();
        return;
    }

    int currentIdx = 0;  // 当前页中第一本图书在 list 中的下标
    while (currentIdx < total)
    {
        cleardevice();

        settextstyle(24, 0, "微软雅黑");
        settextcolor(RGB(255, 255, 255));

        // 显示标题和页码
        char title[128];
        sprintf_s(title, "%s  (%d/%d)", text.c_str(),
            currentIdx / maxLines + 1, (total - 1) / maxLines + 1);
        outtextxy(50, 20, title);

        settextstyle(16, 0, "微软雅黑");
        settextcolor(RGB(220, 220, 220));

        int y = Ystart, count = 0;
		// 从 list 中当前页的第一本图书开始，依次显示每本图书的信息，直到达到 maxLines 或者显示完所有图书
        for (int i = currentIdx; i < total && count < maxLines; i++, count++)
        {
            char line[256];
            sprintf_s(line, "ISBN:%-20s 书名:%-30s 作者:%-10s 出版社:%-20s 价格:%.2f",
                list[i].ISBN.c_str(), list[i].name.c_str(), list[i].author.c_str(),
                list[i].publisher.c_str(), list[i].price);
            outtextxy(50, y, line);
            y += lineHeight;
        }

        settextstyle(18, 0, "微软雅黑");
        settextcolor(RGB(200, 200, 200));

        // 判断是否还有下一页
        if (currentIdx + count < total)
        {
            outtextxy(200, win_height - 40, "按任意键继续，按 ESC 返回");
            int key = _getch();
            if (key == 27)  // ESC
                return;
        }
        else
        {
            outtextxy(300, win_height - 40, "已显示完毕，按任意键返回主菜单");
            (void)_getch();
            return;
        }

        currentIdx += count;  // 下一页
    }
    
    settextstyle(18, 0, "微软雅黑");
    settextcolor(RGB(200, 200, 200));
    outtextxy(300, win_height - 40, "按任意键返回主菜单");

    (void)_getch();
}

void PrintStatistics()
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

	// 统计所有出版社
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

    outtextxy(50, y, "各出版社图书数量:");
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

string InputByConsole(const string& prompt)
{
    HWND hwnd = GetHWnd();
    if (hwnd)
		ShowWindow(hwnd, SW_MINIMIZE);      // 最小化窗口，显示控制台

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
        ShowWindow(hwnd, SW_RESTORE);      // 恢复窗口
    return result;
}