// Выполнила Лосева Катя 13501/4
//Реализовать класс ТЕЛЕФОННАЯ КНИГА. Класс должен быть предназначен для хранения номеров телефонов различных людей. 
//Не должно быть ограничений на количество людей в телефонной книге и должна быть возможность сохранить 
//несколько (не более 10) телефонов для одного человека. Телефон задаётся последовательностью символов, 
//среди которых могут встречаться цифры, +, *, #, p, остальные символы считать ошибкой. 
//Человек задаётся строкой, содержащей фамилию на русском или английском языке, 
//опционально можно добавлять (через пробел) имя и отчество.
//Требуемые методы: конструктор по умолчанию (создаёт пустую таблицу), деструктор, 
//вывод телефонной книги в текстовый файл и ввод телефонной книги из того же текстового файла (т.е. сохранение и загрузка),
//добавление и удаление пары «человек—телефон», удаление человека из телефонной книги (со всеми телефонами), 
//получение списка телефонов заданного человека, получение человека, соответствующего заданному телефону, 
//получение списка людей, фамилия которых начинается на заданную подстроку.
// Написать главную функцию, тестирующую данный класс путём создания его объектов и проведения над ними различных операций.
// class.cpp: определяет точку входа для консольного приложения.

// class.cpp: определяет точку входа для консольного приложения.
#include <Windows.h>
#include <ostream>
#include <algorithm>
#include "TelBook.h"
#include <iostream>
#include < string.h > 
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;
void VivodBukvi(vector<vector<string>>& book) // вывод поиска по буквам
		{
			
			for (int i=0; i<book.size(); i++)

			{
				cout<<book[i][0]<<" ";
				for (int j=1;j<book[i].size(); j++)
				{
					
					if (j>1)
					cout<<setw(book[i][0].size()+book[i][j].size()+1)<<book[i][j]<<endl;
					else cout<< book[i][j]<<endl;


				}
			}
			
}
void vivod(vector<vector<string>>& book) // обновление книги
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
void VivodImeni(vector<string>&book) // вывод данных по поиску по имени
{
		for (int i=0; i<book.size(); i++)

			{
				cout<<book[i]<<endl;
							}
			

}
void massiv (const vector <char>& stroka, string &name, string &tel) // конструктор таблицы
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

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	fstream F; 
	F.open("in.txt", ios::in);
	vector<char> stroka;
	vector<vector <string>> book; // таблица номеров
	vector <string> book1;
	string tel;
	string name;
	char simvol;
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
	TelBook objTelbook(book);
	stroka. shrink_to_fit();
F.close();
	cout<<"Вас приветствует ТЕЛЕФОННАЯ КНИГА"<<endl<<"Для продолжения работы выберите 1 из пунктов меню (введите цифру функции)"<<endl;
	cout<<"1 - удаления контакта"<<endl<<"2 - добавления контата"<<endl<<"3 - поиска абонента по имени"<<endl<<"4 - поиска по номеру"<<endl<<"5 - поиска абонентов по первым буквам имени"<<endl<<"6 - удаление телефона из контакта"<<endl;
	int zadacha=0;
	cin>>zadacha;
	string per;
	while(zadacha<7 && zadacha>0) //меню
	{
	switch (zadacha)
	{
	case 1:  //удаление человека с номерами 
		{
			cout<<"Вы зашли в функцию удаления контакта. Введите его имя:"<<endl;
			getline(std::cin,per);
			getline(std::cin,per);
			book=objTelbook.delit(per);
			vivod(book);
			break;
		}
	case 2: // добавление человека с номерами 
		{
			cout<<"Вы зашли в функцию добавления контата. Введите ФИО:"<<endl;
			getline(std::cin,per);
			cout<<"Сколько телефонных номеров вы хотите добавить?"<<endl;
			cin>>zadacha;
			if (zadacha<11)
			{
				if (zadacha>1) // если номеров несколько
				{
					book1.push_back(per);
					cout<< "Введите номерa:"<<endl; 
					for (int i=0; i<zadacha; i++)
					{ 
						cin>>tel;
						book1.push_back(tel);	 
						tel.clear();
						}
					book=objTelbook.dobavlenie(book1);
					vivod(book);
					per.clear();
					book1.clear();
					book1.shrink_to_fit();
					break;
				}
				else // если номер 1
				{
					cout<< "Введите номер:"<<endl; 
					cin>>tel;
					book=objTelbook.OdinNomDobavlenie(per,tel);
					vivod(book);
					break;
				}
			}
			else 
			{
				cout<<"Можно не более 10"<<endl;
				break;
			}
		}
	case 3: // поиск по имени 
		{
			cout<< "Вы вошли в функцию поиска абонента по имени. Введите ФИО :"<<endl;
			getline(std::cin,per);
			book1=objTelbook.poiskpoimeni(per);
			if (book1.size()>0)
			{
			cout<<"Номера телефона данного абонента"<<endl;
			VivodImeni(book1);
			}
			break;
		}
	case 4:// поиск по номеру 
		{
			cout<<"Вы вошли в функцию поиска по номеру. Ведите номер:"<<endl;
			cin>>per;
			per=objTelbook.poiskpotel(per);
			cout<<per<<endl;
			break;
		}
	case 5:// начинающиеся с определенных букв 
		{
			cout<< "Вы вошли в функцию поиска абонентов по первым буквам имени.Введите буквы :";
			getline(std::cin,per);
			book=objTelbook .poiskpobokve(per) ;
			if (book.size()>0)
			VivodBukvi(book);
			break;
		}
	case 6: // удаление телефона определенного человека 
		{
			cout<<"Вы вошли в функцию удаления телефона из контакта. Введите ФИО абонента:"<<endl;
			getline(std::cin,per);
			cout<<"Введите номер телефона, который хотите удалить:"<<endl;
			cin>>tel;
			book=objTelbook.delittel(per, tel);
			vivod(book);
			break;
		}
	}
	cout<<"Хотите выполнить еще какие-нибудь операции? Если да - выберите номер этой операции"<<endl;
	cin>>zadacha;
	}
	cout<<"Телефонная книга все сделала."<<endl;
	system("pause");
	return 0;
}
