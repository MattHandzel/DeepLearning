#ifndef NEURON
#define NEURON
#include <vector>
#include <functional>
#include <string>
#include "ActivationFunction.h"
#include "utils.h"

class Neuron{
 public:
    Neuron();
    Neuron(double bias);

    // This allows neurons to connect to each other, you pass in a neuron and the value of the weight of the connection
    void AddConnection(std::pair<Neuron*, double> connection);
    void AddConnection(Neuron neuron, double weight);
    void AddConnections(std::vector<std::pair<Neuron*, double>> connections);
    void SetWeight(int index, double newWeight);
    void Neuron::SetBias(double bias);

    // Activation function for the neuron
    void SetActivationFunction(ActivationFunction func);

    // Returns the value of the neuron
    double GetValue();
    double GetBias();

    // TODO:: Make sure that all of the instances of GetValue() are now ProcessData()
    // Process data will do all of the processing of data that the neuron needs to do, such as getting the values from the neron's it
    // is connected to and then multiplying that by the weight, etc.
    void ProcessData();

    // Sets the value of m_value
    void SetValue(double value);

    std::vector<std::pair<Neuron *, double>> GetConnections(){
      return m_connections;
    }


    // TODO:: Make m_connections private and then make a function that returns m_connections (make sure this doesn't screw anything else up)
    // TODO:: Learn about passing objects by referecne and how pointers work
    // This vector holds the connections the neuron has, it is in the public
    std::vector<std::pair<Neuron *, double>> m_connections;

    // Returns a string with data about the connections it has, including the number, the address of the neuron its connected to, as well as the value of the weight of the connection
    std::string ConnectionsToString();

    void ProcessInput(double input);

    void operator()(double input);

 private:
    // Bias id the bias of the neuron, weights are stored in m_connections
    double m_bias = 0;

    // m_value is the value that the neuron will store after it is done after GetValue() is run
    double m_value = 0;

    // The activation function is the activation function that the neuron will run after it computes its value, it might be better
    //? Would storing the activation function in the layer be more efficient?
    ActivationFunction m_activationFunction = ActivationFunction(ActivationFunctionTypes::LINEAR, std::map<std::string, double>{{"slope", 1}});
};
#endif