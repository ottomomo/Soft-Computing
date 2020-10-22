#include<stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
/*
#define NU 0.000001 
#define K 10000

int static pat;


float init_w() {
	return(float)rand() / (float)RAND_MAX;
}

void training(int pat, float &y, std::vector<float> x, std::vector<float> &w, float z ) {
	int k = 0;
	while (k < K) {
		for (int i = 0; i < pat; i++)
			y += x[i] * w[i];						//STEP 5
		for (int i = 0; i < pat; i++)
			//w[i] = w[i]+(NU * (z - y)*x[i]);			//STEP 6
		
		k++;
	}

}

int main() {
	std::ifstream in("patterns1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::cin.rdbuf(in.rdbuf());

	std::string aux;
	int j;
	for (int i = 0; i < 2; ++i) {
		std::cin >> aux;
		std::cout << aux << std::endl;
	}
	std::cin >> j;
	pat = j;
	float y = 0;
	std::vector<float> x(pat);
	std::vector<float> w(pat);
	for (int i = 0; i <= pat + 1; ++i)
		std::cin >> aux;
	for (int i = 0; i < pat; ++i)
		std::cin >> x[i];
	float z;
	std::cin >> z;
	for (int i = 0; i < pat; ++i)
		w[i] = 0.09;			//step 3
	while (j>0) {
		training(pat, y, x, w, z);
		for (int i = 0; i < pat; ++i)
			std::cin >> x[i];
		std::cin >> z;
		--j;
	}
	for (int i = 0; i < pat; i++)
		std::cout << w[i] << " ";
	std::cin.rdbuf(cinbuf);
	system("PAUSE");

	return 0;


}*/