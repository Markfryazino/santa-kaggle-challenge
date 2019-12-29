//
// Created by data_sapiens on 30.12.2019.
//

#include <fstream>
#include "funcs.h"
#include <vector>

void readFile(std::vector<std::vector<int>> &data) {
    std::ifstream in("/home/data_sapiens/programs/challenges/santa_2019_2020/data/data.txt");
    for (int i = 0; i < 6000; ++i)
        for (int j = 0; j < 11; ++j)
            in >> data[i][j];
}