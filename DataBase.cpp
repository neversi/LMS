//Abdrs code, deeeeeeeeee
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<cstdlib>
#include<bits/stdc++.h>
#include "DataBase.h"
#include<array>


DataBase::DataBase(string file_name_):file_name(file_name_) {}

void DataBase::importData()
{
	string readLine;
	vector<string> line;
	vector<string> details;
	ifstream file;
	string csvFile=file_name+".csv";
	file.open(csvFile, ios::in);
	if (!file.is_open())
	{
		cerr << "Something wrong with your file" << endl;
	}

	while (getline(file, readLine, '\n'))
		line.push_back(readLine);

	for (auto i : line)
	{
	    if(i==line[0]) continue;
		details.clear();
		details=split(i);
		library.push_back(new(nothrow) Books(details[0], details[1], details[2], details[3], details[4], details[5], details[6], details[7]));
	}

	for (auto i = library.begin(); i != library.end(); i++)
	{
		string name = (*i)->getName();
		if (name == "")
		{
			auto n = i - 1;

			name = (*n)->getName();
			(*i)->setName(name);
		}
	}
	file.close();
}

vector<string> DataBase::split(string line)
{
	vector<string> elements;
	elements.clear();
	string parts = "";
	for (int i = 0; i <= line.size(); i++)
	{
		if (line[i] != ';')
			parts += line[i];
		else
		{
			elements.push_back(parts);
			parts = "";
		}
	}
	elements.push_back(parts);
	return elements;
}
void DataBase::searchBook()
{
	vector<string> choices;
	vector<string> lineChecker;
	vector<int> numbers;
	string choice, checker="", word = "", finalChecker = "";
	cout << "By which features do you want to search (if you want to search only"<<endl
	<<"by one feature enter the one, otherwise enter several features by space"<<endl
	<<" (please write every feature with space, it is a feature of our program): ";
    cin.get();
	getline(cin, choice);
	string dummy="";
	for (int i = 0; i < choice.size(); i++)
	{
		if (choice[i] != ' '){
			dummy += choice[i];
		}
		else {
			choices.push_back(dummy);
			dummy = "";
			//if(choices[choice.seize])
		}
	}


	int n = choices.size();

	for(int i=0; i<n;i++)
    {
        string word="";
        std::for_each(choices[i].begin(), choices[i].end(), [](char& c) {c = ::tolower(c);});
        if(choices[i]=="author")
        {
            cout<<"Author: ";

            getline(cin, word);
            numbers.push_back(1);
        }
        else if(choices[i]=="title")
        {
            cout<<"Title: ";

            getline(cin, word);
            numbers.push_back(2);
        }
        else if(choices[i]=="year"){
            cout<<"Year: ";

            getline(cin, word);
            numbers.push_back(3);
        }
        else if(choices[i]=="isbn"){
            cout<<"ISBN: ";

            getline(cin, word);
            numbers.push_back(4);
        }
        else if(choices[i]=="publisher"){
        cout<<"Publisher: ";
            getline(cin, word);
            numbers.push_back(5);
            }
        else if(choices[i]=="llc"){
        cout<<"LLC: ";
            getline(cin, word);
            numbers.push_back(6);
    }
        else
            cout<<"You have written incorrect feature: "<<choices[i];
        checker+=word;
    }
	std::for_each(checker.begin(),checker.end(), [](char& c) {c = ::tolower(c); });
    for (int i = 0; i < checker.size(); i++)
		if (checker[i] != ' ')
			finalChecker += checker[i];
    cout<<endl<<finalChecker<<endl;


	for (auto t=library.begin(); t!=library.end();t++)
	{
		string finalLine = "";
        string checkerFinal="";
		for (auto n : numbers)
			checkerFinal+= (*t)->returnType(n);
    std::for_each(checkerFinal.begin(), checkerFinal.end(), [](char& c) {c = ::tolower(c); });
		for (int i = 0; i < checkerFinal.size(); i++)
			if (checkerFinal[i] != ' ')
				finalLine += checkerFinal[i];

		if (finalLine == finalChecker)
		{
			(*t)->infBook();
			cout<<"Do you want to modify it?(y/n): ";
			char ans;
			cin>>ans;
			if(ans=='y')
                {
                    modifyBook(t);
                }
            choices.clear();
            lineChecker.clear();
            numbers.clear();
			break;

		}
		else{
			finalLine = "";
		}
	}
}

