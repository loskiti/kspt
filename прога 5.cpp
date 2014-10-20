#include <iostream>
#include <fstream>
#include < stdio.h >
#include <string>
#include <vector>
using namespace std;
int main(int argc,char *argv[]){
	char simvol; 
	string input = "C:\\Users\\Всемогущая\\Music\\5\\in.txt", output = "C:\\Users\\Всемогущая\\Music\\5\\out.txt";
	int flag2, flag, flag1, star1, star2,i;
	if (argc>=2) 
	{ 
	input = argv[1];
	}
	if (argc>=3)
	{
	output = argv[2];
	}

	//FILE *DocIn;
	vector<char> stroka;
	ifstream file;
	ofstream outfile;
	file.open(input);
	outfile.open(output);
	//ofstream DocOut("C:\\Users\\Всемогущая Оо\\Music\\5\\out.txt",ios::out);
	//ifstream DocIn;
	//DocIn.open("C:\\Users\\Всемогущая Оо\\Music\\5\\in.txt", ios::in);
	//DocIn = fopen (nameIn,"r");
//ofstream DocOut(nameOut,ios::out);
	outfile <<"<html> <body>"<<endl;
	flag=0;
	flag2=0;
	flag1=0;
	star1=0;
	star2=0;
	while (/*1*/!(file.eof()))
	{
		
		// Чтение одного байта из файла
		//simvol = fgetc (DocIn);
		file.get(simvol);
		//Проверка на конец файла или ошибку чтения
		//if (simvol == EOF)
		//{
			// Проверяем что именно произошло: кончился файл
			// или это ошибка чтения
			//if ( /*feof (DocIn)*/ file.eof() != 0)
			//{  
				//Если файл закончился, выходим из бесконечного цикла
			//	break;
			//}
			//else
			//{
				//Если при чтении произошла ошибка, выводим сообщение об
				// ошибке и выходим из бесконечного цикла

			//	break;
			//}
		//}
		//Если файл не закончился, и не было ошибки чтения
		//выводим код считанного символа на экран

		stroka.push_back(simvol); 
			}

	int size =stroka.size();

	// Вывод заполненного вектора на экран
	for (int i = 0; i < size-1; i++)
	{

		if (stroka[i]=='*')
		{
			// if (stroka[i]=='*')

			if (stroka[i+1]!='*')
			{

				if (flag2==0)
				{
					flag2=1;
					outfile<<("<i>");
				}
				else 
				{
					flag2=0;
					outfile<< ("</i>");
				}

			}
			else 
			{
				
				if (star1==0)
				{
					star1=1;
					outfile<<("<b>");

				}
				else  
				{
					star1=0;
					outfile<<("</b>");

				}
				i+=1;
			}
		}
		if (stroka[i]=='/') 
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
		if (stroka[i]=='#')  
		{
			if ((stroka[i-1]==10) || (i==0))
			{
				flag=1;
				flag1=1;
			}

			if (flag>=1)
			{
				flag=flag+1;
			}
			if (((stroka[i+1]!='#') || (flag==8)) && (flag1==1))
			{
				outfile<<"<h" <<flag-1<<">";
				
				flag1=flag-2;
			}
			else 
				if ((flag>8) || (flag1==0))
				{
					outfile<<stroka[i];
				}
			

			


		}
		if (stroka[i]==10)
		{
			if (flag1>1)
			{
				outfile<<"</h" <<flag1+1<<">";
				flag1=0;
				flag=0;
			}
			
				if((stroka[i+1]==10) && (i<size-2) )
				{
					if (star2==0)
					{
						star2=1;
						outfile<<("<p>");

					}
					else 
					{
						star2=0;
						outfile<<("</p>");
					}
				}
				else outfile<<stroka[i];

				

			
		}
		if ((stroka[i]!=10) && (stroka[i]!='#') && (stroka[i]!='/') && (stroka[i]!='*')) 
			outfile<<stroka[i];

	}
	stroka.clear();
	//stroka. shrink_to_fit();

	outfile<<"</body> </html>"<<endl;
	//fclose (DocIn);
	//DocOut.close();
	file.close();
	outfile.close();
	system("pause");
	return 0;
}