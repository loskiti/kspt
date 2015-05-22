// Дополнительная задача № 2 
// Лосева Катя 13501/4
// Написать определение функции findLongestSubstring, находящей самую длинную общую подстроку в двух заданных C-строках. 
// Результат записывается в символьный массив res также в виде C-строки, считать, что места в этом массиве достаточно. 
// Если общей подстроки нет, возвращается пустая строка. Все C-строки должны заканчиваться нуль-символом, 
// их длина никак не ограничивается. Библиотечные функции использовать не разрешается.

#include <iostream>
using namespace std;
int ComElem; // проверка, если ли в 2 строках хоть один общий элемент
int find(const char a[], const char b[], char res[], int i, int j) {
	if ((a[i]!='\0') &&(b[i]!='\0')) //поиск самой длинной общей подстроки
	{
		if (a[i]==b[j]) 
		{ComElem=1;
		i=find(a, b, res, i+1, j+1);
		return i;
		}
		else return i-1;
	}
	else return i-1;
}
void findLongestSubstring(const char a[], const char b[], char res[]) {
	int Substring_Begin,Substring_Begin_Max,Substring_End_Max,Substring_End, i;
	Substring_Begin_Max=0;
	Substring_End_Max=0;
	ComElem=0;
	for ( i=0; a[i]!='\0'; i++)
	{
		for (int j=0; b[j]!='\0'; j++)
		{
			Substring_End=0;
			Substring_Begin=i; // 1 элемент общей подстроки
			Substring_End=find(a, b, res, i, j); // возвращает номер последнего общего 
			// для 2 строк элемента
			if ((Substring_End-Substring_Begin)>(Substring_End_Max-Substring_Begin_Max))   
			{  //проверка, является ли данная последовтельность наибольшей
				Substring_Begin_Max=Substring_Begin;
				Substring_End_Max=Substring_End;

			}
		}
	}
	if (ComElem!=1) res[0]='\0'; // если общих элементов нет - выводится пустая строка
	else 
	{	 
		int j=0;
		for ( i=Substring_Begin_Max; i<=Substring_End_Max; i++) // общие элементы записываются в  
		{  // строку-результат, ненужные элементы из строки-результата удаляются
			res[j]=a[i];
			j++;
		}
		res[j]='\0';
	}

}


int main()
{
	setlocale(LC_ALL, "rus");
	const char str1[] = {"dhjkqlsae"};
	const char str2[] = {"kjhdsrd"};
	char res[] = {"eg2341ilka"} ;

	findLongestSubstring(str1, str2,res);
	cout << "1 исходная строка: " << str1 << endl;
	cout << "2 исходная строка: " << str2 << endl;
	cout << "Самая длинная общая подстрока: " << res << endl;
	system("pause");
	return 0;
}
