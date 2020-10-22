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
#define NU 0.1			//number nu 
#define K 10000			//number of epochs
#define BAIAS 1			// implemented with baias neuron... or not.


void updateW(Network &net, int np, bool baias) {
	for (int z = 1; z < N_LAYERS; ++z) {
		for (int i = 0; i < net.neurons[z].size(); ++i) {
			for (int j = 0; j < net.neurons[z][i].w.size(); ++j) {
				if(baias && j == net.neurons[z][i].w.size()-1)
				net.neurons[z][i].w[j] = 
					net.neurons[z][i].w[j] + NU * net.neurons[z][i].deltaErr;
				else
					net.neurons[z][i].w[j] =
					net.neurons[z][i].w[j] + NU * net.neurons[z][i].deltaErr * net.neurons[z - 1][j].out[np];
			}
		}
	}
}


void setInput(Network &net, Pattern pattern,int np) {
	for (int i = 0; i < N_INPUTS; ++i) {
		net.neurons[0][i].out[np] = pattern.in[i];
	}
}

void backPropagationMethod(Network &net, Pattern pattern, int np) {
	float err;
	for (int z = N_LAYERS - 1; z > 0; --z) {
		for (int i = 0; i < net.neurons[z].size(); ++i) {
			if (z < N_LAYERS - 1) {	//hidden layers:
				err = 0;
				for (int j = 0; j < N_OUTPUTS; ++j) {
					err += net.neurons[z+1][j].w[i] * net.neurons[z + 1][j].deltaErr;	
				}
				net.neurons[z][i].deltaErr = err * fs(net.neurons[z][i].out[np], false);	// delta error(1)
			}
			else {					// output layer:
				net.neurons[z][i].deltaErr = 
					fs(net.neurons[z][i].out[np], false) * (pattern.z[i] - net.neurons[z][i].out[np]); // delta error(2)
			}
		}
	}

}
/* calculate the output of the network
	net: Netowrk
	np: i-th pattern 
	baias: baias neuron
*/
void propagate(Network &net, int np, bool baias) {
	for (int i = 1; i < N_LAYERS; ++i) {
		for (int j = 0; j < net.neurons[i].size(); ++j) {
			net.neurons[i][j].sw = 0;
			for (int z = 0; z < net.neurons[i][j].in.size(); ++z) {
				net.neurons[i][j].in[z] = net.neurons[i-1][z].out[np];
				net.neurons[i][j].sw += net.neurons[i][j].w[z] * net.neurons[i][j].in[z];	//* s
			}
			if (baias) {
				net.neurons[i][j].sw += net.neurons[i][j].w[net.neurons[i][j].w.size()-1];
			}
			net.neurons[i][j].out[np] = fs(net.neurons[i][j].sw, true);//**	f(s) 
		}
	}
}
/* performs just one epoch of the training
*/
void training(Network &net, Pattern pattern, int np) {
	setInput(net, pattern, np);					//STEP 1
	propagate(net, np, BAIAS);					//STEP 2
	backPropagationMethod(net, pattern, np);	//STEP 3
	updateW(net, np, BAIAS);					//STEP 4
}

void setTraining(Network &net, TrainningPatterns p) {
	bool solved = false;
	int i = 0;
	net.initNw();							//STEP 0
	while (!solved && (i < K*N_PATTERNS)) {			
		training(net, p.patterns[i%N_PATTERNS], i%N_PATTERNS);
		i++;
	}
	for (int i = 0; i < N_PATTERNS; ++i) {
		std::cout << "Pattern " << i << std::endl;
		std::cout << "expected out: " << p.patterns[i].z[0] << ", " << p.patterns[i].z[1] << ", " << p.patterns[i].z[2] << ", " << p.patterns[i].z[3] << std::endl;
		std::cout << "network out :" << net.neurons[N_LAYERS-1][0].out[i % N_PATTERNS] << ", " << net.neurons[N_LAYERS - 1][1].out[i % N_PATTERNS] << ", " << net.neurons[N_LAYERS - 1][2].out[i % N_PATTERNS] << ", " << net.neurons[N_LAYERS - 1][3].out[i % N_PATTERNS] << std::endl;
		std::cout << "hidden neurons out :" << net.neurons[1][0].out[i % N_PATTERNS] << ", " << net.neurons[1][1].out[i % N_PATTERNS] << std::endl;
	}
}

int main() {
	/* Network Creation */
	Network net(N_LAYERS);
	Neuron n0 = createNeuron(N_INPUTS, 0, N_PATTERNS, 0);
	Neuron n1 = createNeuron(N_INPUTS, 1, N_PATTERNS, BAIAS);
	Neuron n2 = createNeuron(N_HIDDENS, N_LAYERS - 1, N_PATTERNS, BAIAS);
	net.addLayers(N_LAYERS, N_INPUTS,  N_HIDDENS,  N_OUTPUTS,  n0,  n1,  n2);
	/* Patterns */
	TrainningPatterns patterns;
	std::ifstream in("patterns.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::string aux;
	float a;
	std::getline(in, aux);
	for (int i = 0; i < N_PATTERNS; ++i) {					//READ PATTERNS
		Pattern p;
		p.in = std::vector<float>(N_INPUTS);
		p.z = std::vector<float>(N_OUTPUTS);
		for (int j = 0; j < N_INPUTS; ++j) {
			std::cin >> a;
			p.in[j] = a;
		}
		std::cin >> aux;
		for (int j = 0; j < N_OUTPUTS; ++j) {
			std::cin >> a;
			p.z[j] = a;
		}
		patterns.addPat(p);
	}
	setTraining(net,patterns);

	system("PAUSE");
	return 0;
}