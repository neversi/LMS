
#include <iostream>
#include <string>
#include <cstdlib>
#include "Books.h"
using namespace std;

Books::Books(string id_, string name_, string title_, string year_, string ISBN_, string publisher_, string LLC_, string stock_)
            : id(id_), name(name_), title(title_),year(year_),ISBN(ISBN_), publisher(publisher_), LLC(LLC_), stock(stock_) {}

void Books:: setName(string name)
{
    this-> name = name;
}
void Books::setTitle(string title)
{
    this->title=title;
}
void Books:: setYear(string year)
{
    this->year=year;
}
void Books:: setISBN(string ISBN)
{
    this->ISBN=ISBN;
}
void Books ::setPublisher(string publisher)
{
    this->publisher= publisher;
}
void Books::setLLC(string LLC)
{
    this->LLC= LLC;
}
void Books::setStock(string stock)
{
    this->stock=stock;
}
string Books::getName()
{
    return name;
}
string Books::getTitle()
{
    return title;
}
string Books::getYear()
{
    return year;
}
string Books::getISBN()
{
    return ISBN;
}
string Books::getPublisher()
{
    return publisher;
}
string Books::getLLC()
{
    return LLC;
}
string Books::getStock()
{
    return stock;
}

void Books::infBook()
{
    cout<<"Author: "<<this->getName()<<endl<<"Title: "<<this->getTitle()<<endl<<"Year: "<<getYear()<<endl<<"ISBN: "
    <<getISBN()<<endl<<"Publisher: "<<getPublisher()<<endl<<"LLC: "<<getLLC()<<endl<<"Only "<<this->getStock()<<" books are available"<<endl;
}
string Books::returnType(int n)
{
    switch (n){
case 1:
    return getName();
case 2:
    return getTitle();
case 3:
    return getYear();
case 4:
    return getISBN();
case 5:
    return getPublisher();
case 6:
    return getLLC();
default:
    cout<<"You did not choose one of them"<<endl;
    }
    return "";
}
