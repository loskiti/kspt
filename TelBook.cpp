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


bool TelBook::delit(string delname)// удаление абонента со всеми номерами
{
	for (int i=0; i<book.size(); i++) 
	{
		if (book[i][0]==delname)
		{
			book.erase(book.begin()+i);
			return true;
		}

	}
	return false;
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
vector <string> TelBook::poiskpobokve(string poiskbokva) // начинающиеся с определенных букв 
{ 
	vector<string> VecVivod;
	for (int i=0; i<book.size();i++)
	{
		size_t pos=book[i][0].find(poiskbokva);
		if(pos==0)
			VecVivod.push_back(book[i][0]);
	}
	return (VecVivod);
}
TelBook::~TelBook()
{
}
bool TelBook::dobavlenie( vector <string>& book2) // добавление абонента с несколькими номерами
{
	book.push_back(book2);
	return true;

}
bool TelBook::delittel(string name, string tel)// удаление 1 телефона из контакта,
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
					return true;

				}
			}

		}
	}

	return false;
}
bool TelBook::OdinNomDobavlenie (string name, string tel) // добавление пары абонент-телефон
{
	vector <string> book1;
	book1.push_back(name);			
	book1.push_back(tel);
	book.push_back(book1);
	return true;
}
void TelBook::vivod() // обновление книги
{
	ofstream outfile("in.txt",ios::out);
	for (int i=0; i<book.size(); i++)

	{
		outfile<<book[i][0]<<" ";
		for (int j=1;j<book[i].size(); j++)
		{

			if (j>1)
				outfile<<setw(book[i][0].size()+book[i][j].size()+1)<<book[i][j]<<endl;
			else outfile<< book[i][j]<<endl;


		}
	}
	outfile.close();
}
void TelBook::vvod()
{
	fstream F; 
	F.open("in.txt", ios::in);
	char simvol;
	vector <string> book1;
	vector<char> stroka;
	string tel;
	string name;
	while (!F.eof())// Чтение строки и занесение ее в таблицу
	{		
		F.get(simvol);

		if (simvol!=10)
		{
			stroka.push_back(simvol); 
		}
		else 
		{
			if (stroka.size()>0)
			{
				massiv(stroka, name, tel);
				if (name.size()>1)
				{
					if (book1.size()>0)
						book.push_back(book1);
					book1.clear();
					book1.shrink_to_fit();
					book1.push_back(name);
					book1.push_back(tel);

				}
				else 
				{book1.push_back(tel);
				}
				stroka.clear(); 
				stroka. shrink_to_fit();
				name.clear();
				tel.clear();
			}
		}
	}
	if (book1.size()>0)
		book.push_back(book1);
	book1.clear();
	book1.shrink_to_fit();
	stroka. shrink_to_fit();
	F.close();
}

void TelBook::massiv (const vector <char>& stroka, string &name, string &tel) // конструктор таблицы
{
	int flag =0;
	for (int i=stroka.size()-1; i>0; i--) // поиск последнего пробела - отделение ФИО и номера
	{
		if (stroka[i]==' ')
		{
			flag=i;
			break;
		}
	}

	for (int i=0;i<=stroka.size()-1 ; i++) 
	{ 
		if ((i<flag) )
		{
			if (stroka[i]!=' ')
				name.push_back(stroka[i]);
			else 
				if  (i>0)
					if (stroka[i-1]!=' ')
						name.push_back(stroka[i]);
		}

		else 
			if (isdigit(stroka[i])!=0 ||stroka[i]=='+' || stroka[i]=='*' || stroka[i]=='#' || stroka[i]=='p' || stroka[i]!=' ') 
				tel.push_back(stroka[i]); 
	}
}
