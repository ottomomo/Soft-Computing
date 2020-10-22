#ifndef NETWORKS_H
#define NETWORKS_H

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <math.h>


class Neuron {
public:
	std::vector<float> in;	//vector of inputs
	std::vector<float> out;	//vector of outputs
	std::vector<float> w;	//vector of weights
	float sw;		//sumatory of weighted outputs
	float deltaErr;	// error coefficient

	//number of inputs, weights, outputs
	Neuron(int ni, int nw, int no) : in(ni), w(nw), out(no), sw(0), deltaErr(0){ }
	Neuron(const Neuron &n) : in(n.in), w(n.w), out(n.out), sw(n.sw), deltaErr(n.deltaErr) {}
	~Neuron() = default;

	void init_w() {
		for (int i = 0; i < w.size(); ++i)
			w[i] = ((float)rand() / (float)RAND_MAX) - 0.5; // RANGE: [-0.5 , 0.5] 
	}
};

class Layer
{
public:
	std::vector<Neuron> neurons;	//vector of Neurons
	bool fun;						//activation function flag

	Layer(int num, bool f, Neuron n);
	Layer(const Layer &l);
	~Layer() = default;

	float actvFun(float sw) {
		if (fun)
			return (1 / (1 + pow(exp(1), -sw)));
		else
			return sw;
	}
	
	void addNeurons(int ni, int nw, int no) {
		Neuron n( ni,  nw,  no);
		for(int i=0;i<neurons.size();++i){
			neurons[i] = n;
		}
	}
};

Layer::Layer(int num, bool f, Neuron n) : neurons(num), fun(f) {
	neurons.assign(num, n);
}

Layer::Layer(const Layer &l) : neurons(l.neurons), fun(l.fun) {}

class Network
{
public:
	std::vector<Layer>layers;

	Network(int n, int N_INPUTS, int N_HIDDENS, int N_OUTPUTS, Neuron n0, Neuron n1, Neuron n2) : layers(n) {
		 Layer l(N_INPUTS, false, n0);
		 Layer l2(N_OUTPUTS, true, n2);
		 Layer l1(N_HIDDENS, true, n1);
		/*layers[0] = l;
		layers[n - 1] = l2;
		for (int i = 1; i < n - 1; ++i) {
			layers[i] = l1;
		}*/
		std::vector<Layer>::iterator it;
		it = layers.begin();
		it = layers.insert(it, l2);
		it=layers.insert(it, n-2, l1);
		layers.insert(it,l);
	}
	Network(int n) : layers(n) {}
	~Network() = default;
	
	/*void addLayer(int n, bool f) {
		Layer l(n,f);
		for(int i=0;i<layers.size();++i){
			layers[i]=l;
		}
	}*/
};

class TrainningPattern
{
public:
	TrainningPattern(int ni, int nz) : in(ni), z(nz) { }
	~TrainningPattern()= default;

	std::vector<float> in;		//vector of inputs
	std::vector<float> z;		//vector of outputs expected
};
#endif	//NETWORKS_H
