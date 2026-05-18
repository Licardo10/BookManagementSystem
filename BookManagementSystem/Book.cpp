#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <io.h>
#include <fcntl.h>

vector<Book> books; // 图书列表

void AddBook(vector<Book> &books, const Book &newbook)
{
	books.push_back(newbook);
}

bool DeleteBookByISBN(vector<Book> &books, const wstring &ISBN)
{
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->ISBN == ISBN)
		{
			books.erase(it);
			return true;
		}
	}
	return false;
}

bool DeleteBookByName(vector<Book> &books, const wstring &name)
{
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->name == name)
		{
			books.erase(it);
			return true;
		}
	}
	return false;
}

Book *SearchBookByISBN(vector<Book> &books, const wstring &ISBN)
{
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->ISBN == ISBN)
		{
			return &(*it);
		}
	}
	return NULL;
}

Book *SearchBookByName(vector<Book> &books, const wstring &name)
{
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->name == name)
			return &(*it);
	}
	return NULL;
}

vector<Book> FuzzySearchByName(vector<Book> &books, const wstring &keyword)
{
	vector<Book> results; // 存储模糊匹配的结果
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->name.find(keyword) != wstring::npos) // wstring::find返回值为wstring::npos表示未找到
			results.push_back(*it);
	}
	return results;
}

vector<Book> FuzzySearchByPublisher(vector<Book> &books, const wstring &keyword)
{
	vector<Book> results;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->publisher.find(keyword) != wstring::npos)
			results.push_back(*it);
	}
	return results;
}

vector<Book> CombinedSearchByName(vector<Book> &books, const wstring &name)
{
	vector<Book> results;
	vector<wstring> keywords; // 存储分割后的关键字
	wstringstream ss(name);
	wstring token;
	while (getline(ss, token, L' '))
	{
		keywords.push_back(token);
	}
	for (auto it = books.begin(); it != books.end(); it++)
	{
		bool match = true;
		for (auto keyword = keywords.begin(); keyword != keywords.end(); keyword++)
		{
			if (it->name.find(*keyword) == wstring::npos)
			{
				match = false;
				break;
			}
		}
		if (match)
			results.push_back(*it);
	}
	return results;
}

int TotalBooks(const vector<Book> &books)
{
	return (int)books.size();
}

int CountBooksByPublisher(const vector<Book> &books, const wstring &publisher)
{
	int count = 0;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->publisher == publisher)
			count++;
	}
	return count;
}

int CountBooksByPriceRange(const vector<Book> &books, double minPrice, double maxPrice)
{
	int count = 0;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->price >= minPrice && it->price <= maxPrice)
			count++;
	}
	return count;
}

vector<Book> GetAllBooks(const vector<Book> &books)
{
	return books;
}

bool LoadDataFromFile(vector<Book> &books, const wstring &filename)
{
	FILE *fp = _wfopen(filename.c_str(), L"r, ccs=UTF-8");
	if (!fp)
		return false;

	books.clear(); // 先清空原有数据

	wchar_t line[1024];

	while (fgetws(line, sizeof(line) / sizeof(wchar_t), fp))
	{
		if (line[0] == L'\n' || line[0] == L'\0' || line[0] == L'\r') // 去掉末尾的换行符
			continue;

		size_t len = wcslen(line);
		while (len > 0 && (line[len - 1] == L'\n' || line[len - 1] == L'\r'))
			line[--len] = L'\0';

		Book b;

		wchar_t ISBN[50] = {0}, name[50] = {0}, author[50] = {0},
				publisher[50] = {0}, pubdate[20] = {0};

		int count = swscanf(line, L"%49[^|]|%49[^|]|%49[^|]|%49[^|]|%19[^|]|%lf|%d",
							ISBN, name, author, publisher, pubdate, &b.price, &b.state);

		if (count == 7) // 成功获取所有信息
		{
			b.ISBN = ISBN;
			b.name = name;
			b.author = author;
			b.publisher = publisher;
			b.pubdate = pubdate;
			books.push_back(b);
		}
	}
	fclose(fp);
	return true;
}

bool SaveDataToFile(vector<Book> &books, const wstring &filename)
{
	FILE *fp = _wfopen(filename.c_str(), L"w, ccs=UTF-8");
	if (!fp)
		return false;

	for (auto it = books.begin(); it != books.end(); it++)
	{
		fwprintf(fp, L"%s|%s|%s|%s|%s|%.2f|%d\n", it->ISBN.c_str(), it->name.c_str(),
				 it->author.c_str(), it->publisher.c_str(), it->pubdate.c_str(),
				 it->price, it->state);
	}
	fclose(fp);
	return true;
}

void BorrowByISBN(vector<Book> &books, const wstring &ISBN)
{
	wstring isbn = ISBN;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->ISBN == isbn && it->state == 0)
		{
			it->state = 1;
		}
	}
}

void ReturnByISBN(vector<Book> &books, const wstring &ISBN)
{
	wstring isbn = ISBN;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->ISBN == isbn && it->state == 1)
		{
			it->state = 0;
		}
	}
}