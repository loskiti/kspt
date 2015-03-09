#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void vniz(int &x1, int &y1, int i, vector<vector<int>> &map,string &otvet)
{
	if (map[y1][x1-1]==i-1) 
	{	
		map[y1][x1]=-3;
		x1=x1-1;
		otvet.push_back('l');
		return;
	}					
	if (map[y1][x1+1]==i-1) 
	{	
		map[y1][x1]=-3;
		x1=x1+1;
		otvet.push_back('r');
		return;
	}
	if (map[y1-1][x1]==i-1) 
	{	
		map[y1][x1]=-3;
		y1=y1-1;
		otvet.push_back('u');
		return;
	}	
	if (map[y1+1][x1]==i-1) 
	{	
		map[y1][x1]=-3;
		y1=y1+1;
		otvet.push_back('d');
		return;
	}

}
void vverx (int &x1, int &y1, int i, vector<vector<int>> map, string &otvet)
{
	if (map[y1][x1-1]==i+1) 
	{	
		x1=x1-1;
		i++;
		otvet.push_back('l');
		return;
	}					
	if (map[y1][x1+1]==i+1) 
	{
		x1=x1+1;
		i++;
		otvet.push_back('r');
		return;
	}
	if (map[y1-1][x1]==i+1) 
	{	
		y1=y1-1;
		i++;
		otvet.push_back('u');
		return;
	}	
	if (map[y1+1][x1]==i+1) 
	{	
		y1=y1+1;
		i++;
		otvet.push_back('d');
		return;
	}
}
bool rec (int &x1,int &y1,int i,int &k, vector<vector<int>> &map,string &stroka, vector <int> &stop )
{
	bool flag;
	if (k==i)
	{
		for(int j=stop.size()-1; j>-1;j-=3)
		{
			if ((map[stop[j-1]][stop[j-2]]==k)&&((stop[j-1]==y1) &&(x1==stop[j-2])))
			{
				stop.erase(stop.begin() + j-2, stop.end() -(stop.size()-j-1));
				if (stop.size()	>0)
					k=map[stop[stop.size()-2]][stop[stop.size()-3]];
				else 
					k=0;

				if (i>k)
				{
					vniz(x1, y1, i, map,stroka);
					return true;
				}
				else 
				{
					vniz(x1, y1, i, map,stroka);
					return false;
				}
			}
		}
		map[y1][x1]=-3;
		return false;
	}

	if (k>i) // счетчик!!!
	{
		vverx(x1,y1,i,map, stroka);
		flag=rec(x1, y1, i+1, k, map, stroka, stop);
	}
	if (flag==true)
	{
		vniz(x1, y1, i, map,stroka);
		return true;
	}
	else 
	{
		if ((map[y1][x1-1]==i+1)||(map[y1][x1+1]==i+1) ||(map[y1+1][x1]==i+1)||(map[y1-1][x1]==i+1))
		{
			vverx(x1,y1,i,map, stroka);
			flag=rec(x1, y1,  i+1, k, map, stroka, stop);
			if (flag==true) 
			{
				vniz(x1, y1, i, map,stroka);
				return true;
			}
		}
		else
		{
			vniz(x1, y1, i, map,stroka);			
			return false;			
		}
	}// вниз до ближайщего и тд
	return false;
}


void rech(int z, vector<vector<int>> &map, int stroka_size, int x)
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
	file.open("C:\\Users\\Всемогущая Оо\\Desktop\\in.txt");
	char simvol; 
	vector <vector <int>> map;
	int i=0;
	int x=0, y=0, x1, y1, x3, y3;
	vector <int> stroka;
	vector <int> stop;
	while (!(file.eof()))// Чтение одного байта из файла и запись этого элемента в массив
	{		
		file.get(simvol);
		if (simvol ==10) 
		{			
			map.push_back(stroka);
			stroka.clear(); 
			//stroka. shrink_to_fit();
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
				x=stroka.size();
				y=i;
				stroka.push_back(0);
				break;
			}
		case 'e': 
			{
				x1=stroka.size();
				y1=i;
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
	while (((x+i)<stroka.size()-1) || ((x-i)>0))  // распространение волны
	{

		int n=0,  k=0;
		while (((y+n)>0) || ((y+k)<map.size()-1))
		{
			if ((y+n)>0)
				rech(y+n, map,stroka.size(), x);
			if ((y+k)<map.size()-1)
				rech(y+k, map,stroka.size(),x);
			n--;
			k++;
		}
		i++;
	}
	i=0;

	int temp; 
	for (i = 2; i < stop.size(); i+=3)
	{
		temp = stop[i]; // инициализируем временную переменную текущим значением элемента массива
		// запоминаем индекс предыдущего элемента массива
		while(i-3 >= 0 && stop[i-3] > stop[i]) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
		{
			stop[i] = stop[i-3]; // перестановка элементов массива
			stop[i-3] = temp;
			temp=stop[i-1];
			stop[i-1]=stop[i-4];
			stop[i-4]=temp;
			temp=stop[i-2];			
			stop[i-2]=stop[i-5];			
			stop[i-5]=temp;
			i-=3;
		}
	}

	string otvet;
	bool flag;
	int k=map[stop[stop.size()-2]][stop[stop.size()-3]];
	for (i=map[y1][x1]; i>-1;i--)
	{
		if (k<i)
			vniz(x1,y1,i,map, otvet);
		if (k==i)
		{
			if ((stop[stop.size()-3]!=x1) ||(y1!=stop[stop.size()-2]))
			{
				while ((map[y1][x1-1]!=i+1)&&(map[y1][x1+1]!=i+1) &&(map[y1+1][x1]!=i+1)&&(map[y1-1][x1]!=i+1))
				{
					vniz(x1,y1,i,map, otvet);
					i--;
				}
				if (2*0.1*(k-i)< stop[stop.size()-1])				
					flag=rec(x1,  y1, i, k, map, otvet, stop);

				if (flag == true)
				{
					if ((k==0) && (i==0))
						break;
					vniz(x1,y1,i,map, otvet);
				} 
			}

			else 
			{
				vniz(x1,y1,i,map, otvet);
			}

		}

	}
	cout<<otvet<<endl;
	file.close();
	system ("pause");
	return 0;
}
