#include "Neuron.h"
#include <functional>

// Constructors for the neuron, if you do not pass in a bias then the
// bias will be the default which is in the header file
Neuron::Neuron(){}
Neuron::Neuron(double bias){
  m_bias = bias;
}

// Adds the connection into the connections vector
void Neuron::AddConnection(const std::pair<Neuron*, double>& connection){
  m_connections.push_back(connection);
}

// This is a different version of AddConnection that lets you pass in a neuron and a value instead, this is a bit less typing :)
void Neuron::AddConnection(Neuron neuron, double value)
{
  m_connections.push_back(std::pair<Neuron*, double>(&neuron, value));
}

// This will add a vector of connections to the neruons connections.
void Neuron::AddConnections(std::vector<std::pair<Neuron*, double>>& connections){
  // || This can probably be done better than a for each loop
  for(std::pair<Neuron*, double> connection : connections){
    m_connections.push_back(connection);
  }
}

// Sets the activation function so that we can do cool machine learning stuff
void Neuron::SetActivationFunction(ActivationFunction func)
{
  m_activationFunction = func;
}

// this will return the value, THE DATA IS NOT PROCESSED HERE
double& Neuron::GetValue()
{

  // ! The connection size, for some reason, is huge
  // TODO:: Figure out why the connections size is huge and fix it
  // TODO:: Once this is fixed, then remove this

  return m_value;
}

// This will prcoess data
void Neuron::ProcessData()
{
  // if(m_connections.size() == 0){
  //   throw std::logic_error("You have no connections on this neuron.");
  // }

  m_value = m_bias;

  for(int i = 0; i < m_connections.size(); i++){
    m_value += m_connections.at(i).first->GetValue() * m_connections.at(i).second;
  }
  
  m_value = m_activationFunction(m_value);
}

// Sets the value of the neuron
void Neuron::SetValue(double value){
  m_value = value;
}

void Neuron::SetWeight(int index, double newWeight){
  this->m_connections.at(index).second = newWeight;
}

double Neuron::GetBias(){
  return m_bias;
}

void Neuron::SetBias(double bias){
  m_bias = bias;
}

// Returns a string with data about the connections it has, including the number, the address of the neuron its connected to, as well as the value of the weight of the connection
std::string Neuron::ConnectionsToString()
{
  std::string message = "";
  int i = 0;
  for(std::pair<Neuron *, double> connection : m_connections){
    std::cout << "Neuron address of " << connection.first << " has a value of " << connection.first->GetValue() << " and the weight is " << connection.second << std::endl;
  }
  //! This can break if the size of m_connections is super big for some reason
  return message;
}

void Neuron::ProcessInput(double input)
{
  m_value = m_activationFunction(m_bias + input);
}

void Neuron::operator()(double input)
{
  this->ProcessInput(input);
}

double mse(double x, double y)
{
  // || this can be optimized
  return (y - x) * (y - x);
}

double derivative(Neuron n, double input)
{
  static double h = 0.00000000001;
  n(input);
  double value1 = n.GetValue();
  n(input - h);
  double value2 = n.GetValue();

  return (value1 - value2) / h;
}
