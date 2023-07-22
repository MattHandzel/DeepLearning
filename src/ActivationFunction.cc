#include "ActivationFunction.h"
#include <functional>
#include <math.h>

ActivationFunction::ActivationFunction(ActivationFunctionType type, std::map<std::string, double> params) : m_type(type), m_params(params){
    
}

double ActivationFunction::operator()(double value){
    switch(m_type){
        case RELU:
            return m_params.at("slope") * ((value) > m_params.at("x-intercept")) * value;
        case LINEAR:
            return m_params.at("slope") * value;
        case SIGMOID:
            return 1 / (1 + pow(E, -value));
        default:
            std::__throw_logic_error("this is not implemented yet!");
    }
}
