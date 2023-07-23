#include "utils.h"


double derivative(std::function<double(double)> func, double x)
{
    static double h = 0.000000001;
    return (func(x + h) - func(x)) / h;
}

long long now()
{
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

<<<<<<< HEAD
    if (high < low)
    {
        throw std::runtime_error("HIGH IS LOWER THAN LOW");
=======
    if(high < low){
        throw std::runtime_error(std::to_string(high) + " is lower than " + std::to_string(low));
>>>>>>> a40b978e597d4636954daf1b82bedab2fd14b19b
    }

    // random device class instance, source of 'true' randomness for initializing random seed
    // std::random_device rd;

    // Mersenne twister PRNG, initialized with seed from previous random device instance
    // std::mt19937 gen(rand());

    // std::normal_distribution<float> d((high + low) / 2, (high - low) / 2);

    // return d(gen);
    return (((double)(rand()) / (RAND_MAX)) * (high - low) + low);
}

<<<<<<< HEAD
array<double> generateRandomNumberVector(int size, double high = 1, double low = -1)
{
    array<double> v{size};
    for (int i = 0; i < size; i++)
    {
        v[i] = (generateRandomNumber(high, low));
=======
double* generateRandomNumbers(int size, double high = 1, double low = -1){
    double v[size];
    for(int i = 0; i < size; i++){
        v[i] = generateRandomNumber(high, low);
>>>>>>> a40b978e597d4636954daf1b82bedab2fd14b19b
    }
    return v;
}

<<<<<<< HEAD
array<Weights> generateWeights(int layer_1_size, int layer_2_size, WeightGenerationType type, double weight = 0)
{
    array<Weights> weights{layer_1_size};
=======
double** generateWeights(int layer_1_size, int layer_2_size, WeightGenerationType type, double weight = 0)
{
    double** weights;
>>>>>>> a40b978e597d4636954daf1b82bedab2fd14b19b
    switch (type)
    {
    case WeightGenerationType::RANDOM:
        for (int i = 0; i < layer_1_size; i++)
        {
<<<<<<< HEAD
            weights[i] = Weights(generateRandomNumberVector(layer_2_size, 2, -2));
=======
            weights[i] = generateRandomNumbers(layer_2_size, 2, -2);
         
>>>>>>> a40b978e597d4636954daf1b82bedab2fd14b19b
        }
        break;
    case WeightGenerationType::FIXED:
        for (int i = 0; i < layer_1_size; i++)
        {
<<<<<<< HEAD
            array<double> temp{layer_2_size};
            for(int b = 0; b < layer_2_size; b++){
                temp[b] = weight;
=======
            for (int b = 0; b < layer_2_size; b++)
            {
                weights[i][b] = (weight);
>>>>>>> a40b978e597d4636954daf1b82bedab2fd14b19b
            }
            weights[i] = Weights(temp);
        }
        assert(weights[0][0] == weight);
        assert(weights[layer_1_size-1][layer_2_size-1] == weight);
        break;

    default:
        throw std::invalid_argument("You passed in a weight generation type that has not been implemented yet!");
    }
    return weights;
}

double computeError(double _true, double _pred)
{
    return pow(_true - _pred, 2);
}

double computeError(array<double> _true, array<double> _pred)
{
    double error = 0;
    for (int i = 0; i < _true.size(); i++)
    {
        error += pow(_true[i] - _pred[i], 2);
    }
    return error / _true.size();
}