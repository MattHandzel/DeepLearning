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
// assert(n2.GetValue() == n2.GetConnections().at(0).second * n.GetValue() + n2.GetBias());
// n3.AddConnection(n2, -0.1);

NeuralLayer layer = NeuralLayer(1);
NeuralLayer layer2 = NeuralLayer(3);
NeuralLayer layer3 = NeuralLayer(3);
NeuralLayer output = NeuralLayer(1);
struct RunData
{
  double error;
  std::vector<std::vector<std::vector<double>>> weights{};
  std::vector<ActivationFunction> functions{};
  std::vector<std::vector<double>> biases{};
};

RunData runRun(std::vector<double> trainData, std::vector<double> trainLabels, RunData bestRun)
{
  // n3.ProcessData();
  NeuralLayer layer = NeuralLayer(1);
  NeuralLayer layer2 = NeuralLayer(3);
  NeuralLayer layer3 = NeuralLayer(3);
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
  currentRun.weights.clear();
  currentRun.functions.clear();
  currentRun.biases.clear();

  currentRun.functions.push_back(ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", generateRandomNumber(2, -2)}}));
  currentRun.functions.push_back(ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", generateRandomNumber(2, -2)}}));
  currentRun.weights.push_back(generateWeights(layer2, layer, WeightGenerationType::RANDOM));
  currentRun.weights.push_back(generateWeights(layer3, layer2, WeightGenerationType::RANDOM));

  currentRun.biases.push_back(generateRandomNumberVector(layer2.GetLayerSize(), 2, -2));
  currentRun.biases.push_back(generateRandomNumberVector(layer3.GetLayerSize(), 2, -2));

  assert(currentRun.weights.size() == 2);

  layer2.SetActivationFunction(currentRun.functions.at(0));
  layer3.SetActivationFunction(currentRun.functions.at(1));

  layer2.SetWeights(currentRun.weights.at(0));
  layer3.SetWeights(currentRun.weights.at(1));

  layer2.SetBiases(currentRun.biases.at(0));
  layer3.SetBiases(currentRun.biases.at(1));

  for (int i = 0; i < trainData.size(); i++)
  {
    layer.SetInput(std::vector<double>{trainData.at(i)});
    layer2.ProcessLayer();
    layer3.ProcessLayer();
    output.ProcessLayer();

    currentRun.error += computeError(trainLabels.at(i), output.GetNeurons().at(0).GetValue()) / trainData.size();
    if(currentRun.error > bestRun.error){
      return bestRun;
    }
  }
  return currentRun;
}

RunData runRuns(int nRuns, std::vector<double> trainData, std::vector<double> trainLabels)
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

  std::vector<double> trainData{0, 1, 3, 4, 6, 8, 10};
  // for (int i = 0; i < 10; i++)
  // {
  //   trainData.push_back(i);
  // }

  std::vector<double> trainLabels{-5, 0, -5, 4, 2.5, 9, 9}; //{0, , 0, 1, 0, 1, 0, 1, 0};
  // for (int i = 0; i < trainData.size(); i++)
  // {
  //   trainLabels.push_back(pow(trainData.at(i), 2));
  // }
  layer.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  output.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::LINEAR, std::map<std::string, double>{{"slope", 1}}));
  layer2.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", 100}}));
  layer3.SetActivationFunction(ActivationFunction(ActivationFunctionTypes::RELU, std::map<std::string, double>{{"slope", 1}, {"x-intercept", 100}}));

  layer2.ConnectLayer(&layer, generateWeights(layer2, layer, WeightGenerationType::RANDOM, 1));
  layer3.ConnectLayer(&layer2, generateWeights(layer3, layer2, WeightGenerationType::RANDOM, 1));

  output.ConnectLayer(&layer3, generateWeights(output, layer2, WeightGenerationType::FIXED, 1));

  std::vector<std::vector<std::vector<double>>> currentWeights;
  std::vector<ActivationFunction> currentFunctions;
  std::vector<std::vector<double>> currentBiases;

  long long s_t = now();

  bestRun.error = static_cast<double>(MAX_INT);
  int n_threads = 6;
  std::vector<std::promise<RunData>> promises;
  std::vector<std::future<RunData>> futures;
  std::vector<std::thread> threads;

  for (int i = 0; i < n_threads; i++)
  {
    promises.push_back(std::promise<RunData>());
    futures.push_back(promises.at(i).get_future());
    threads.push_back(std::thread([&promises, trainData, trainLabels, i, runs, n_threads]()
                                  {
        RunData result = runRuns(runs / n_threads, trainData, trainLabels);
        promises.at(i).set_value(result); }));

  }

  for (int i = 0; i < n_threads; i++)
  {
    RunData result = futures.at(i).get();
    if (result.error < bestRun.error)
    {
      bestRun = result;
      // std::cout << "Run " << runNumber << " had an error of " << currentRun.error << std::endl;
    }
  }
  // bestRun = runRuns(runs, trainData, trainLabels);

  long long e_t = now();
  std::cout << "Best error was " << bestRun.error << " and it took " << (e_t - s_t) / 1e6 << " milliseconds" << std::endl;
  currentWeights = bestRun.weights;
  layer2.SetWeights(currentWeights.at(0));
  layer3.SetWeights(currentWeights.at(1));

  layer2.SetActivationFunction(bestRun.functions.at(0));
  layer3.SetActivationFunction(bestRun.functions.at(1));

  layer2.SetBiases(bestRun.biases.at(0));
  layer3.SetBiases(bestRun.biases.at(1));
  double testError = 0;
  for (int i = 0; i < trainData.size(); i++)
  {
    layer.SetInput(std::vector<double>{trainData.at(i)});
    layer2.ProcessLayer();
    layer3.ProcessLayer();
    output.ProcessLayer();
    testError += computeError(trainLabels.at(i), output.GetNeurons().at(0).GetValue()) / trainData.size();
    std::cout << "Input:\t" << trainData.at(i) << "\tOutput:\t" << output.GetNeurons().at(0).GetValue() << std::endl;
  }

  for(int i= 0; i < layer2.GetLayerSize(); i++){
    std::cout << layer2.GetNeurons().at(i).ConnectionsToString() << std::endl;
  }

  assert(testError == bestRun.error);
  for(int i = 0; i < n_threads; i++){
    threads.at(i).join();

  }
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