//
// Created by Javier Peralta on 4/5/18.
//
#include <cmath>
#include "OptiProblem.hpp"

using namespace std;

OptiProblem::OptiProblem(OptiFunction funcName, double func_min, double func_max)
  :__function(funcName),__min(func_min),__max(func_max){
  __step_size = (__max - __min)/double(MAX_NUM);
}

vector<double> OptiProblem::genoToFeno(vector<bitset<GENSIZE>> &geno){
  vector<double> feno;
  feno.reserve(NUMVARS);
  for (auto &x : geno) {
    double val = __min + __step_size * x.to_ulong();
    feno.emplace_back(val);
  }
  return feno;
}


double OptiProblem::evalFunction(vector<bitset<GENSIZE>> &geno){
  vector<double> feno = genoToFeno(geno);
  double val = 0;
  switch (__function){
    case sphere:
      return __evalSphere(feno);
    default:
      break;
  }
  return val;
}
//functions

double OptiProblem::__evalSphere(std::vector<double> &vars){
  double val = 0;
  for (auto& var: vars){
    val += var * var;
  }
  return val;
}
double OptiProblem::__evalEllipsoid(std::vector<double> &vars){
  double val = 0;
  for (int i = 0; i < vars.size(); ++i){
    double v = double(i)/double(vars.size() - 1);
    val += pow(1E6, v) * vars[i]*vars[i];
  }
  return val;
}
double OptiProblem::__evalZakharov(std::vector<double> &vars){
  double val = 0;

  return val;
}