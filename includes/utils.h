#ifndef UTILS
#define UTILS
#include <functional>
#include <random>
#include <chrono>
#include <iostream>
#include <cstdlib> // this is where srand() is defined
#include <ctime>   // this is where time() is defined
#include <limits>  // Getting the limit for a double
#include "math.h"
#include <stdexcept>
#include <limits>
#include <map>
#include <thread>

#include <cassert>

template <typename T>
struct array
{
  T *data;
  int m_size = 0;
  array(int size) : m_size(size)
  {
    data = new T[size];
  }
  array() : m_size(0){

  }
  void init(int size){
    data = new T[size];
    m_size = size;
  }
  T &operator[](int i) const
  {
    assert(i >= 0 && i < m_size);
    return data[i];
  }
  const int size()
  {
    return m_size;
  }
  T &at(int i) const
  {
    assert(i >= 0 && i < m_size);
    return data[i];
  }
  array<double> &operator=(const array<double> &other)
  {
    assert(other.m_size != 0);
    if(m_size == 0){
      data = new T[other.m_size];
      m_size = other.m_size;
    }
    for (int i = 0; i < m_size; ++i)
    {
      data[i] = other.data[i];
    }
    return *this;
  }
  array<T> &operator=(array<T> &other)
  {
    assert(other.m_size != 0);
    if(m_size == 0){
      data = new T[other.m_size];
      m_size = other.m_size;
    }
    for (int i = 0; i < m_size; ++i)
    {
      data[i] = other.data[i];
    }
    return *this;
  }

  T* begin() { return data; }
  T* end() { return data + m_size; }
};

struct Weights{
  array<double> weights;
  Weights(array<double> _weights) : weights(_weights){}
  Weights() : weights(array<double>(0)){}
  double& operator[](int i) const
  {
    return weights[i];
  }
  const int size()
  {
    return weights.size();
  }
  double &at(int i) const
  {
    return weights[i];
  }
  array<double> &operator=(const array<double> &other)
  {
    weights.init(other.m_size);
    weights = other;
  }
};


double derivative(std::function<double(double)> func, double x);

void timeIt(std::function<void(void)> func);

double generateRandomNumber(double high, double low);

enum WeightGenerationType
{
  RANDOM,
  FIXED,

};

array<Weights> generateWeights(int layer_1_size, int layer_2_size, WeightGenerationType type, double weight = 0);

array<double> generateRandomNumberVector(int size, double high = 1, double low = -1);
long long now();
double computeError(double _true, double _pred);
double computeError(array<double> _true, array<double> _pred);

#endif