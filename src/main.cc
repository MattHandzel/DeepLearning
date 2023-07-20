#include "Neuron.h"
#include "NeuralLayer.h"
#include <iostream>
#include "utils.h"
#include <future>
// Neuron n = Neuron(10);
// Neuron n2 = Neuron(5);
// Neuron n3 = Neuron(-10);

// n3.SetActivationFunction(ActivationFunction::sigmoid);

// assert(n.GetValue() == 0);
// n.SetValue(5);
// n2.AddConnection(n, 5);
// n2.ProcessData();
// assert(n2.GetValue() == n2.GetConnections()[0].second * n.GetValue() + n2.GetBias());
// n3.AddConnection(n2, -0.1);

NeuralLayer layer = NeuralLayer(1);
NeuralLayer layer2 = NeuralLayer(5);
NeuralLayer layer3 = NeuralLayer(5);
NeuralLayer output = NeuralLayer(1);
struct RunData
{
  double error;
  double*** weights{};
  ActivationFunction* functions{};
  double** biases{};
};

RunData runRun(double trainData[], double trainLabels[], RunData bestRun)
{
  // n3.ProcessData();
  NeuralLayer layer = NeuralLayer(1);
  NeuralLayer layer2 = NeuralLayer(5);
  NeuralLayer layer3 = NeuralLayer(5);
  NeuralLayer output = NeuralLayer(1);
  layer.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  output.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer2.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", 100}}));
  layer3.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", 100}}));

  layer2.ConnectLayer(&layer, generateWeights(layer2, layer, WeightGenerationType::RANDOM, 1));
  layer3.ConnectLayer(&layer2, generateWeights(layer3, layer2, WeightGenerationType::RANDOM, 1));

  output.ConnectLayer(&layer3, generateWeights(output, layer2, WeightGenerationType::FIXED, 1));


  RunData currentRun;
  currentRun.error = 0;

  currentRun.functions[0] = (ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", generateRandomNumber(10, -10)}}));
  currentRun.functions[1] = (ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", generateRandomNumber(10, -10)}}));
  currentRun.weights[0] = (generateWeights(layer2, layer, WeightGenerationType::RANDOM));
  currentRun.weights[1] = (generateWeights(layer3, layer2, WeightGenerationType::RANDOM));

  currentRun.biases[0] = (generateRandomNumbers(layer2.GetLayerSize(), 10, -10));
  currentRun.biases[1] = (generateRandomNumbers(layer3.GetLayerSize(), 10, -10));

  layer2.SetActivationFunction(currentRun.functions[0]);
  layer3.SetActivationFunction(currentRun.functions[1]);

  layer2.SetWeights(currentRun.weights[0]);
  layer3.SetWeights(currentRun.weights[1]);

  layer2.SetBiases(currentRun.biases[0]);
  layer3.SetBiases(currentRun.biases[1]);

  for (int i = 0; i < sizeof(trainData) / sizeof(trainData[0]); i++)
  {
    layer.SetInput(new double{trainData[i]});
    layer2.ProcessLayer();
    layer3.ProcessLayer();
    output.ProcessLayer();

    currentRun.error += computeError(trainLabels[i], output.GetNeurons()[0].GetValue()) / (sizeof(trainData) / sizeof(trainData[0]));
    if(currentRun.error > bestRun.error){
      return bestRun;
    }
  }
  return currentRun;
}

RunData runRuns(int nRuns, double trainData[], double trainLabels[])
{
  RunData bestRun;
  bestRun.error = 14214124214124124.;

  for (int i = 0; i < nRuns; i++)
  {
    RunData cur = runRun(trainData, trainLabels, bestRun);
    if (cur.error < bestRun.error)
    {
      bestRun = cur;
    }
  }
  return bestRun;
}

int MAX_INT = ~(1 << 31);
int main(int argc, char *argv[])
{

  if (argc != 2)
  {
    throw std::invalid_argument("Not right amount of args");
  }

  int runs = std::stoi(static_cast<std::string>(argv[1]));

  RunData bestRun;

  int nLayers = 2;
  int dataSize = 10;

  double trainData[dataSize];
  for (int i = 0; i < dataSize; i++)
  {
    trainData[i] = (i);
  }

  double trainLabels[dataSize]; //{0, , 0, 1, 0, 1, 0, 1, 0};
  for (int i = 0; i < 10; i++)
  {
    trainLabels[i] = (pow(trainData[i], 2));
  }
  layer.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  output.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer2.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", 100}}));
  layer3.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", 100}}));

  layer2.ConnectLayer(&layer, generateWeights(layer2, layer, WeightGenerationType::RANDOM, 1));
  layer3.ConnectLayer(&layer2, generateWeights(layer3, layer2, WeightGenerationType::RANDOM, 1));
  return 0;

  output.ConnectLayer(&layer3, generateWeights(output, layer2, WeightGenerationType::FIXED, 1));
  double*** currentWeights;
  ActivationFunction* currentFunctions;
  double** currentBiases;

  long long s_t = now();

  bestRun.error = static_cast<double>(MAX_INT);
  int n_threads = 6;
  std::vector<std::promise<RunData>> promises;
  std::vector<std::future<RunData>> futures;
  std::vector<std::thread> threads;

  // for (int i = 0; i < n_threads; i++)
  // {
  //   promises.push_back(std::promise<RunData>());
  //   futures.push_back(promises[i].get_future());
  //   threads.push_back(std::thread([&promises, trainData, trainLabels, i, runs, n_threads]()
  //                                 {
  //       RunData result = runRuns(runs / n_threads, trainData, trainLabels);
  //       promises[i].set_value(result); }));

  // }

  // for (int i = 0; i < n_threads; i++)
  // {
  //   RunData result = futures[i].get();
  //   if (result.error < bestRun.error)
  //   {
  //     bestRun = result;
  //     // std::cout << "Run " << runNumber << " had an error of " << currentRun.error << std::endl;
  //   }
  // }
  bestRun = runRuns(runs, trainData, trainLabels);

  long long e_t = now();
  std::cout << "Best error was " << bestRun.error << " and it took " << (e_t - s_t) / 1e6 << " milliseconds" << std::endl;
  currentWeights = bestRun.weights;
  layer2.SetWeights(currentWeights[0]);
  layer3.SetWeights(currentWeights[1]);

  layer2.SetActivationFunction(bestRun.functions[0]);
  layer3.SetActivationFunction(bestRun.functions[1]);

  layer2.SetBiases(bestRun.biases[0]);
  layer3.SetBiases(bestRun.biases[1]);
  double testError = 0;
  for (int i = 0; i < dataSize; i++)
  {
    layer.SetInput(new double{trainData[i]});
    layer2.ProcessLayer();
    layer3.ProcessLayer();
    output.ProcessLayer();
    testError += computeError(trainLabels[i], output.GetNeurons()[0].GetValue()) / dataSize;
    std::cout << "Input:\t" << trainData[i] << "\tOutput:\t" << output.GetNeurons()[0].GetValue() << std::endl;
  }
  // assert(testError == bestRun.error);
  // for(int i = 0; i < n_threads; i++){
  //   threads[i].join();

  // }
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