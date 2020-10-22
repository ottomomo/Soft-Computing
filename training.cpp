#include<stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>

#define NU 0,2 

int static pat=2;


 float init_w(){
	return((float)rand())/(float)RAND_MAX;
}

void training(){
	float x[2];
	float w[2];
	float z;
	float y=0;
	int k=0;
	std::string aux;
	 for(int i=0;i<=pat;++i)
		 std::cin >> aux;
	  for(int i=0;i<pat;++i)
		std::cin >> x[i];
		std::cin >> z;
	   for(int i=0;i<pat;++i)
		   w[i]=init_w();
	   while(k<pat){
			for(int i=0;i<pat;i++)	
				y += x[i]*w[i];						//STEP 5
		    for(int i=0;i<pat;i++)
				w[i]= w[i]+ NU*(z-y)*x[i];			//STEP 6
			k++;
	   }
}
int main(){
	//FILE *fich;
	//fich=fopen("C:\Users\student\AppData\Local\Microsoft\Windows\INetCache\IE\LLONXNI0\lab\patterns1.txt", r);
	 std::ifstream in("C:\Users\student\Desktop\ery\Lab1\lab\patterns1.txt");
     //auto cinbuf = std::cin.rdbuf(in.rdbuf());
	  std::cin.rdbuf(in.rdbuf());
	 
	 std::string aux;
	 //fscanf
	 int j;
	 for(int i=0;i<2;++i){
		std::cin >> aux;
		std::cout << aux << std::endl;
	 }
	std::cin >> j;
	pat=j;
	while(!j){
		training();
		--j;
	}

	 // std::cin.rdbuf(cinbuf);
      system("PAUSE");

	return 0;


}