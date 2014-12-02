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

string WorkWithTag (int& WorkTag, const char tag, string output) // подготовка "обозначений" тегов к записи
{	
	string OutTag;
	if (WorkTag==0) // открытие тега
	{
		WorkTag=1; 
		OutTag=tag;
		OutTag.push_back('>');
		OutTag.insert(OutTag.begin(), '<');
	}
	else  // закрытие тега
	{
		WorkTag=0;
		OutTag=tag;
		OutTag.push_back('>');
		OutTag="</"+OutTag;
	}
	return OutTag;
}
int main(int argc,char *argv[]){
	char simvol; 
	string input = "in.md", output = "out.html";
	int OneStarTag, TitleTag_N, TitleTag_flag, DoubleStarTag, TitleTag,i;
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
	TitleTag_N=0;           // определение, надо открыть или закрыть тег "<hN>"
	OneStarTag=0;     // определение, надо открыть или закрыть тег "<i>"
	TitleTag_flag=0;  // счетчик в теге "<hN>"
	DoubleStarTag=0;  // определение, надо открыть или закрыть тег "<b>"
	TitleTag=0;      // определение, надо открыть или закрыть тег "<p>"
	while (!(file.eof()))// Чтение одного байта из файла и запись этого элемента в массив
	{		
		file.get(simvol);
		stroka.push_back(simvol);	
	}
	stroka.pop_back();
	int size =stroka.size();
	string OutTag; // сам тег, т.е. "<i>" или "</b>" 
	for ( i = 0; i < size-1; i++)
	{
		switch(stroka[i])
		{
		case '*': // работа с тегами <b> и <i>
			{  
			        if (stroka[i+1]!='*')
		        	{		
				OutTag=WorkWithTag(OneStarTag,'i', output); // создание тега "<i>" или "</i>" 
			        	outfile<<OutTag;                          // и запись его в файл
			        }
			        else 
			        {				
				        OutTag=WorkWithTag(DoubleStarTag,'b', output); // создание тега "<b>" или "</b>" 
				        i+=1;                           // "пропускаем" следующий символ, тк он является 
				                                     //  частью тега
				         outfile<<OutTag;//  запись тега в файл
				         continue;
			        }
		        	break;
			 }

				 
		case '/': // "пропуск" одинарного символа "/"
			{
				if (stroka[i+1]=='/')
				{
					outfile<<stroka[i+1];
					i+=1;
					continue;
				}
				if (stroka[i+1]=='*')
				{
					outfile<<stroka[i+1];
					i+=1;
					continue;
				}
				if (stroka[i+1]=='#')
				{
					outfile<<stroka[i+1];
					i+=1;
					continue;
				}
	               		break;
			}
			
		case '#':// работа с тегом заголовка
			{
				if ((stroka[i-1]==10) || (i==0)) // определение, является ли символ "#"
				{                                // началом строки
					TitleTag_N=1; // символ - начало строки, до него не стоит "/"
					TitleTag_flag=1; // требуется использование тега "<hN>"
				}
				if (TitleTag_N>=1) // подсчет кол-ва подряд стоящих символов "#" 
				{
					TitleTag_N=TitleTag_N+1;
				}
				if (((stroka[i+1]!='#') || (TitleTag_N==8)) && (TitleTag_flag==1)) // открытие тега "<hN>"
				{
					outfile<<"<h" <<TitleTag_N-1<<">"; 
					TitleTag_flag=TitleTag_N-2; // кол-во "#", являющихся частью тега "<hN>"
				}
				else  // если символов "#" больше 7 или они не начинают строку, 
					// то они не являются частью тега "<hN>"
					if ((TitleTag_N>8) || (TitleTag_flag==0))
					{
						outfile<<stroka[i];
					}
				break;
			}
			
		case 10: // работа с символом перехода на новую строку
			{
				if (TitleTag_flag>1) // закрытие тега "<hN>"
				{
					outfile<<"</h" <<TitleTag_flag+1<<">";
					TitleTag_flag=0;
					TitleTag_N=0;
				}

				if((stroka[i+1]==10) && (i<size-2) ) // при условии, что следующая строка - пустая 
				{
					OutTag=WorkWithTag(TitleTag,'p', output); // создание тега "<р>" или "</р>" 
					outfile<<OutTag;                           // и запись его в файл
				}
				else outfile<<stroka[i]; // просто переход на новую строку
	                 	break;	
			}
			
		
			
		default:// вывод обычных символов, не являющихся началами тегов
			{
			outfile<<stroka[i];
			break;
			}
			
		}
	}
		if (i<stroka.size()) // вывод последнего символа при условии, что он не является частью тега
			outfile<<stroka[i];
		stroka.clear(); //"очищение" массива
		stroka. shrink_to_fit();
		outfile<<"</body> </html>"<<endl;
		file.close(); // закрытие файлов
		outfile.close();
		system("pause");
		return 0;
	}
