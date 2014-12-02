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
void vivodRes(bool resultat)
{
	if (resultat == true) cout<<"Выполнено"<<endl;
			else cout<<"Таких данных не существует"<<endl;
}
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
void VivodImeni(vector<string>&book) // вывод данных по поиску по имени
{
	for (int i=0; i<book.size(); i++)

		{
			cout<<book[i]<<endl;
		}
		
}

int main()
{
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
vector<vector <string>> book; // таблица номеров
vector <string> book1;
string tel;
TelBook objTelbook(book); 
objTelbook.vvod();// чтение из файла
cout<<"Вас приветствует ТЕЛЕФОННАЯ КНИГА"<<endl<<"Для продолжения работы выберите 1 из пунктов меню (введите цифру функции)"<<endl;
cout<<"1 - удаления контакта"<<endl<<"2 - добавления контата"<<endl<<"3 - поиска абонента по имени"<<endl<<"4 - поиска по номеру"<<endl<<"5 - поиска абонентов по первым буквам имени"<<endl<<"6 - удаление телефона из контакта"<<endl;
int zadacha=0;
cin>>zadacha;
string per;
bool resultat;
while(zadacha<7 && zadacha>0) //меню
	{
	switch (zadacha)
	{
	case 1:  //удаление человека с номерами 
		{
			cout<<"Вы зашли в функцию удаления контакта. Введите его имя:"<<endl;
			getline(std::cin,per);
			resultat=objTelbook.delit(per);
			vivodRes(resultat);
			objTelbook.vivod();
			break;
		}
	case 2: // добавление человека с номерами 
		{
			cout<<"Вы зашли в функцию добавления контата. Введите ФИО:"<<endl;
			getline(std::cin,per);
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
					resultat=objTelbook.dobavlenie(book1);
					vivodRes(resultat);
					objTelbook.vivod();
					per.clear();
					book1.clear();
					book1.shrink_to_fit();
					break;
				}
				else // если номер 1
				{
					cout<< "Введите номер:"<<endl; 
					cin>>tel;
					resultat=objTelbook.OdinNomDobavlenie(per,tel);
					objTelbook.vivod();
					vivodRes(resultat);
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
			resultat=objTelbook.delittel(per, tel);
			vivodRes(resultat);
			objTelbook.vivod();
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
