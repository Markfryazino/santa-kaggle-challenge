#include <iostream>
#include <vector>
#include "Population.h"
#include "Distribution.h"
#include "funcs.h"

int main() {
    std::vector<std::vector<int>> data(6000, std::vector<int>(11));
    readFile(data);
    Population pop = Population(data);

    return 0;
}