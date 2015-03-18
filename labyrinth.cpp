// Работа Лосевой Кати группа 13501/4
// Поиск кротчайшего пути по лабиринту с возможностью получения бонуса.
// Реализовано с помощью волнового алгоритма. Есть проверка: стоит ли идти до бонуса - принесет ли он дополнительные 
// баллы или нет.
// Пример работы: https://yadi.sk/i/M4EE2U1yf9bTM



#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
// спускаемся на 1 клетку по волне ( с 19 ячейки на 18 и тд)
void StepDown(int &Out_X, int &Out_Y, int i, vector<vector<int>> &map,string &otvet) 
{ 
	if (map[Out_Y][Out_X-1]==i-1) 
	{	
		map[Out_Y][Out_X]=-3;
		Out_X=Out_X-1;
		otvet.push_back('r');
		return;
	}					
	if (map[Out_Y][Out_X+1]==i-1) 
	{	
		map[Out_Y][Out_X]=-3;
		Out_X=Out_X+1;
		otvet.push_back('l');
		return;
	}
	if (map[Out_Y-1][Out_X]==i-1) 
	{	
		map[Out_Y][Out_X]=-3;
		Out_Y=Out_Y-1;
		otvet.push_back('d');
		return;
	}	
	if (map[Out_Y+1][Out_X]==i-1) 
	{	
		map[Out_Y][Out_X]=-3;
		Out_Y=Out_Y+1;
		otvet.push_back('u');
		return;
	}

}
// поднимаемся на 1 клетку по волне ( с 18 ячейки на 19 и тд)
void StepUp (int &Out_X, int &Out_Y, int i, vector<vector<int>> map, string &otvet)
{
	if (map[Out_Y][Out_X-1]==i+1) 
	{	
		Out_X=Out_X-1;
		i++;
		otvet.push_back('r');
		return;
	}					
	if (map[Out_Y][Out_X+1]==i+1) 
	{
		Out_X=Out_X+1;
		i++;
		otvet.push_back('l');
		return;
	}
	if (map[Out_Y-1][Out_X]==i+1) 
	{	
		Out_Y=Out_Y-1;
		i++;
		otvet.push_back('d');
		return;
	}	
	if (map[Out_Y+1][Out_X]==i+1) 
	{	
		Out_Y=Out_Y+1;
		i++;
		otvet.push_back('u');
		return;
	}
}
// поиск ячейки с цифрой
bool Search (int &Out_X,int &Out_Y,int i,int &k,int &summa,int &flag2, vector<vector<int>> &map,string &stroka, vector <int> &stop )
{

	flag2=0;
	bool flag;
	if (k==i)
	{
		for(int j=stop.size()-1; j>-1;j-=3) // нашли ячейку, проверяем: она ли это
		{
			if ((map[stop[j-1]][stop[j-2]]==k)&&((stop[j-1]==Out_Y) &&(Out_X==stop[j-2])))
			{
				summa=summa +stop[j];
				stop.erase(stop.begin() + j-2, stop.end() -(stop.size()-j-1));
				if (stop.size()	>0)
					k=map[stop[stop.size()-2]][stop[stop.size()-3]];
				else 
					k=-1;

				if (i>k) // если ячеек с цифрой на данном отрезке несколько - вернем false и поищем их
				{
					StepDown(Out_X, Out_Y, i, map,stroka);
					return true;
				}
				else 
				{
					StepDown(Out_X, Out_Y, i, map,stroka);
					return false;
				}
			}
		}
		map[Out_Y][Out_X]=-3; // ячейка нам не подходит
		flag2=1;
		StepDown(Out_X, Out_Y, i, map,stroka);

		return false;
	}

	if (k>i) // идем до нужной ячейки
	{
		StepUp(Out_X,Out_Y,i,map, stroka);
		flag=Search(Out_X, Out_Y, i+1, k, summa,flag2, map, stroka, stop);
	}
	if (flag==true) // ячейку нашли, возвращаемся к исходному пути
	{
		StepDown(Out_X, Out_Y, i, map,stroka);
		return true;
	}
	else // вдруг по дороге встетится еще одна ячейка с цифрой
	{
		if ((map[Out_Y][Out_X-1]==i+1)||(map[Out_Y][Out_X+1]==i+1) ||(map[Out_Y+1][Out_X]==i+1)||(map[Out_Y-1][Out_X]==i+1))
		{
			StepUp(Out_X,Out_Y,i,map, stroka);
			flag=Search(Out_X, Out_Y,  i+1, k,summa,flag2, map, stroka, stop);
			if (flag==true) 
			{
				StepDown(Out_X, Out_Y, i, map,stroka);
				return true;
			}
			
		}
		else
		{ 
			if(flag2!=1)
			{
				StepDown(Out_X, Out_Y, i, map,stroka);
			}
			return false;			
		}
	}
	flag2=1;
	return false;
}

