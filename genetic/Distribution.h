//
// Created by data_sapiens on 29.12.2019.
//
#include <vector>
#include "funcs.h"
#include "Population.h"
#include <string>

#ifndef GENETIC_DISTRIBUTION_H
#define GENETIC_DISTRIBUTION_H

class Distribution {
public:
    double score;
    std::vector<std::vector<int>> &data;
    std::vector<int> &byfams;
    std::vector<int> &bydays;

    Distribution(std::vector<std::vector<int>> &_data, std::vector<int> &_byfams,
            std::vector<int> &_bydays);
    Distribution(std::vector<std::vector<int>> &_data, std::vector<int> &_byfams,
            std::vector<int> &_bydays, bool nothing);
    void evaluate();

    Distribution& operator = (Distribution d2);
    Distribution mutate(std::pair<std::vector<int>, std::vector<int>>& slot);
    void toFile(std::string file);
    Distribution crossbreed(Distribution& other, std::pair<std::vector<int>, std::vector<int>>& slot);
private:
    double familyGift(int date, int index, const int feesForAll[11], const int feesForEach[11]);
    double penalty();
};

#endif //GENETIC_DISTRIBUTION_H
