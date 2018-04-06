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
    case ellipsoid:
      return __evalEllipsoid(feno);
    case zakharov:
      return __evalZakharov(feno);
    case rosenbrock:
      return __evalRosenbrock(feno);
    case ackley:
      return __evalAckley(feno);
    case griewank:
      return __evalGriewank(feno);
    case rastrigin:
      return __evalRastrigin(feno);
    default:
      break;
  }
  return val;
}
//functions
//unimodal
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
  double val1 = 0, val2 = 0;
  for (int i = 0; i < vars.size(); ++i){
    val1 += vars[i] * vars[i];
    val2 += 0.5*(i+1)*vars[i];
  }
  return val1 + val2*val2 + val2*val2*val2*val2;
}
//multimodal
double OptiProblem::__evalRosenbrock(vector<double> &vars){
  double val = 0;
  for (int i = 0; i < vars.size() - 1; ++i){
    val += 100 * (vars[i+1] - vars[i]*vars[i]) * (vars[i+1] - vars[i]*vars[i]) + (1 - vars[i])*(1 - vars[i]);
  }
  return val;
}
double OptiProblem::__evalAckley(vector<double> &vars){
  double val = 0, val1 = 0, val2 = 0;
  for (int i = 0; i < vars.size(); ++i){
    val1 += vars[i]*vars[i];
    val2 += cos(2 * M_PI * vars[i]);
  }
  val1 = -0.2 * sqrt(val1 / vars.size());
  val2 = val2 / vars.size();
  val = -20 * exp(val1) - exp(val2) + 20 + M_E;
  return val;
}
double OptiProblem::__evalGriewank(vector<double> &vars){
  double val = 0, val2 = 1;
  for (int i = 0; i < vars.size(); ++i){
    val += vars[i]*vars[i];
    val2 *= cos(vars[i]/sqrt(i+1));
  }
  return 1 + val/4000 - val2;
}
double OptiProblem::__evalRastrigin(vector<double> &vars){
  double val = 0;
  for (auto&x : vars){
    val += x*x - 10 * cos(M_PI * 2 * x);
  }
  return 10 * vars.size() + val;
}
