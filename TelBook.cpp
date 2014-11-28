// файл реализации класса TelBook.cpp
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "TelBook.h"
using namespace std;
TelBook::TelBook(const vector<vector <string>>& book2)
{
	//setBook(book2);
	book=book2;
}
//void TelBook::setBook (const vector <vector<string>>& book2)
//{
//	book=book2;		
//	}

vector<vector<string>> TelBook::delit(string delname)// удаление абонента со всеми номерами
{
	for (int i=0; i<book.size(); i++) 
	{
		if (book[i][0]==delname)
		{
			book.erase(book.begin()+i);
			cout<<"Выполнено"<<endl;
			return book;
		}
	}
	message();
	return book;
}
void TelBook::message()
{
	cout<<"Таких данных не существует"<<endl;
}
vector<string> TelBook::poiskpoimeni(string poiskname) // поиск абонента по имени
{
	vector <string> VecVivod;
	for (int i=0; i<book.size(); i++)
	{
		if (book[i][0]==poiskname)
		{
			for (int j=1; j<book[i].size(); j++)
			{					
				VecVivod.push_back(book[i][j]);
			}
			return VecVivod;
		}

	}
	message();
	return VecVivod;
}
string TelBook::poiskpotel(string poisktel) // поиск абонента по телефону
{
	for (int i=0; i<book.size(); i++)
	{
		for (int j=1; j<book[i].size(); j++)
		{
			if (book[i][j]==poisktel) 
			{
				return(book[i][0]);

			}
		}
	}

	return ("Такого абонента не существует");
}
vector<vector <string>> TelBook::poiskpobokve(string poiskbokva) // начинающиеся с определенных букв 
{ int flag=0;
vector<vector <string>> VecVivod;
vector<string> book1;
for (int i=0; i<book.size();i++)
{
	size_t pos=book[i][0].find(poiskbokva);
	if(pos==0){
		flag=1;
		for (int j=0; j<book[i].size();j++)
		{
			book1.push_back(book[i][j]);
		}
		VecVivod.push_back(book1);
		book1.clear();
		book1.shrink_to_fit();
	}

}
if (flag==0) message();
return (VecVivod);
}
TelBook::~TelBook()
{
}
vector<vector <string>> TelBook::dobavlenie( vector <string>& book2) // добавление абонента с несколькими номерами
{
	book.push_back(book2);
	return book;
	
}
vector<vector <string>> TelBook::delittel(string name, string tel)// удаление 1 телефона из контакта,
	                                                              //у которого телефонов много
{
	for  (int i=0; i<book.size();i++)
	{
		if (book[i][0]==name)
		{
			for (int j=1; j<book[i].size(); j++)
			{

				if (book[i][j]==tel) 
				{			
					book[i].erase(book[i].begin()+j);
					return book;

				}
			}

		}
	}
	message();
	return book;
}
vector<vector <string>> TelBook::OdinNomDobavlenie (string name, string tel) // добавление пары абонент-телефон
{
	vector <string> book1;
	book1.push_back(name);			
	book1.push_back(tel);
	book.push_back(book1);
	return book;
}
