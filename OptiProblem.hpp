//
// Created by Javier Peralta on 4/5/18.
//

#ifndef GENETIC_OPTIPROBLEM_HPP
#define GENETIC_OPTIPROBLEM_HPP

#include <vector>
#include <bitset>

#define NUMVARS 10
#define GENSIZE 15U
#define MAX_NUM ((1U << GENSIZE) - 1)

enum OptiFunction {sphere, ellipsoid, zakharov};

class OptiProblem{
private:
  OptiFunction __function;
  double __min, __max, __step_size;
  //eval functions
  double __evalSphere(std::vector<double> &vars);
  double __evalEllipsoid(std::vector<double> &vars);
  double __evalZakharov(std::vector<double> &vars);
  std::vector<double> genoToFeno(std::vector<std::bitset<GENSIZE>> &geno);
public:
  double evalFunction(std::vector<std::bitset<GENSIZE>> &geno);
  OptiProblem(OptiFunction funcName, double func_min, double func_max);
};



#endif //GENETIC_OPTIPROBLEM_HPP
