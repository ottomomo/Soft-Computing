
#ifndef NEURONS_H
#define NEURONS_H

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <math.h>
#include"TreeMap.h"

typedef int Layer;

typedef struct {
	Layer layer;
	std::vector<float> in;	// vector of inputs
	std::vector<float> w;	// vector of weights
	std::vector<float> out;				// output
	float sw;				// sumatory of weighted inputs
	float deltaErr;			// error coefficient
} Neuron;

typedef struct Pattern
{
	std::vector<float> in;		//vector of inputs
	std::vector<float> z;		//vector of outputs expected
};

/* Neuron Constructor
	num: number of inputs of the neuron,
	layer: i-th layer that the neuron belongs
	np: number of patterns will store 
	baias: implemented with baias neuron
	@return: Neuron 
*/
Neuron createNeuron(int num, int layer, int np, bool baias) {
	Neuron n;
	n.layer = layer;
	n.in = std::vector<float>(num);
	if(baias)
		n.w = std::vector<float>(num + 1);	//w(inputs) + w(baias)
	else
		n.w = std::vector<float>(num);

	n.out = std::vector<float>(np);
	n.deltaErr = 0;
	n.sw = 0;
	return n;
}
/* Sigmoidal activation function
  @return: f(s) when d=true, f'(s) when d=false
*/
float fs(float s, bool d) { 
	return d ? (1 / (1 + exp(-s))) : (s * (1 - s ));
}

// Random initialization of neurons weights
void init_w(Neuron &n) {
	for (int i = 0; i < n.w.size(); ++i) {
		n.w[i] = ((float)rand() / (float)RAND_MAX) - 0.5; // RANGE: [-0.5 , 0.5] 
	}
}

class Network
{
public:
	Network() {}
	Network(int n) : neurons(n), nLayers(n) {}
	~Network();
	void addLayers(int n, int N_INPUTS, int N_HIDDENS, int N_OUTPUTS, Neuron n0, Neuron n1, Neuron n2);
	void initNw();

	int nLayers;
	std::vector<std::vector<Neuron>> neurons;
};

/*Network::Network() : nLayers(0)
{
}*/

Network::~Network()
{
}
/* Add all the layers and their respectives neurons of each layer to the network
	n: number of layers
	N_INPUTS: number of neurons in input layer
	N_HIDDENS: number of neurons in hidden layers
	N_OUTPUTS: number of neurons in output layer
	n0: neurons of input layer
	n1: neurons of hidden layers
	n2: neurons of output layer
*/
void Network::addLayers(int n, int N_INPUTS, int N_HIDDENS, int N_OUTPUTS, Neuron n0, Neuron n1, Neuron n2) {	
	std::vector<Neuron> in(N_INPUTS, n0);
	std::vector<Neuron> out(N_OUTPUTS, n2);
	neurons[0].resize(in.size());
	neurons[0]= in;
	neurons[n-1].resize(out.size());
	neurons[n-1] = out;
	for (int i = 1; i < n - 1; ++i) {
		n1.layer = i;
		std::vector<Neuron> hid(N_HIDDENS, n1);
		neurons[i].resize(hid.size());
		neurons[i] = hid;
		//neurons.insert(i, hid);
	}
}

// Random initialization of neurons weights
void Network::initNw() {
	for (int i = 1; i < nLayers; ++i) {
		for (int j = 0; j < neurons[i].size(); ++j) {
				init_w(neurons[i][j]);
		}
	}
}

class TrainningPatterns
{
public:
	TrainningPatterns(int n) : patterns(n)  { }
	TrainningPatterns() {}
	~TrainningPatterns() = default;
	void addPat(Pattern p);

	std::vector<Pattern>::iterator it;
	std::vector<Pattern> patterns;		//vector of training patterns
};

void TrainningPatterns::addPat(Pattern p) {
	it = patterns.end();
	patterns.insert(it, p);
}
#endif