// распространение волны
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
int main(int argc,char *argv[])
{
	setlocale(LC_ALL, "rus"); 
	ifstream file;
	file.open(argv[1]);
	char simvol; 
	vector <vector <int>> map; // поле
	int i=0;
	int Entry_X=0, Entry_Y=0, Out_X, Out_Y; // координаты входа и выхода
	vector <int> stroka;
	vector <int> stop; // координаты ячейки с цифрой 
	// чтение поля из файла
	while (!(file.eof()))
	{		
		file.get(simvol);
		if (simvol ==10) 
		{			
			map.push_back(stroka);
			stroka.clear(); 
			stroka. shrink_to_fit();
			i++;
			continue;
		};

		switch(simvol) 
		{
		case '#':
			{
				stroka.push_back(-2);
				break;
			}
		case ' ':
			{
				stroka.push_back(-1);
				break;
			}
		case '*':
			{	
				Entry_X=stroka.size();
				Entry_Y=i;
				stroka.push_back(0);
				break;
			}
		case 'e': 
			{
				Out_X=stroka.size();
				Out_Y=i;
				stroka.push_back(-1);
				break;
			}
		default: 
			{
				stop.push_back(stroka.size());
				stop.push_back(i);
				stop.push_back(atoi(&simvol));
				stroka.push_back(-1);
				break;
			}
		}
	}
	stroka.pop_back();
	map.push_back(stroka);
	i=0;
	while (((Entry_X+i)<stroka.size()-1) || ((Entry_X-i)>0))  // распространение волны
	{

		int n=0,  k=0;
		while (((Entry_Y+n)>0) || ((Entry_Y+k)<map.size()-1))
		{
			if ((Entry_Y+n)>0)
				wave(Entry_Y+n, map,stroka.size(), Entry_X);
			if ((Entry_Y+k)<map.size()-1)
				wave(Entry_Y+k, map,stroka.size(),Entry_X);
			n--;
			k++;
		}
		i++;
	}
	i=0;
	// каждой точке после распространения волны присвивается цифра (кол-во ходов до точки)
	// сортировка массива по возрастанию  кол-ва шагов до ячейки
	int flag2; 
	for (i = 2; i < stop.size(); i+=3)
	{
		flag2 = stop[i]; 

		while((i-5)>=0 && map[stop[i-4]][stop[i-5]]>map[stop[i-1]][stop[i-2]])
		{
			stop[i] = stop[i-3]; 
			stop[i-3] = flag2;
			flag2=stop[i-1];
			stop[i-1]=stop[i-4];
			stop[i-4]=flag2;
			flag2=stop[i-2];			
			stop[i-2]=stop[i-5];			
			stop[i-5]=flag2;
			i-=3;
		}
	}


	string otvet;
	bool flag;
	flag2=0;
	int summa=0;
	int k;
	if(stop.size()>0)  // проверка, есть ли вообще ячейки с цифрами и нужно ли их искать
		k=map[stop[stop.size()-2]][stop[stop.size()-3]];
	else  k=-1;
	int x,y, flag4;
	// поиск кротчайшего пути
	for (i=map[Out_Y][Out_X]; i>-1;i--)
	{
		x=Out_X;
		y=Out_Y;
		int i1=i;
		if (k<i)
			StepDown(Out_X,Out_Y,i,map, otvet);
		if ((k==i)||(k>i)) // цена ячейки равна цене ячейки с цифрой, проверка: она ли это, если нет - поиск
		{ // точки с этой цифрой
			if ((stop[stop.size()-3]!=Out_X) ||(Out_Y!=stop[stop.size()-2]))
			{ // спускаемся вниз, пока не достигнем точки, с которой можно попасть в ячейку с цифрой
				while ((map[Out_Y][Out_X-1]!=i+1)&&(map[Out_Y][Out_X+1]!=i+1)
				&&(map[Out_Y+1][Out_X]!=i+1)&&(map[Out_Y-1][Out_X]!=i+1))
				{
					StepDown(Out_X,Out_Y,i,map, otvet);
					i--;
					x=Out_X;
					y=Out_Y;
				}
				string flag3=otvet;
				flag=Search(Out_X,  Out_Y, i, k,summa,flag4, map, otvet, stop);
				// если "вес" точки не перекрывает затраченные на нее шаги - мы в эту точку не идем
				if ((otvet.length()-flag3.length())*0.1>=summa)
					otvet=flag3;
				if (flag4==1)
				{ // если не были найдены необходимые нам ячейки с цифрами
					otvet=flag3;
					Out_X=x;
					Out_Y=y;
					i=map[Out_Y][Out_X]+1;

				}
				summa=0;
				if (flag == true) // если точка найдена, продолжим путь
				{
					if ((k==0) && (i==0)) // нашли все ячейки - идем к выходу
						break;
					StepDown(Out_X,Out_Y,i,map, otvet);
				} 
			}

			else 
			{
				StepDown(Out_X,Out_Y,i,map, otvet);
			}

		}

	}
	for (i=otvet.length()-1;i>-1; i--)
	{
		cout<<otvet[i];
	}
	stroka.clear(); 
	stroka. shrink_to_fit();
	map.clear(); 
	map. shrink_to_fit();
	stop.clear(); 
	stop. shrink_to_fit();
	file.close();
	//system ("pause");
	return 0;
}
