#include <functional>
#include <cmath>
#include "utils.h"
enum ActivationFunctionType{
    LINEAR,
    SIGMOID,
    RELU,
};

class ActivationFunction
{
public:
  // std::function<double(double)> linear [](double value) {return value;};
  static double linear(double value);
  static double sigmoid(double value);
  static double relu(double value);
  static constexpr double E = 2.7182818284590452353602874713527;

  ActivationFunction(ActivationFunctionType type, std::map<std::string, double> params);
  std::function<double(double)> m_activationFunction;
  
  double operator()(double value);

private:
  ActivationFunctionType m_type = LINEAR;
  std::map<std::string, double> m_params;

};