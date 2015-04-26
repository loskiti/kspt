#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
# include <vector>
using namespace std;
// генерация координат входа и выхода
void En_Ex(int a, int b,vector<vector<int>> map, int &X, int &Y )
{
	int x=0,y=0;
	while ((x==0)&&(y==0))
	{
		x=rand() % a +1;
		y=rand() % b +1;
		if (map[y][x]==-2)
		{
			x=0;
			y=0;
		}
	}
	X=x;
	Y=y;

}
// поиск пути по волне
void StepDown(int &Out_X, int &Out_Y, int i, vector<vector<int>> &map,string &otvet) 
{ 
	if (map[Out_Y][Out_X-1]==i-1) 
	{	
		Out_X=Out_X-1;
		otvet.push_back('r');
		return;
	}					
	if (map[Out_Y][Out_X+1]==i-1) 
	{	
		Out_X=Out_X+1;
		otvet.push_back('l');
		return;
	}
	if (map[Out_Y-1][Out_X]==i-1) 
	{	
		Out_Y=Out_Y-1;
		otvet.push_back('d');
		return;
	}	
	if (map[Out_Y+1][Out_X]==i-1) 
	{	
		Out_Y=Out_Y+1;
		otvet.push_back('u');
		return;
	}

}
//распространение волны
void wave(int z, vector<vector<int>> &map, int stroka_size, int x) 
{
	int i=0;
	while(((x+i)<stroka_size-1)) // вправо 
	{
		if (map[z][(x+i)]>=0)
		{
			if (map[z][(x+i+1)]==-1) 
				map[z][(x+i+1)]=map[z][(x+i)]+1;
			if (map[z][(x+i-1)]==-1) 
				map[z][(x+i-1)]=map[z][(x+i)]+1;
			if (map[z+1][(x+i)]==-1) 
				map[z+1][(x+i)]=map[z][(x+i)]+1;
			if (map[z-1][(x+i)]==-1) 
				map[z-1][(x+i)]=map[z][(x+i)]+1;
		}

		i++;
	}
	i=0;
	while ((x-i)>0) // влево 
	{

		if (map[z][(x-i)]>=0)
		{
			if (map[z][(x-i+1)]==-1) 
				map[z][(x-i+1)]=map[z][(x-i)]+1;
			if (map[z][(x-i+-1)]==-1)
				map[z][(x-i-1)]=map[z][(x-i)]+1;
			if (map[z+1][(x-i)]==-1) 
				map[z+1][(x-i)]=map[z][(x-i)]+1;
			if (map[z-1][(x-i)]==-1)
				map[z-1][(x-i)]=map[z][(x-i)]+1;
		}
		i++;
	}
}
int main()
{
	setlocale(0, "rus");
	srand(time(0));
	int a,b;
	cout<<"Введите размеры лабиринта:"<<endl;
	cin>>a>>b;
	vector <vector <int>> map; 
	int i;
	vector <int> stroka;
	// создание "рамки" лабиринта
	for(int j=0; j<=b;j++)
	{
		for (i=0;i<=a;i++)
		{
			if ((j==0) || (j==b))
			{
				stroka.push_back(-2);
			}
			else 

				if ((i==0) || (i==a))
					stroka.push_back(-2);
				else
					stroka.push_back(-1);
		}
		map.push_back(stroka);
		stroka.clear(); 
		stroka. shrink_to_fit();
	}
// генерация 1 строки
	for (i=1; i<a;i++)
	{
		map[1][i]=i;
	}
	for (i=2; i<a;i++)
	{
		if (rand() % 2<1)
		{
			map[1][i]=map[1][i-1];
		}
		else
		{
			map[1][i]=-2;
			i++;
		}
	}
// генерация строк, не считая 1 и последнюю

	for(int j=2; j<b-1;j++)
	{

		for (i=1;i<a;i++)
		{

			if( map[j-1][i]!=-2)
			{
				map[j][i]=map[j-1][i];
			}
			else 
			{ 
				if (i==1)
				{map[j][i]=1;}
				else
					map[j][i]=map[j][i-1];
			}


		}


		for (i=2; i<a-1;i++)
		{
			if (map[j][i]==map[j][i-1])
			{
				if (rand() % 2<1)
				{
					map[j][i]=-2;
					i++;
				}
			}
		}
	}
	string otvet;
// генерация последней строки
	for (i=1;i<a;i++)
	{
		if (map[b-1][i]!=-2)
			if( map[b-2][i]!=-2)
				map[b-1][i]=map[b-2][i];
			else map[b-1][i]=map[b-1][i-1];


	}
	for (i=1;i<a;i++)
	{
		if (map[b-1][i]==map[b-1][i+1])
			map[b-1][i]=0;

	}

	int Entry_X, Entry_Y=0, Out_X, Out_Y; // координаты входа и выхода
	// генерация координат входа и выхода
	En_Ex(a-1,b-1,map,Entry_X,Entry_Y);
	map[Entry_Y][Entry_X]=-10;
	En_Ex(a-1,b-1,map,Out_X,Out_Y);
	map[Out_Y][Out_X]=-11;
	cout<<"Сгенерированный лабирин:"<<endl;
	// вывод лабиринта
	for (i=0;i<b+1;i++)
	{
		for(int j=0; j<a+1;j++)
		{
			if (map[i][j]!=-2)
			{
				if (map[i][j]==-10)
				{	
					cout<<"*";
					map[i][j]=0;
				}
				else
				{
					if (map[i][j]==-11)
					{	
						cout<<"e";
						map[i][j]=-1;
					}
					else
					{
						cout<<".";
						map[i][j]=-1;
					}
				}
			}
			else
			{				
				cout<<"#";
				map[i][j]=-2;
			}
		}
		cout<<endl;
	}
	cout<<"(* - вход, е - выход)"<<endl;
	// распространение волны
	for (i=0; map[1].size()*map.size()>i;i++)
	{
		int n=0,  k=0;
		while (((Entry_Y+n)>0) || ((Entry_Y+k)<map.size()-1))
		{
			if ((Entry_Y+n)>0)
				wave(Entry_Y+n, map,map[Entry_Y+n].size(), Entry_X);
			if ((Entry_Y+k)<map.size()-1)
				wave(Entry_Y+k, map,map[Entry_Y+k].size(),Entry_X);
			n--;
			k++;
		}

	}
	// поиск пути
	for (i=map[Out_Y][Out_X]; i>-1;i--)
	{
		StepDown(Out_X,Out_Y,i,map, otvet);
	}
	cout<<"Шаги:"<<endl;
	// вывод пути
	for (i=otvet.length()-1;i>-1; i--)
	{
		cout<<otvet[i];
	}
	cout<<endl;
	cout<<"d - вниз, u - вверх, l - влево, r - вправо"<<endl;
	map.clear(); 
	map. shrink_to_fit();
	system ("pause");
	return 0;
}