void DataBase::printData()
{
    for( auto i: library)
    {
        i->infBook();
        cout<<"-----------------------\n";

    }
}
void DataBase::exportData(vector<Books*> &library)
{
    //opening the file
    ofstream exportFile("lmsdb.csv", ios::out);

    //checking if it has opened

    //header line
    exportFile << "#"<< ";";
    exportFile<<"Author"<< ";";
    exportFile<<"Title"<< ";";
    exportFile<<"Year"<< ";";
    exportFile<<"ISBN"<< ";";
    exportFile<<"Publisher"<< ";";
    exportFile<<"LLC"<< ";";
    exportFile<<"Stock";
    exportFile<<endl;
    int n=0;
    string b;
    //saving books line by line
    for (int i = 0; i < library.size(); i++)
    {
        n++;
        b=to_string(n);
        exportFile << b;
        exportFile << ";" << library.at(i)->getName() << ";";
        exportFile << library.at(i)->getTitle() << ";";
        exportFile << library.at(i)->getYear()<< ";";
        exportFile << library.at(i)->getISBN()<< ";";
        exportFile << library.at(i)->getPublisher() << ";";
        exportFile << library.at(i)->getLLC() << ";";
        exportFile << library.at(i)->getStock();

        if (i != library.size() - 1)
        {
            exportFile << endl;
        }
    }
    exportFile.close();
}

bool DataBase:: borrowBook()
{
    string isbn;
    cout<<"Enter ISBN to borrow a book: ";
    cin>>isbn;
    for (auto i: library)
    {
        if(i->getISBN()==isbn)
        {
            cout<<"There is only: "<< i->getStock();
            int amountBook=stoi(i->getStock());
            if(amountBook>0)
            {

                amountBook--;
                i->setStock(to_string(amountBook));
                cout<<endl<<"Book is borrowed";
                return true;
            }
            else
                {
                    cout<<endl<<"Last book has been borrowed yesterday, sorry"<<endl;
                    return false;
                }
        }
    }
    return false;
}

bool DataBase::returnBook()//parametr is bool
{
    string isbn;
    bool check=false;
    cout<<"Enter ISBN to return a book: ";
    cin>>isbn;
     for (auto i: library)
    {
        if(i->getISBN()==isbn)
        {
            cout<<"Now is "<<i->getStock();
            bool check=true;
            int amountBook=stoi(i->getStock());
            amountBook++;
            i->setStock(to_string(amountBook));
            cout<<"Book is returned"<<endl;
        }
    }
    return check;
}

bool DataBase::addBook()
{
    vector<string> details;
    details.push_back("new");
    string world;
    cout<<"Write information about book";
    cout<<endl<<"Enter the author name of a book: ";
    cin.get();
    getline(cin, world);
    details.push_back(world);
    cout<<endl<<"Enter the title of a book: ";

    getline(cin,world);
    details.push_back(world);
    cout<<endl<<"Enter the year of a book: ";
    //cin.get();
    getline(cin,world);
    details.push_back(world);
    cout<<endl<<"Enter the ISBN number of a book: ";
    //cin.get();
    getline(cin,world);
    details.push_back(world);
    cout<<endl<<"Enter the publisher of a book: ";
    //cin.get();
    getline(cin,world);
    details.push_back(world);
    cout<<endl<<"Enter LLC number of a book: ";
    //cin.get();
    getline(cin,world);
    details.push_back(world);
    cout<<endl<<"How many certain books do you have: ";
    //cin.get();
    getline(cin,world);
    details.push_back(world);
    world="";
    vector<Books*> p;
    int n=sizeof(p)/sizeof(p[0]);
    for(auto i=library.begin(); i!=library.end();i++)
    {
         if((*i)->getName()=="")
         {
             (*i)->getName()=" ";
             library.push_back(new(nothrow) Books(details[0],details[1],details[2],details[3],details[4],details[5],details[6],details[7]));
             details.clear();
             return true;
         }

            else if((*i)->getName() > details[1])
            {
                library.insert(i, new(nothrow) Books(details[0],details[1],details[2],details[3],details[4],details[5],details[6],details[7]));
                details.clear();
                p.clear();
                return true;
            }else{

            }
}

    p.clear();
    return true;
}
void DataBase::deleteBook()
{
    cout<<"Enter ISBN number to delete a book: ";
    string isbn;
    cin>>isbn;
    for(auto i=library.begin();i!=library.end();i++){
                    if(isbn==(*i)->getISBN()){
                        library.erase(i);
                        cout<<"Book was successfully deleted"<<endl;
                        break;
                    }
}
cout<<"Something wrong with ISBN"<<endl;

}

