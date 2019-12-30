#include <iostream>
#include <vector>
#include "Population.h"
#include "Distribution.h"
#include "funcs.h"
#include <string>

int main() {
    std::vector<std::vector<int>> data(6000, std::vector<int>(11));
    readData(data);
    //Population pop = Population(data);
    Distribution dist = readFromFile("sample.txt", data);

    return 0;
}