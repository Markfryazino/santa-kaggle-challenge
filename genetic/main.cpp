#include <iostream>
#include <vector>
#include "Population.h"
#include "Distribution.h"
#include <random>
#include "funcs.h"
#include <string>
#include <fstream>

int main() {
    srand(time(0));
    int iters;
    std::string ansname, logname;
    std::cout << "Enter number of iterations: ";
    std::cin >> iters;
    std::cout << "Enter path to the directory where file data.txt is located: ";
    extern std::string FILE_PATH;
    std::cin >> FILE_PATH;
    std::cout << "Enter filenames for logs and for answer: ";
    std::cin >> logname >> ansname;
    std::ofstream log(FILE_PATH + logname);

    std::vector<std::vector<int>> data(6000, std::vector<int>(11));
    readData(data);
    Population pop = Population(data);
    for (int i = 0; i < iters; ++i) {
        pop.step();
        if (!(i % 50)) {
            std::cout << i << ": " << pop.bestScore << "\n";
            log << i << ": " << pop.bestScore << "\n";
        }
    }
    std::cout << iters - 1 << ": " << pop.bestScore;
    log << iters - 1 << ": " << pop.bestScore;
    log.close();

    pop.samples[pop.bestIndex].toFile(ansname);
    return 0;
}