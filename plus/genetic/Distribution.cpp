//
// Created by data_sapiens on 29.12.2019.
//
#include "Distribution.h"
#include <cmath>
#include <random>
#include <algorithm>
#include <time.h>

double Distribution::familyGift(int date, int index, const int feesForAll[11],
        const int feesForEach[11]) {
    int num = this->data[index][10];
    for (int i = 0; i < 10; ++i)
        if (date == this->data[index][i])
            return feesForAll[i] + feesForEach[i] * num;
    return feesForAll[10] + feesForEach[10] * num;
}

double Distribution::penalty() {
    double res = 0;
    for (int d = 0; d < 100; ++d) {
        double first = (bydays[d] - 125.) / 400.;
        double s = 0;
        for (int j = 1; j < 6; ++j) {
            int ind = d + j > 99 ? 99 : d + j;
            double abs = bydays[d] - bydays[ind];
            abs = abs > 0 ? abs : -abs;
            s += pow(bydays[d], (0.5 + abs / 50.)) / j / j;
        }
        res += s * first;
    }
    return res;
}

Distribution::Distribution(std::vector<std::vector<int>> &_data,
        std::vector<int> &_byfams, std::vector<int> &_bydays) : data(_data),
        byfams(_byfams), bydays(_bydays) {
    srand(time(0));
    this->data = _data;
    std::vector<int> sourceDays(100, 0);
    std::vector<int> sourceFams(6000, -1);
    this->byfams = sourceFams;
    this->bydays = sourceDays;
    std::vector<int> fams(6000);
    for (int i = 0; i < 6000; ++i) fams[i] = i;
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(fams.begin(), fams.end(), g);
    int ind = 0, cur = 0;
    while (ind < 100) {
        byfams[fams[cur]] = ind;
        bydays[ind] += data[fams[cur]][10];
        if (bydays[ind] >= 125)
            ++ind;
        ++cur;
    }
    for (int family = cur; family < 6000; ++family) {
        bool ok = false;
        while (!ok) {
            ind = rand() % 100;
            if (bydays[ind] + data[fams[family]][10] > 300)
                continue;
            bydays[ind] += data[fams[family]][10];
            byfams[fams[family]] = ind;
            ok = true;
        }
    }
    evaluate();
}


void Distribution::evaluate() {
    int feesForAll[] = {0, 50, 50, 100, 200, 200, 300, 300, 400, 500, 500};
    int feesForEach[] = {0, 0, 9, 9, 9, 18, 18, 36, 36, 235, 434};
    double base = 0;
    for (int ind = 0; ind < 6000; ++ind)
        base += this->familyGift(this->byfams[ind], ind, feesForAll, feesForEach);
    this->score = base + penalty();
}

Distribution &Distribution::operator=(Distribution d2) {
    return d2;
}

Distribution::Distribution(std::vector<std::vector<int>> &_data, std::vector<int> &_byfams,
        std::vector<int> &_bydays, bool nothing) : data(_data), byfams(_byfams), bydays(_bydays) {
    //Nothing
}