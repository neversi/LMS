#pragma once
#include <vector>
#include<string>
#include "Books.h"
using namespace std;
class DataBase {
private:
	vector<Books*> library;
	string file_name;
public:
	DataBase(string);
    vector<Books*>& getData();
	vector<string> split(string);
	bool borrowBook();//ready
	bool returnBook();//ready
	//bool comparatorAsc(Books**, Books**);
	//bool comparatorDes(Books**, Books**);
	void printData();//tested
	void importData();//ready
	void exportData(vector<Books*>&);//ready
	void searchBook();//ready
	bool addBook();//ready
	bool sortData();//NOT
	void deleteBook();
	void modifyBook(vector<Books*>::iterator);

};

