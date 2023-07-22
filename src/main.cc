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

// assert(n.GetValue() == 0);
// n.SetValue(5);
// n2.AddConnection(n, 5);
// n2.ProcessData();
// assert(n2.GetValue() == n2.GetConnections().at(0).second * n.GetValue() + n2.GetBias());
// n3.AddConnection(n2, -0.1);

// array<array<double>> convertData(array<double> input){
//   array<array<double>> output{1};
//   for(int i = 0; i < input.size(); i++){
//     array<double> temp{1};
//     temp[0] = input[i];
//     output[i] = temp;
//   }
//   return output;
// }


int MAX_INT = ~(1 << 31);
int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    throw std::invalid_argument("Not right amount of args");
  }

  int runs = std::stoi(static_cast<std::string>(argv[1]));

  int nLayers = 2;

  array<double> trainData{100};
  for (int i = 0; i < trainData.size(); i++)
  {
    trainData[i] = (i);
  }

  long long s_t = now();

  NeuralNetwork nn = NeuralNetwork();
  NeuralLayer layer1 = NeuralLayer(1, WeightGenerationType::FIXED);
  NeuralLayer layer2 = NeuralLayer(500, WeightGenerationType::FIXED);
  NeuralLayer layer3 = NeuralLayer(500, WeightGenerationType::FIXED);
  NeuralLayer layer4 = NeuralLayer(500, WeightGenerationType::FIXED);
  NeuralLayer layer5 = NeuralLayer(1, WeightGenerationType::FIXED);
  layer1.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer2.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer3.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer4.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer5.SetActivationFunction(ActivationFunction(ActivationFunctionType::LINEAR, std::map<std::string, double>{{"slope", 1}}));

  nn(layer1)(layer2)(layer3)(layer4)(layer5);
  nn.Build();
  for(int i = 0; i < trainData.size(); i++){
    std::cout << "Input: " << trainData.at(i) << "\tOutput: " << nn(trainData[0])[0] << std::endl;
  }

  long long e_t = now();
  std::cout << "Completion time:\t" << (e_t - s_t) / 1e6 << std::endl; 
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