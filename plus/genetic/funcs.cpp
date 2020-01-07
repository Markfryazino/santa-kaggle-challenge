//
// Created by data_sapiens on 30.12.2019.
//

#include <fstream>
#include "funcs.h"
#include <vector>
#include <string>
#include "Distribution.h"

void readData(std::vector<std::vector<int>> &data) {
    std::ifstream in("/home/data_sapiens/programs/challenges/santa_2019_2020/data/data.txt");
    for (int i = 0; i < 6000; ++i)
        for (int j = 0; j < 11; ++j)
            in >> data[i][j];
}

Distribution readFromFile(std::string file, std::vector<std::vector<int>>& data, std::pair<std::vector<int>, std::vector<int>>& slot) {
    Distribution dist(data, slot.first, slot.second, false);
    std::vector<int> byfams(6000);
    std::ifstream in("/home/data_sapiens/programs/challenges/santa_2019_2020/data/" + file);
    for (int i = 0; i < 6000; ++i)
        in >> byfams[i];
    std::vector<int> bydays(100, 0);
    for (int i = 0; i < 6000; ++i)
        bydays[byfams[i]] += data[i][10];
    dist.byfams = byfams;
    dist.bydays = bydays;
    dist.evaluate();
    in.close();
    return dist;
}