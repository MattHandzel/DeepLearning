#ifndef NEURALNETWORK
#define NEURALNETWORK

#include "NeuralLayer.h"
#include "utils.h"
struct RunData
{
  double error;
};

class NeuralNetwork
{
public:
  NeuralNetwork();
  NeuralNetwork& operator()(NeuralLayer layer);
  array<double> operator()(array<double> input);
  array<double> NeuralNetwork::operator()(double _input);
  void Train(array<array<double>> trainData, array<array<double>> trainLabels, int epochs, int nThreads, int verbose = 0);
  int GetSize();
  void Build();
private:
  std::vector<NeuralLayer> m_layers;
  bool isBuilt = false;
};

#endif