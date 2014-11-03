// Задача 5 "Text"
// Лосева Катя 13501/4
// Реализовать простейшее преобразование из некоего подмножества языка Markdown в язык HTML.
// Исходный текст необходимо преобразовать по следующим правилам:
// Весь текст "оборачивается" в теги <html><body>...</body></html>;
// **текст** считается полужирным и оборачивается в тег <b>;
// *текст* считается курсивом и оборачивается в тег <i>;
// Строка, начинающаяся с 1 или больше символов '#', считается заголовком, и оборачивается в тег <hN>, 
// где N - количество этих символов, но не более 7;
// Любой текст, отделённый пустыми строками, считается параграфом, и оборачивается целиком в тег <p>;
// Любой символ может быть отделён символом '\', при этом он не участвует в других операциях, 
// например '\*' выводится в итоговый файл как '*', но не может начинать курсивное или полужирное начертание. 
// Сам символ '\' выводится с помощью последовательности '\\'.
// Входной и выходной файл задавать как аргументы командной строки. 
// В случае отсутствия аргументов командной строки считать, что их имена соответственно in.md и out.html.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
string OutTeg; // сам тег, т.е. "<i>" или "</b>" 
int WorkWithTeg (int WorkTeg, const char teg, string output) // подготовка "обозначений" тегов к записи
{	
	if (WorkTeg==0) // открытие тега
	{
		WorkTeg=1; 
		OutTeg=teg;
		OutTeg.push_back('>');
		OutTeg.insert(OutTeg.begin(), '<');
	}
	else  // закрытие тега
	{
		WorkTeg=0;
		OutTeg=teg;
		OutTeg.push_back('>');
		OutTeg="</"+OutTeg;
	}
	return WorkTeg;
}
int main(int argc,char *argv[]){
	char simvol; 
	string input = "in.md", output = "out.html";
	int OneStarTeg, TitleTeg_N, TitleTeg_flag, DoubleStarTeg, TitleTeg,i;
	if (argc>=2) //если входной и выходной файл являются аргументами командной строки
	{ 
		input = argv[1];
	}
	if (argc>=3)
	{
		output = argv[2];
	}
	vector<char> stroka; // массив, элементом которого является 1 символ
	ifstream file; // если входной и выходной файл не задаются через командную строку
	file.open(input);
	ofstream outfile(output,ios::out);
	outfile <<"<html> <body>"<<endl;
	TitleTeg_N=0;           // определение, надо открыть или закрыть тег "<hN>"
	OneStarTeg=0;     // определение, надо открыть или закрыть тег "<i>"
	TitleTeg_flag=0;  // счетчик в теге "<hN>"
	DoubleStarTeg=0;  // определение, надо открыть или закрыть тег "<b>"
	TitleTeg=0;      // определение, надо открыть или закрыть тег "<p>"
	while (!(file.eof()))// Чтение одного байта из файла и запись этого элемента в массив
	{		
		file.get(simvol);
		stroka.push_back(simvol); 
	}
	int size =stroka.size();
	for (int i = 0; i < size-1; i++)
	{
		if (stroka[i]=='*') // работа с тегами <b> и <i>
		{
			if (stroka[i+1]!='*')
			{		
				OneStarTeg=WorkWithTeg(OneStarTeg,'i', output); // создание тега "<i>" или "</i>" 
				outfile<<OutTeg;                          // и запись его в файл
			}
			else 
			{				
				DoubleStarTeg=WorkWithTeg(DoubleStarTeg,'b', output); // создание тега "<b>" или "</b>" 
				i+=1;                           // "пропускаем" следующий символ, тк он является 
				//  частью тега
				outfile<<OutTeg;                //  запись тега в файл
			}
		}
		if (stroka[i]=='/') // "пропуск" одинарного символа "/"
		{
			if (stroka[i+1]=='/')
			{
				outfile<<stroka[i];
				i+=1;
			}
			if (stroka[i+1]=='*')
			{
				outfile<<stroka[i+1];
				i+=1;
			}
			if (stroka[i+1]=='#')
			{
				outfile<<stroka[i+1];
				i+=2;
			}
		}
		if (stroka[i]=='#')  // работа с тегом заголовка
		{
			if ((stroka[i-1]==10) || (i==0)) // определение, является ли символ "#"
			{                                // началом строки
				TitleTeg_N=1; // символ - начало строки, до него не стоит "/"
				TitleTeg_flag=1; // требуется использование тега "<hN>"
			}
			if (TitleTeg_N>=1) // подсчет кол-ва подряд стоящих символов "#" 
			{
				TitleTeg_N=TitleTeg_N+1;
			}
			if (((stroka[i+1]!='#') || (TitleTeg_N==8)) && (TitleTeg_flag==1)) // открытие тега "<hN>"
			{
				outfile<<"<h" <<TitleTeg_N-1<<">"; 
				TitleTeg_flag=TitleTeg_N-2; // кол-во "#", являющихся частью тега "<hN>"
			}
			else  // если символов "#" больше 7 или они не начинают строку, 
				// то они не являются частью тега "<hN>"
				if ((TitleTeg_N>8) || (TitleTeg_flag==0))
				{
					outfile<<stroka[i];
				}			
		}
		if (stroka[i]==10) // работа с символом перехода на новую строку
		{
			if (TitleTeg_flag>1) // закрытие тега "<hN>"
			{
				outfile<<"</h" <<TitleTeg_flag+1<<">";
				TitleTeg_flag=0;
				TitleTeg_N=0;
			}

			if((stroka[i+1]==10) && (i<size-2) ) // при условии, что следующая строка - пустая 
			{
				TitleTeg=WorkWithTeg(TitleTeg,'p', output); // создание тега "<р>" или "</р>" 
				outfile<<OutTeg;                           // и запись его в файл
			}
			else outfile<<stroka[i]; // просто переход на новую строку
		}
		if ((stroka[i]!=10) && (stroka[i]!='#') && (stroka[i]!='/') && (stroka[i]!='*')) 
			// вывод обычных символов, не являющихся началами тегов
			outfile<<stroka[i];

	}
	stroka.clear(); //"очищение" массива
	stroka. shrink_to_fit();
	outfile<<"</body> </html>"<<endl;
	file.close(); // закрытие файлов
	outfile.close();
	system("pause");
	return 0;
}
