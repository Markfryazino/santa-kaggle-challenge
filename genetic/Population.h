//
// Created by data_sapiens on 29.12.2019.
//

#ifndef GENETIC_POPULATION_H
#define GENETIC_POPULATION_H


#include <vector>
#include "Distribution.h"
#include "funcs.h"

class Population {
public:
    const int SIZE = 100;
    int worstIndex, bestIndex;
    double worstScore, bestScore;
    std::vector<std::vector<int>> &data;
    std::vector<Distribution> samples;
    std::vector<std::pair<std::vector<int>, std::vector<int>>> values;

    Population(std::vector<std::vector<int>> &_data);
    void step();
};


#endif //GENETIC_POPULATION_H
