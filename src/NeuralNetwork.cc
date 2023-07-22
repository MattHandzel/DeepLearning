#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(){

}

NeuralNetwork& NeuralNetwork::operator()(NeuralLayer layer){
    this->m_layers.push_back(layer);
    return *this;
}


std::vector<double> NeuralNetwork::operator()(double _input){
  assert(isBuilt);
  assert(m_layers[0].GetLayerSize() == 1);
  std::vector<double> input{1};
  input[0] = _input;
  this->m_layers[0].SetInput(input);
  int i = 1;
  for (; i < this->m_layers.size(); i++)
  {
    this->m_layers[i].ProcessLayer();
  }

  return m_layers[i-1].GetValues();
}

std::vector<double> NeuralNetwork::operator()(std::vector<double> input){
  assert(isBuilt);

  this->m_layers[0].SetInput(input);
  int i = 1;
  for (; i < this->m_layers.size(); i++)
  {
    this->m_layers[i].ProcessLayer();
  }

  return m_layers[i-1].GetValues();
}

void NeuralNetwork::Train(std::vector<std::vector<double>> trainData, std::vector<std::vector<double>> trainLabels, int epochs, int nThreads, int verbose = 0)
{
  // n3.ProcessData();
 
  RunData currentRun;
  currentRun.error = 0;

  for(int i = 0; i < epochs; i++){
    for(int dataIndex = 0; dataIndex < trainData.size(); dataIndex++){
      std::vector<double> output = this->operator()(trainData.at(dataIndex));
      double error = computeError(trainLabels.at(i), output);
      
      // Do gradient discent
    }

  }
}

void NeuralNetwork::Build(){
  this->isBuilt = true;
  for(int i = 1; i < this->GetSize(); i++){
    std::cout << "Connecting layer " << i << " to layer " << i-1 << "\n";
    m_layers[i].ConnectLayer(m_layers[i-1]);
  }
}

int NeuralNetwork::GetSize(){
  return this->m_layers.size();
}
