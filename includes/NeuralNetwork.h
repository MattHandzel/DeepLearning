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
  std::vector<double> operator()(std::vector<double> input);
  std::vector<double> NeuralNetwork::operator()(double _input);
  void Train(std::vector<std::vector<double>> trainData, std::vector<std::vector<double>> trainLabels, int epochs, int nThreads, int verbose = 0);
  int GetSize();
  void Build();
private:
  std::vector<NeuralLayer> m_layers;
  bool isBuilt = false;
};

#endif