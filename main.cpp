#include <iostream>
#include "GeneticAlgorithm.hpp"
#include <cmath>

using namespace std;

int main(int argc, const char **argv) {
  auto problem = OptiProblem(sphere, -600.0, 600.0);

  auto algo = GeneticAlgorithm(1000, 300 * 1000, problem);
  while(algo.iterate(100, 10)){}
  GeneticAlgorithm::Individual best = algo.getBest();
  cout << best.get_value();
  std::vector<std::bitset<GENSIZE> >data = best.get_data();
  return 0;
}
