#include "Neuron.h"
#include "NeuralLayer.h"
#include <iostream>
#include "utils.h"
#include <future>
#include "NeuralNetwork.h"
#include <set>

// Neuron n = Neuron(10);
// Neuron n2 = Neuron(5);
// Neuron n3 = Neuron(-10);

// n3.SetActivationFunction(ActivationFunction::sigmoid);

// assert(n.m_value == 0);
// n.SetValue(5);
// n2.AddConnection(n, 5);
// n2.ProcessData();
// assert(n2.m_value == n2.GetConnections().at(0).second * n.m_value + n2.GetBias());
// n3.AddConnection(n2, -0.1);
std::vector<std::vector<double>> convertData(std::vector<double> input){
  std::vector<std::vector<double>> output;
  for(int i = 0; i < input.size(); i++){
    output.push_back(std::vector<double>{input.at(i)});
  }
  return output;
}

int MAX_INT = ~(1 << 31);
int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    throw std::invalid_argument("Not right amount of args");
  }

  int runs = std::stoi(static_cast<std::string>(argv[1]));

  int nLayers = 2;

  std::vector<double> trainData;
  for (int i = 0; i < 100; i++)
  {
    trainData.push_back(i);
  }
  std::cout << "hello " << std::endl;

  long long s_t = now();

  NeuralNetwork nn = NeuralNetwork();
  NeuralLayer layer1 = NeuralLayer(1, WeightGenerationType::RANDOM);
  NeuralLayer layer2 = NeuralLayer(500, WeightGenerationType::RANDOM);
  NeuralLayer layer3 = NeuralLayer(500, WeightGenerationType::RANDOM);
  NeuralLayer layer4 = NeuralLayer(500, WeightGenerationType::RANDOM);
  NeuralLayer layer5 = NeuralLayer(1, WeightGenerationType::RANDOM);
  layer1.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer2.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer3.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer4.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer5.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));

  nn(layer1)(layer2)(layer3)(layer4)(layer5);
  nn.Build();
  for(int i = 0; i < trainData.size(); i++){
    std::cout << "Input: " << trainData.at(i) << "\tOutput: " << nn(trainData[i])[0] << std::endl;
  }
  std::cout << trainData.size();

  long long e_t = now();
  std::cout << "Completion time:\t" << (e_t - s_t) / 1e6 << std::endl;   std::vector<double> trainLabels{-5, 0, -5, 4, 2.5, 9, 9}; //{0, , 0, 1, 0, 1, 0, 1, 0};
  return 0;
}
// 1.3 s -> no multithreading; 0.6 -> threading
// Best error was 6.74691 and it took 14934.6 milliseconds
/*
Best error was 1.87233 and it took 16286 milliseconds
Input:  0       Output: -0.0284443
Input:  1       Output: 1.77687
Input:  2       Output: 3.58219
Input:  3       Output: 7.09013
Input:  4       Output: 13.3834
Input:  5       Output: 25.5395
Input:  6       Output: 37.6955
Input:  7       Output: 50.3095
Input:  8       Output: 65.0485
Input:  9       Output: 79.7874
*/

// make -> 36ms