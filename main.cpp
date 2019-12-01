#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <conio.h>
#include "Books.h"
#include "DataBase.h"
#include<algorithm>
#include<bits/stdc++.h>


using namespace std;
extern int n;
int main()
{
    cout<<setw(20)<<"Welcome to our Library"<<endl;
    cout<<setw(20)<<"Menu"<<endl;
    string file_name;
    cout<<"Put the name of file which you want to include\n (type file name without format type) : ";
    getline(cin, file_name);
    DataBase Library(file_name);
    Library.importData();

    while(1)
    {
        cout<<"\t1-Add     \t2-View      \t3- Borrow"
            <<"\n\t4-Return \t5-Delete"
            <<"\t6-Search \n\t7-Sort     \t8-Export Data \tq-Quit"<<endl;
        char choice;
        cin>>choice;
        bool flag=false;
        switch(choice)
        {
        case '1':
            flag=Library.addBook();
            if(flag)
                cout<<"Successful!"<<endl;
            break;
        case '2':
            cout<<Library.getData().size()<<endl;
            Library.printData();
            break;
        case '3':
            Library.borrowBook();
            break;
        case '4':
            Library.returnBook();
            break;
        case '5':
            Library.deleteBook();
            break;
        case '6':
            Library.searchBook();
            break;
        case '7':
                Library.sortData();
                break;
        case '8':
                Library.exportData(Library.getData());
                break;
        case 'q':
            cout<<"Library is closed";
            return 0;
        default:
            cout<<"You put a wrong character, try again"<<endl;
            break;
        }
    }
    return 0;
}
