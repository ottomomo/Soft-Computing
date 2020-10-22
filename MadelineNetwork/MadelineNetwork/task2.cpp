/*
	@author: Jose Luis Rocabado, Octavio Sales
*/
#include<stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <math.h>

/*number of templete patterns, horizontal resolution, vertical resolution, number of testing patterns*/
double n, p, q, m, c;
std::ifstream fin;

void madeline_setup(std::vector<char> &name, std::vector<std::vector<double>> &w)
{
	char curr_char;
	std::vector<int> count(n);
	std::string aux;
	for (int i = 0; i < n; i++)
	{
		count[i] = 0;
		fin >> name[i];
		std::getline(fin, aux);
		std::getline(fin, aux);
		for (int j = 0; j < m; j++)
		{
			fin >> curr_char;
			if (curr_char == '#')
			{
				w[i][j] = 1;
				count[i]++;
			}
			else if (curr_char == '-')
				w[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; ++j) {
			if (w[i][j] == 1) {
				w[i][j] = 1 / sqrt(count[i]);	//NORMALIZED
			}
		}
	}
	fin.close();			//CLOSE FILE
}
void madeline_test(std::vector<std::vector<double>> w, std::vector<std::vector<double>> x, std::vector<char> name)
{
	std::ofstream fout;
	fout.open("LogMadelineNet.txt");
	double r, value;
	int max;
	for (int z = 0; z < c; ++z) {
		value = 0;
		for (int i = 0; i < n; ++i) {
			r = 0;
			fout << z << " test pattern\n";
			for (int j = 0; j < m; ++j) {
				r += x[z][j] * w[i][j];
			}
			if (r > value) {
				max = i;
				value = r;
			}
			fout << "Neuron '" << name[i] << "' responded with the value: " << r << std::endl;
		}
		fout << "=> network has recognized letter '" << name[max] <<"' with level of confidence = " << value << std::endl << std::endl;
	}
	fout.close();
}

void getInput(std::vector<std::vector<double>> &x) {
	std::string aux;
	char curr_char;
	std::vector<int> count(c);
	for (int i = 0; i < 4; ++i) {
		std::getline(fin, aux);
	}
	for (int i = 0; i < c; ++i) {
		count[i] = 0;
		fin >> aux;
		std::getline(fin, aux);
		std::getline(fin, aux);
		for (int j = 0; j < m; j++)
		{
			fin >> curr_char;
			if (curr_char == '#')
			{
				x[i][j] = 1;
				count[i]++;
			}
			else if (curr_char == '-')
				x[i][j] = 0;
		}
	}
	for (int i = 0; i < c; i++)
	{
		for (int j = 0; j < m; ++j) {
			if (x[i][j] == 1) {
				x[i][j] = 1 / sqrt(count[i]);	//NORMALIZED
			}
		}
	}
	fin.close();		//CLOSE FILE
}

int main() 
{
	double j;
	fin.open("madeline_setup.txt");
	std::string aux;
	std::getline(fin, aux);
	fin >> j;
	n = j;			// NUMBER OF TEMPLATE PATTERNS
	std::getline(fin, aux);
	fin >> j;
	p = j;			//HORIZONTAL RESOLUTION
	std::getline(fin, aux);
	fin >> j;
	q = j;			//VERTICAL RESOLUTION
	std::getline(fin, aux);
	m = q * p;		// SIZE OF CHARACTER RESOLUTION
	std::vector<char> name(n);		// VECTOR OF CHARACTERS
	std::vector<std::vector<double>> w(n, std::vector<double>(m)); //Matrix of templete patterns
	madeline_setup(name, w);
	fin.open("recognitiontest.txt");
	fin >> j;
	c = j;			// NUMBER OF INPUT CHARACTERS
	std::vector<std::vector<double>> x(c, std::vector<double>(m)); //Mattrix of input characters
	getInput(x);
	madeline_test(w,x, name);
	system("PAUSE");

	return 0;
}