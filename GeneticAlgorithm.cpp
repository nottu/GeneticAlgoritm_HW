#include <iostream>
#include <algorithm>
#include <cmath>

#include "GeneticAlgorithm.hpp"
using namespace std;

/*  GeneticAlgorithm  */
GeneticAlgorithm::GeneticAlgorithm(int pop_size, int max_ev,  OptiProblem problem):
  __problem(problem), max_evals(max_ev){
  population.reserve((unsigned)(pop_size));
  for (int i = 0; i < pop_size; ++i){
    population.emplace_back(Individual());
    vector<bitset<GENSIZE> > dat = population[i].get_data();
    population[i].set_value(__problem.evalFunction(dat));
    max_evals--;
  }
}

bool GeneticAlgorithm::iterate(int n_replace, int n_tourney){
  sort(population.begin(), population.end(), [](Individual &i1, Individual &i2){
    return (i1.get_value()<i2.get_value());
  });
  double best = population[0].get_value();
  double min_fit = population[n_replace].get_value();
  int replaced = 0;
  while(replaced < n_replace && max_evals){
    pair<Individual, Individual> children = getChilds(n_tourney);
    vector<bitset<GENSIZE> > dat = children.first.get_data();
    children.first.set_value(__problem.evalFunction(dat));
    max_evals--;
    if(children.first.get_value() < min_fit){
      population[population.size() - n_replace + replaced] = children.first;
      replaced++;
    }
    if(max_evals){
      max_evals--;
      dat = children.second.get_data();
      children.second.set_value(__problem.evalFunction(dat));
      if(children.second.get_value() < min_fit && replaced < n_replace){
        population[population.size() - n_replace + replaced] = children.second;
        replaced++;
      }
    }
  }
  return max_evals > 0;// can still iterate
}
GeneticAlgorithm::Individual GeneticAlgorithm::getBest(){
  sort(population.begin(), population.end(), [](Individual &i1, Individual &i2){
    return (i1.get_value()<i2.get_value());
  });
  return population[0];
}
pair<GeneticAlgorithm::Individual, GeneticAlgorithm::Individual> GeneticAlgorithm::getChilds(int n_tourney){
  Individual p1 = getParent(n_tourney);
  Individual p2 = getParent(n_tourney);
  return p1.crossOver(p2);
}
GeneticAlgorithm::Individual GeneticAlgorithm::getParent(int n_tourney){
  auto fittest_idx = int(population.size() - 1);
  for (int i = 0; i < n_tourney; ++i) {
    auto idx = int(rand()%population.size());
    if(idx < fittest_idx) fittest_idx = idx;
  }
  return population[fittest_idx];
}
/*  GeneticAlgorithm::Individual  */
GeneticAlgorithm::Individual::Individual(){
  data.reserve(unsigned(NUMVARS));
  for (int i = 0; i < NUMVARS; ++i) {
    auto number = rand() % MAX_NUM;
    auto val = bitset<15>(number);
    data.emplace_back(val);
  }
}
vector<bitset<GENSIZE> > GeneticAlgorithm::Individual::get_data(){
  return data;
}
double GeneticAlgorithm::Individual::get_value(){
  return value;
}
void GeneticAlgorithm::Individual::set_value(double val){
  value = val;
}
pair<GeneticAlgorithm::Individual, GeneticAlgorithm::Individual> GeneticAlgorithm::Individual::crossOver(Individual couple){
  int crossIndex = rand() % (NUMVARS * GENSIZE);
  int n_var = crossIndex / GENSIZE; //variable at which cross happens
  for (int i = 0; i < GENSIZE; ++i) {
    bool tmp = data[n_var][i];
    data[n_var][i] = couple.data[n_var][i];
    couple.data[n_var][i] = tmp;
  }
  for (int i = n_var+1; i < data.size() ; ++i) {
    bitset<GENSIZE> tmp = data[i];
    data[i] = couple.data[i];
    couple.data[i] = tmp;
  }
  mutate();
  couple.mutate();
  pair<Individual, Individual> mypair(*this, couple);
  return mypair;
}
void GeneticAlgorithm::Individual::mutate(){
  for (int i = 0; i < NUMVARS; ++i) {
    for (int j = 0; j < GENSIZE; ++j) {
      double prob = rand()/double(RAND_MAX);
      if(prob < 0.025){
        data[i][j] = !data[i][j];
      }
    }
  }
}