//
// Created by data_sapiens on 29.12.2019.
//

#include "Population.h"
#include "Distribution.h"
#include <algorithm>
#include <vector>
#include <string>

extern std::string FILE_PATH;

Population::Population(std::vector<std::vector<int>> &_data) : data(_data) {
    samples = {};
    worstScore = 0;
    bestScore = 1e18;
    values = std::vector<std::pair<std::vector<int>, std::vector<int>>>(SIZE);
    for (int i = 0; i < SIZE; ++i) {
        samples.emplace_back(Distribution(data, values[i].first, values[i].second));
        if (samples[i].score > worstScore) {
            worstScore = samples[i].score;
            worstIndex = i;
        }
        if (samples[i].score < bestScore) {
            bestIndex = i;
            bestScore = samples[i].score;
        }
    }
}

bool compare(Distribution one, Distribution two) {
    return one.score < two.score;
}

void Population::step() {
    std::vector<std::pair<std::vector<int>, std::vector<int>>> slot(2 * SIZE);
    std::vector<Distribution> vec;
    std::vector<int> init = {};
    for (int ind = 0; ind < SIZE; ++ind)
        vec.emplace_back(samples[ind]);
    for (int ind = 0; ind < SIZE; ++ind)
        vec.emplace_back(samples[ind].mutate(slot[ind]));
    int i = 0;
    while (i < SIZE) {
        int male = rand() % SIZE, female = rand() % SIZE;
        if (male == female) continue;
        Distribution temp = samples[male].crossbreed(samples[female], slot[SIZE + i]);
        if (temp.score == -1) continue;
        vec.emplace_back(temp);
        ++i;
    }
    std::sort(vec.begin(), vec.end(), compare);
    std::vector<std::pair<std::vector<int>, std::vector<int>>> values2(SIZE);
    for (int i = 0; i < SIZE; ++i)
        values2[i] = std::make_pair(vec[i].byfams, vec[i].bydays);
    values = values2;
    for (int i = 0; i < SIZE; ++i) {
        samples[i] = Distribution(data, values[i].first, values[i].second, false);
        samples[i].score = vec[i].score;
    }
    bestScore = samples[0].score;
    bestIndex = 0;
    worstScore = samples[SIZE - 1].score;
    worstIndex = SIZE - 1;
}