// заголовочный файл TelBook.h
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class TelBook
{
private:
	vector<vector <string>> book;
public:
	TelBook(const vector<vector <string>>&);
	//void setBook (const vector <vector<string>>&);
	bool delit(string ); // удаление абонента со всеми номерами
	vector<string> poiskpoimeni(string);// поиск абонента по имени
	string poiskpotel(string);// поиск абонента по телефону
	vector<vector <string>> poiskpobokve(string );// начинающиеся с определенных букв 
	~TelBook();
	bool dobavlenie( vector <string>&);// добавление абонента с несколькими номерами
	bool delittel(string, string);// удаление 1 телефона из контакта,
	                             //у которого телефонов много
	bool OdinNomDobavlenie(string, string); // добавление пары абонент-телефон
	void vivod ();
	void vvod();
	void massiv(const vector <char>&, string&, string&);
};
