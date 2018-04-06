#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include <bitset>
#include "OptiProblem.hpp"

#define NUMVARS 10
#define GENSIZE 15U
#define MAX_NUM ((1U << GENSIZE) - 1)


class GeneticAlgorithm {
public:
  class Individual;
private:
  OptiProblem __problem;
  int max_evals;
  std::vector<Individual> population;
  Individual getParent(int n_tourney);
  std::pair<Individual, Individual> getChilds(int n_tourney);
public:
  Individual getBest();
  GeneticAlgorithm(int pop_size, int max_evals, OptiProblem problem);
  int getEvals();
  bool iterate(int n_replace, int n_tourney);
};

class GeneticAlgorithm::Individual{
  std::vector<std::bitset<GENSIZE> > data;
  double value;
public:
  std::vector<std::bitset<GENSIZE> > get_data();
  double get_value();
  void set_value(double val);
  std::pair<Individual, Individual> crossOver(Individual couple);
  void mutate();
  Individual();
};

#endif