//
// Created by data_sapiens on 29.12.2019.
//
#include "Distribution.h"
#include <cmath>
#include <random>
#include <algorithm>
#include "Population.h"
#include <iostream>
#include <fstream>

extern std::string FILE_PATH;

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
    this->data = _data;
    std::vector<int> sourceDays(100, 0);
    std::vector<int> sourceFams(6000, -1);
    this->byfams = sourceFams;
    this->bydays = sourceDays;
    std::vector<int> fams(6000);
    for (int i = 0; i < 6000; ++i) fams[i] = i;
    std::default_random_engine e((rand() << 15) + rand());
    std::shuffle(fams.begin(), fams.end(), e);
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
    bydays = d2.bydays;
    byfams = d2.byfams;
    data = d2.data;
    score = d2.score;
    return *this;
}

Distribution::Distribution(std::vector<std::vector<int>> &_data, std::vector<int> &_byfams,
        std::vector<int> &_bydays, bool nothing) : data(_data), byfams(_byfams), bydays(_bydays) {
    //Nothing
}

Distribution Distribution::mutate(std::pair<std::vector<int>, std::vector<int>>& slot) {
    bool ok = false;
    Distribution d2 = Distribution(data, slot.first, slot.second, false);
    d2.byfams = byfams;
    d2.bydays = bydays;
    while (!ok) {
        int fam = rand() % 6000;
        int newind = rand() % 100;
        if (d2.bydays[newind] + d2.data[fam][10] <= 300 && d2.bydays[d2.byfams[fam]] -
                                                            d2.data[fam][10] >= 125) {
            ok = true;
            d2.bydays[newind] += d2.data[fam][10];
            d2.bydays[d2.byfams[fam]] -= data[fam][10];
            d2.byfams[fam] = newind;
        }
    }
    d2.evaluate();
    return d2;
}

void Distribution::toFile(std::string file) {
    std::ofstream out(FILE_PATH + file);
    for (int i = 0; i < 6000; ++i)
        out << byfams[i] + 1 << "\n";
}

Distribution Distribution::crossbreed(Distribution &other, std::pair<std::vector<int>, std::vector<int>>& slot) {
    Distribution res(data, slot.first, slot.second, false);
    res.byfams = std::vector<int>(6000, -1);
    res.bydays = std::vector<int>(100, 0);
    for (int ind = 0; ind < 6000; ++ind) {
        int first = byfams[ind], second = other.byfams[ind];
        if (bydays[first] >= 300 || (bydays[first] >= 125 && bydays[second] < 125)) {
            res.byfams[ind] = second;
            res.bydays[second] += data[ind][10];
        } else if (bydays[second] >= 300 || (bydays[second] >= 125 && bydays[first] < 125)) {
            res.byfams[ind] = first;
            res.bydays[first] += data[ind][10];
        } else {
            int r = rand() % 2;
            if (r) {
                res.byfams[ind] = first;
                res.bydays[first] += data[ind][10];
            } else {
                res.byfams[ind] = first;
                res.bydays[first] += data[ind][10];
            }
        }
    }
    bool ok = true;
    while (ok) {
        ok = false;
        for (int i = 0; i < 6000; ++i) {
            if (res.bydays[res.byfams[i]] > 300) {
                ok = true;
                bool ok2 = false;
                int r;
                while (!ok2) {
                    r = rand() % 100;
                    if (res.bydays[r] <= 300 - data[i][10])
                        ok2 = true;
                }
                res.bydays[res.byfams[i]] -= data[i][10];
                res.bydays[r] += data[i][10];
                res.byfams[i] = r;
            } else if (res.bydays[res.byfams[i]] < 125) {
                ok = true;
                bool ok2 = false;
                int r;
                while (!ok2) {
                    r = rand() % 6000;
                    if (res.bydays[res.byfams[r]] >= 125 - data[r][10])
                        ok2 = true;
                }
                res.bydays[res.byfams[i]] += data[r][10];
                res.bydays[res.byfams[r]] -= data[r][10];
                res.byfams[r] = res.byfams[i];
            }
        }
    }
    bool glok = true;
    for (int d = 0; d < 100; ++d)
        if (res.bydays[d] > 300 || res.bydays[d] < 125) {
            glok = false;
            break;
        }
    if (glok) {
        res.evaluate();
        return res;
    }
    std::vector<int> init = {};
    Distribution dist = Distribution(data, init, init, false);
    dist.score = -1;
    return dist;
}