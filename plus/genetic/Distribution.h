//
// Created by data_sapiens on 29.12.2019.
//
#include <vector>
#include "funcs.h"

#ifndef GENETIC_DISTRIBUTION_H
#define GENETIC_DISTRIBUTION_H

class Distribution {
public:
    double score;
    std::vector<std::vector<int>> &data;
    std::vector<int> &byfams;
    std::vector<int> &bydays;

    Distribution(std::vector<std::vector<int>> &_data, std::vector<int> &_byfams,
            std::vector<int> _bydays);
    void evaluate();
    Distribution& operator = (Distribution d2);

private:
    double familyGift(int date, int index, const int feesForAll[11], const int feesForEach[11]);
    double penalty();
};

#endif //GENETIC_DISTRIBUTION_H
