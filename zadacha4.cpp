// Matrix Лосева Екатерина 13501.4
//Матрицу K(m,n) заполнить следующим образом. 
//Элементам, находящимся на периферии (по периметру матрицы), присвоить значение 1; 
//периметру оставшейся подматрицы – значение 2 и так далее до заполнения всей матрицы. 
//Числа m и n следует читать из файла in.txt. 
//Матрицу-результат следует записывать в файл out.txt 
//(первые два числа в файле – размерности матрицы, далее – элементы матрицы).


#include <iostream>
#include <fstream>
using namespace std;
int main(){
int m,n;
ofstream DocOut("out.txt",ios::out);
ifstream DocIn;
DocIn.open("in.txt", ios::in);
DocIn>>m>>n;
int *k = new int[m,n];
for (int i = 0; i <= n-1; i++) {
	for (int j=0; j<=m-1;j++){
	        if ((i<n/2) && (j>=i) && (j<=m-i-1))
                {
		  k[i,j]=i+1;
		  DocOut<<k[i,j];
	        }
	        else 
                {
                  if ((i>=n/2) && (j>=abs(n-i)) && (j<=m-abs(n-i))) 
                  {
		    k[i,j]=n-i;DocOut<<k[i,j];
	          }
	          else 
                  {
                     if (j<m/2)
                     {
                        k[i,j]=j+1; DocOut<<k[i,j];
		     }
		     else 
                     {
                        k[i,j]=m-j;DocOut<<k[i,j];
		     };
		  };
	        };
	}
    DocOut<<endl;
}
DocIn.close();
DocOut.close();
delete []k;
system("pause");
return 0;
}
