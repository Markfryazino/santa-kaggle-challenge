//
// Created by data_sapiens on 29.12.2019.
//

#include "Population.h"
#include "Distribution.h"
#include <vector>

Population::Population(std::vector<std::vector<int>> &_data) : data(_data) {
    samples = {};
    std::vector<int> init = {};
    for (int i = 0; i < SIZE; ++i)
        samples.push_back(Distribution(data, init, init));
}