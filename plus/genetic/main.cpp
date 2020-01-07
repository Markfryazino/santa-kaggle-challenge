#include <iostream>
#include <vector>
#include "Population.h"
#include "Distribution.h"
#include <random>
#include "funcs.h"
#include <string>

int main() {
    srand(time(0));
    std::vector<std::vector<int>> data(6000, std::vector<int>(11));
    readData(data);
    Population pop = Population(data);
    int iters = 250000;
    for (int i = 0; i < iters; ++i) {
        pop.step();
        if (!(i % 50))
            std::cout << i << ": " << pop.bestScore << "\n";
    }
    std::cout << iters - 1 << ": " << pop.bestScore;
    pop.samples[pop.bestIndex].toFile("try2.txt");
    return 0;
}