void DataBase::modifyBook(vector<Books*>::iterator i)
{
    string identifier;
    vector<string> parametrs;
    cout<<"What features do you want to modify: ";
    cin.get();
    getline(cin, identifier);
    string dummy="";
    for(int i=0;i<identifier.size();i++)
    {
        if(identifier[i]!=' ')
        {
            dummy+=identifier[i];
        }
        else{
            parametrs.push_back(dummy);
            dummy="";
        }
    }

    for(auto v=parametrs.begin();v!=parametrs.end();v++)
    {
            string subs="";
        if(*v=="Author")
           {
               cout<<"New Author: ";
               getline(cin, subs);
                (*i)->setName(subs);
           }
           if(*v=="Title")
           {
               cout<<"New Title: ";
               getline(cin, subs);
                (*i)->setTitle(subs);
           }
           if(*v=="Year")
           {
               cout<<"New Year: ";
               getline(cin, subs);
                (*i)->setYear(subs);
           }
           if(*v=="ISBN")
           {
               cout<<"New ISBN: ";
               getline(cin, subs);
                (*i)->setISBN(subs);
           }
           if(*v=="Publisher")
           {
               cout<<"New Publisher: ";
               getline(cin, subs);
                (*i)->setPublisher(subs);
           }
           if(*v=="LLC")
           {
               cout<<"New LLC: ";
               getline(cin, subs);
                (*i)->setLLC(subs);
           }
           subs="";
    }


}

bool  DataBase::sortData()
{
    cout<<"By which feature do you want to sort?: ";
    string feature, order;
    cin>>feature;
    cout<<endl<<"Ascending or descending order?(asc, des): ";
    cin>>order;

    if(order=="asc")
    {
    if(feature=="Author") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(1))>(b->returnType(1));});
    else if(feature=="Title") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(2))>(b->returnType(2));});
    else if(feature=="Year") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(3))>(b->returnType(3));});
    else if(feature=="ISBN") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(4))>(b->returnType(4));});
    else if(feature=="Publisher") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(5))>(b->returnType(5));});
    else if(feature=="LLC") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(6))>(b->returnType(6));});
    else
    {cout<<"You choose wrong feature"<<endl;
        return false;}

    return true;
}
else if(order=="des")
{
    if(feature=="Author") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(1))<(b->returnType(1));});
    else if(feature=="Title") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(2))<(b->returnType(2));});
    else if(feature=="Year") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(3))<(b->returnType(3));});
    else if(feature=="ISBN") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(4))<(b->returnType(4));});
    else if(feature=="Publisher") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(5))<(b->returnType(5));});
    else if(feature=="LLC") std::sort(library.begin(), library.end(),[](Books* a, Books* b){return (a->returnType(6))<(b->returnType(6));});
    else
    {cout<<"You choose wrong feature"<<endl;
        return false;}
        return true;
}
else
{
    cout<<endl<<"Wrong order type, try again?(y/n)";
    char ans;
    cin>>ans;
    if(ans=='y')
    {
        sortData();
    }
    else
        return false;
}
}
 vector<Books*>& DataBase::getData()
 {
     return library;
 }
