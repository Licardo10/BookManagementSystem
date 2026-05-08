#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include <cstdio>
#include <cstring> 
#include <cstdlib>
#include <sstream>

vector<Book> books;	// 图书列表

void AddBook(vector<Book>& books, const Book& newbook)
{
	books.push_back(newbook);
}

bool DeleteBookByISBN(vector<Book>& books, const string& ISBN)
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

bool DeleteBookByName(vector<Book>& books, const string& name)
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

Book* SearchBookByISBN(vector<Book>& books, const string& ISBN)
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

Book* SearchBookByName(vector<Book>& books, const string& name)
{
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->name == name)
			return &(*it);
	}
	return NULL;
}

vector<Book> FuzzySearchByName(vector<Book>& books, const string& keyword)
{
	vector<Book> results;	// 存储模糊匹配的结果
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->name.find(keyword) != string::npos)	// string::find返回值为string::npos表示未找到
			results.push_back(*it);
	}
	return results;
}

vector<Book> FuzzySearchByPublisher(vector<Book>& books, const string& keyword)
{
	vector<Book> results;	
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->publisher.find(keyword) != string::npos)
			results.push_back(*it);
	}
	return results;
}

vector<Book> CombinedSearchByName(vector<Book>& books, const string& name)
{
	vector<Book> results;
	vector<string> keywords;	// 存储分割后的关键字
	stringstream ss(name);
	string token;
	while (getline(ss, token, ' '))
	{
		keywords.push_back(token);
	}
	for (auto it = books.begin(); it != books.end(); it++)
	{
		bool match = true;
		for (auto keyword = keywords.begin(); keyword != keywords.end(); keyword++)
		{
			if (it->name.find(*keyword) == string::npos)
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

int TotalBooks(const vector<Book>& books)
{
	return (int)books.size();
}

int CountBooksByPublisher(const vector<Book>& books, const string& publisher)
{
	int count = 0;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->publisher == publisher)
			count++;
	}
	return count;
}

int CountBooksByPriceRange(const vector<Book>& books, double minPrice, double maxPrice)
{
	int count = 0;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->price >= minPrice && it->price <= maxPrice)
			count++;
	}
	return count;
}

vector<Book> GetAllBooks(const vector<Book>& books)
{
	return books;
}

bool LoadDataFromFile(vector<Book>& books, const string& filename)
{
	FILE* fp = fopen(filename.c_str(), "r");
	if (!fp)
		return false;

	books.clear();		// 先清空原有数据

	char line[1024];
	while (fgets(line, sizeof(line), fp))
	{
		if (line[0] == '\n' || line[0] == '\0' || line[0] == '\r')
			continue;
		Book b;

		char ISBN[50] = { 0 }, name[50] = { 0 }, author[50] = { 0 },
			publisher[50] = { 0 }, pubdate[20] = { 0 };

		int count = sscanf(line, "%49[^|]|%49[^|]|%49[^|]|%49[^|]|%19[^|]|%lf|%d",
			ISBN, name, author, publisher, pubdate, &b.price, &b.state);

		if (count == 7)		// 成功获取所有信息
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

bool SaveDataToFile(vector<Book>& books, const string& filename)
{
	FILE* fp = fopen(filename.c_str(), "w");
	if (!fp)
		return false;

	for (auto it = books.begin(); it != books.end(); it++)
	{
		fprintf(fp, "%s|%s|%s|%s|%s|%.2f|%d\n", it->ISBN.c_str(), it->name.c_str(), 
			it->author.c_str(), it->publisher.c_str(), it->pubdate.c_str(), 
			it->price, it->state);
	}
	fclose(fp);
	return true;
}

void BorrowByISBN(vector<Book>& books, const string& ISBN)
{
	string isbn = ISBN;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->ISBN == isbn && it->state==0)
		{
			it->state = 1;
		}
	}
}

void ReturnByISBN(vector<Book>& books, const string& ISBN)
{
	string isbn = ISBN;
	for (auto it = books.begin(); it != books.end(); it++)
	{
		if (it->ISBN == isbn && it->state == 1)
		{
			it->state = 0;
		}
	}
}