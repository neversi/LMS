#pragma once
#include<string>
using namespace std;
class Books {
private:
	string id, name, title, year, ISBN, publisher, LLC, stock;
public:
	Books(string, string, string, string, string, string, string, string);
	void setName(string);
	void setTitle(string);
	void setYear(string);
	void setISBN(string);
	void setPublisher(string);
	void setLLC(string);
	void setStock(string);
	void infBook();
	string returnType(int n);
	string getName();
	string getTitle();
	string getYear();
	string getISBN();
	string getPublisher();
	string getLLC();
	string getStock();

};
