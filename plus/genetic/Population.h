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
    std::vector<std::vector<int>> &data;
    std::vector<Distribution> samples;

    Population(std::vector<std::vector<int>> &_data);
};


#endif //GENETIC_POPULATION_H
