#include <iostream>
#include <random>

  std::random_device rd; // Obtain a seed from hardware
  std::mt19937 gen(rd()); // Mersenne Twister engine
  std::uniform_int_distribution<int> dist(0,100); // Define distribution
double rand_double(double min, double max){
  return min + (max - min)/100 * dist(gen);
}
