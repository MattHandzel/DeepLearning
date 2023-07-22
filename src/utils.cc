#include "utils.h"
double derivative(std::function<double(double)> func, double x)
{
    static double h = 0.000000001;
    return (func(x + h) - func(x)) / h;
}

long long now(){
  // Get the current time point
  std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();

  // Convert the time point to nanoseconds since the epoch
  std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch());

  return ns.count();
}

void timeIt(std::function<void(void)> func)
{
    auto start = now();
    func();
    auto end = now();
    std::cout << "Time taken by function:\t" << (end - start) / 1e3 << " microseconds\n";
}

double generateRandomNumber(double high = 1, double low = -1)
{

    if(high < low){
        throw std::runtime_error("HIGH IS LOWER THAN LOW");
    }

    // random device class instance, source of 'true' randomness for initializing random seed
    // std::random_device rd; 

    // Mersenne twister PRNG, initialized with seed from previous random device instance
    // std::mt19937 gen(rand()); 
    
    // std::normal_distribution<float> d((high + low) / 2, (high - low) / 2);
    
    // return d(gen);
    return (((double)(rand()) / (RAND_MAX)) * (high - low) + low);
}

std::vector<double> generateRandomNumberVector(int size, double high = 1, double low = -1){
    std::vector<double> v;
    for(int i = 0; i < size; i++){
        v.push_back(generateRandomNumber(high, low));
    }
    return v;
}

std::vector<std::vector<double>> generateWeights(int layer_1_size, int layer_2_size, WeightGenerationType type, double weight = 0)
{
    std::vector<std::vector<double>> weights;
    switch (type)
    {
    case WeightGenerationType::RANDOM:
        for (int i = 0; i < layer_1_size; i++)
        {
            weights.push_back(generateRandomNumberVector(layer_2_size, 2, -2));
        }
        break;
    case WeightGenerationType::FIXED:
        for (int i = 0; i < layer_1_size; i++)
        {
            weights.push_back(std::vector<double>());
            for (int b = 0; b < layer_2_size; b++)
            {
                weights.at(i).push_back(weight);
            }
        }
        break;

    default:
        throw std::invalid_argument("You passed in a weight generation type that has not been implemented yet!");
    }
    return weights;

}

double computeError(double _true, double _pred){
    return pow(_true - _pred, 2);
}

double computeError(std::vector<double> _true, std::vector<double> _pred){
    double error = 0;
    for(int i =0; i < _true.size(); i++){
        error += pow(_true.at(i) - _pred.at(i), 2);
    }
    return error / _true.size();
    
}