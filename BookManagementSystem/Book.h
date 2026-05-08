#pragma once
#include <string>
#include <vector>
using namespace std;

struct Book
{
	string ISBN;		// 编号
	string name;		// 名称
	string author;		// 作者
	string publisher;	// 出版社
	string pubdate;		// 出版日期
	double price = 0.0;		// 价格
	int state = 0;			// 借阅状态，0表示可借，1表示已借出
};

extern vector<Book> books;	// 图书列表

void AddBook(vector<Book>& books, const Book& newbook);								// 添加图书
bool DeleteBookByISBN(vector<Book>& books, const string& ISBN);						// 根据ISBN删除图书
bool DeleteBookByName(vector<Book>& books, const string& name);						// 根据名称删除图书

Book* SearchBookByISBN(vector<Book>& books, const string& ISBN);					// 根据ISBN查找图书
Book* SearchBookByName(vector<Book>& books, const string& name);					//根据名称查找图书
vector<Book> FuzzySearchByName(vector<Book>& books, const string& keyword);			//根据名称模糊查找
vector<Book> FuzzySearchByPublisher(vector<Book>& books, const string& keyword);	//根据出版社模糊查找
vector<Book> CombinedSearchByName(vector<Book>& books, const string& name);			//根据名称组合查询

int TotalBooks(const vector<Book>& books);												// 获取图书总数
int CountBooksByPublisher(const vector<Book>& books, const string& publisher);			// 统计某出版社的图书数量
int CountBooksByPriceRange(const vector<Book>& books, double minPrice, double maxPrice);// 统计某价格范围内的图书数量
vector<Book> GetAllBooks(const vector<Book>& books);									// 获取所有图书列表

bool LoadDataFromFile(vector<Book>& books, const string& filename);		//从文件中加载图书
bool SaveDataToFile(vector<Book>& books, const string& filename);		//将图书存储到文件中

void BorrowByISBN(vector<Book>& books, const string& ISBN);
void ReturnByISBN(vector<Book>& books, const string& ISBN);