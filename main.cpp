#include <iostream>
#include "GeneticAlgorithm.hpp"
#include <cmath>
#include <chrono>
#include <string>

using namespace std;

int main(int argc, const char **argv) {
  if(argc < 4){
    cout << "gene [func_name] [min] [max]";
    exit(1);
  }
  srand(chrono::system_clock::now().time_since_epoch().count());
  string func = argv[1];
  OptiFunction opt = sphere;
  if(func == "ellipsoid")     opt = ellipsoid;
  else if(func == "zakharov") opt = zakharov;

  else if(func == "rosenbrock") opt = rosenbrock;
  else if(func == "ackley")     opt = ackley;
  else if(func == "griewank")   opt = griewank;
  else if(func == "rastrigin")  opt = rastrigin;

  auto problem = OptiProblem(opt, atoi(argv[2]), atoi(argv[3]));
  for (int i = 0; i < 1; ++i) {
    auto algo = GeneticAlgorithm(1000, 300 * 1000, problem);
    while(algo.iterate(100, 10)){}
    GeneticAlgorithm::Individual best = algo.getBest();
    cout << "f(x):"<<best.get_value()<<"\t"<<algo.getEvals()<<endl;
  }
  return 0;
}
