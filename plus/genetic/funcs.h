//
// Created by data_sapiens on 30.12.2019.
//

#ifndef GENETIC_FUNCS_H
#define GENETIC_FUNCS_H

#include <vector>
#include <string>
#include "Distribution.h"

void readData(std::vector<std::vector<int>> &data);
Distribution readFromFile(std::string file, std::vector<std::vector<int>> &data);

#endif //GENETIC_FUNCS_H
