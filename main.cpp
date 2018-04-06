#include <iostream>
#include "GeneticAlgorithm.hpp"
#include <cmath>
#include <chrono>

using namespace std;

int main(int argc, const char **argv) {
  srand(chrono::system_clock::now().time_since_epoch().count());
//  auto problem = OptiProblem(sphere, -600.0, 600.0);
//  auto problem = OptiProblem(sphere, -20.0, 20.0);
//   auto problem = OptiProblem(zakharov, -20.0, 20.0);

//  auto problem = OptiProblem(rosenbrock, -20.0, 20.0);
//  auto problem = OptiProblem(ackley, -20.0, 20.0);
//  auto problem = OptiProblem(griewank, -600.0, 600.0);
  auto problem = OptiProblem(rastrigin, -20.0, 20.0);
  for (int i = 0; i < 1; ++i) {
    auto algo = GeneticAlgorithm(1000, 300 * 1000, problem);
    while(algo.iterate(100, 10)){}
    GeneticAlgorithm::Individual best = algo.getBest();
    cout << "f(x):"<<best.get_value()<<"\t"<<algo.getEvals()<<endl;
  }
  return 0;
}
