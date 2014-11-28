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
	vector<vector<string>> delit(string ); // удаление абонента со всеми номерами
	void message();
	vector<string> poiskpoimeni(string);// поиск абонента по имени
	string poiskpotel(string);// поиск абонента по телефону
	vector<vector <string>> poiskpobokve(string );// начинающиеся с определенных букв 
	~TelBook();
	vector<vector <string>> dobavlenie( vector <string>&);// добавление абонента с несколькими номерами
	vector<vector <string>> delittel(string, string);// удаление 1 телефона из контакта,
	                                                 //у которого телефонов много
	vector<vector <string>> OdinNomDobavlenie(string, string); // добавление пары абонент-телефон
};
