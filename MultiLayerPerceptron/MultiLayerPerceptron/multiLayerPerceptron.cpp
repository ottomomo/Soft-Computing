/*
	@author: Jose Luis Rocabado, Octavio Sales
	@brief: implementation of multi layer perceptron network

#include "Networks.h"
#include "Neurons.h"
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <math.h>

#define N_PATTERNS 4	//number of trainning patterns
#define N_LAYERS 3		//number of layers in the network
#define N_INPUTS 4		//number of neurons in input layer
#define N_HIDDENS 2		//number of neurons in hidden layer
#define N_OUTPUTS 4		//number of neurons in output layer
#define NU 0.000001		//number nu
#define K 10000			//number of epochs

bool isSolution(Network net, TrainningPattern patterns) {
		for (int j = 0; j < N_OUTPUTS; ++j) {
			if (net.layers[N_LAYERS - 1].neurons[j].out[0] != patterns.z[j])
				return false;
		}
		return true;
}

void updateW(Network &net) {
	for (int z = 1; z < N_LAYERS - 1; ++z) {
		for (int i = 0; i < net.layers[z].neurons.size(); ++i) {
			for (int j = 0; j < N_OUTPUTS; ++j) {
				net.layers[z].neurons[i].w[j] = net.layers[z].neurons[i].w[j] + NU * net.layers[z].neurons[i].deltaErr *net.layers[z - 1].neurons[j].out[0];
			}
		}
	}
}

void backPropagationMethod(Network &net, TrainningPattern pattern) {
	//output layer
	for (int i = 0; i < N_OUTPUTS; ++i) {
		net.layers[N_LAYERS - 1].neurons[i].deltaErr = 
			net.layers[N_LAYERS - 1].actvFun(net.layers[N_LAYERS - 1].neurons[i].sw) * 
			(pattern.z[i] - net.layers[N_LAYERS - 1].neurons[i].out[0]);
	}
	float err;
	//hidden layers
	for (int z = N_LAYERS - 2; z > 0; --z) {
		for (int i = 0; i < N_HIDDENS; ++i) {
			err = 0;
			for (int j = 0; j < N_OUTPUTS; ++j) {
				err += net.layers[z].neurons[i].w[j] * net.layers[z + 1].neurons[j].deltaErr;
			}
			net.layers[z].neurons[i].deltaErr = err;
		}
	}

}
void propagate(Network &net) {
	for (int i = 1; i < N_LAYERS; ++i) {
		for (int j = 0; j < N_INPUTS; ++j) {
			for (int z = 0; z < N_HIDDENS; ++z) {
				net.layers[i].neurons[z].in[j] = net.layers[i-1].neurons[j].out[0];
				net.layers[i].neurons[z].out[j] = net.layers[i].neurons[z].in[j];
				net.layers[i].neurons[z].sw += net.layers[i].neurons[z].w[j] * net.layers[i].neurons[z].in[j];
			}
		}
	}
	for (int j = 0; j < N_OUTPUTS; ++j) {
		for (int z = 0; z < N_HIDDENS; ++z) {
			net.layers[N_LAYERS-1].neurons[j].in[z] = net.layers[1].neurons[z].out[0];
			net.layers[N_LAYERS-1].neurons[j].out[z] = net.layers[2].neurons[j].in[z];
			net.layers[N_LAYERS-1].neurons[j].sw += net.layers[2].neurons[j].w[z] * net.layers[2].neurons[j].in[z];
		}
	}
}

void setInput(Network &net, TrainningPattern pattern) {
	for (int i = 0; i < N_INPUTS; ++i) {
		net.layers[0].neurons[i].out[0] = pattern.in[i];
	}
}

void training(Network &net, TrainningPattern pattern, bool &sol) {
	setInput(net, pattern);					//STEP 1
	propagate(net);							//STEP 2
	backPropagationMethod(net, pattern);	//STEP 3
	updateW(net);							//STEP 4
}

bool finished(bool marks []) {
	for (int i = 0; i < N_PATTERNS; ++i) {
		if (!marks[i])
			return false;
	}
	return true;
}
void SetTraining(Network &net, std::vector<TrainningPattern> patterns) {
	bool solved = false;
	int i = 0;
	bool marks[N_PATTERNS];
	while (!solved && (i < N_PATTERNS)) {
		training(net, patterns[i % N_PATTERNS], solved);
		if (isSolution(net, patterns[i % N_PATTERNS])) {
			marks[i % N_PATTERNS] = true;
			if (finished(marks))
				solved = true;
		}
		i++;
	}
	std::cout << "Trainned!\n";
}

int main() {
	std::vector<TrainningPattern> patterns(N_PATTERNS);		//PATTERNS
	/*Neuron inN(1,0,1);										//Input Neuron
	Neuron hiN(N_INPUTS, N_INPUTS, 1);
	Neuron outN(N_HIDDENS, N_HIDDENS, 1);
	Network net(N_LAYERS, N_INPUTS, N_HIDDENS, N_OUTPUTS, inN,hiN,outN);			//NETWORK
	net.layers[0] = Layer(N_INPUTS, false);					//INPUT LAYER
	for (int i = 0; i < N_INPUTS; ++i) {
		net.layers[0].neurons[i] = Neuron(1, 0, 1);
	}
	net.layers[N_LAYERS-1] = Layer(N_OUTPUTS, true);		//OUTPUT LAYER
	for (int i = 0; i < N_OUTPUTS; ++i) {
		net.layers[N_LAYERS-1].neurons[i] = Neuron(N_HIDDENS, N_HIDDENS, 1);
		net.layers[N_LAYERS - 1].neurons[i].init_w();		//**STEP 0**
	}
	for (int i = 1; i < N_LAYERS - 1; ++i) {
		net.layers[i] = Layer(N_HIDDENS, true);				//HIDDENS LAYERS
		for (int j = 0; j < N_HIDDENS; ++j) {
			net.layers[i].neurons[j] = Neuron(N_INPUTS, N_INPUTS, 1);
			net.layers[i].neurons[j].init_w();				//**STEP 0**
		}
	}
	Network n
	std::ifstream in("patterns.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	//std::cin.rdbuf(in.rdbuf());
	std::string aux;
	float a;
	std::getline(in, aux);
	for (int i = 0; i < N_PATTERNS; ++i) {					//READ PATTERNS
		patterns[i] = TrainningPattern(N_INPUTS, N_OUTPUTS);
		for (int j = 0; j < N_INPUTS; ++j) {
			std::cin >> a;
			patterns[i].in[j]=a;
		}
		std::cin >> aux;
		for (int j = 0; j < N_OUTPUTS; ++j) {
			std::cin >> a;
			patterns[i].z[j]=a;
		}
	}

	system("PAUSE");
	return 0;
}*/