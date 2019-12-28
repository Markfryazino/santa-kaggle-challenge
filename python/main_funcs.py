import pandas as pd
import numpy as np
import random
from evaluation import evaluate


def sample(data):
    dist = [0] * 100
    res = [-1] * 6000
    fams = list(range(6000))
    random.shuffle(fams)
    ind = 0
    cur = 0
    while ind < 100:
        res[fams[cur]] = ind
        dist[ind] += data.loc[fams[cur], 'n_people']
        if dist[ind] >= 125:
            ind += 1
        cur += 1
    for family in range(cur, 6000):
        ok = False
        while not ok:
            ind = random.randint(0, 99)
            if dist[ind] + data.loc[fams[family], 'n_people'] > 300:
                continue
            dist[ind] += data.loc[fams[family], 'n_people']
            res[fams[family]] = ind
            ok = True
    return res, dist


def create_population(data, pop_size=100):
    population = []
    for i in range(pop_size):
        res, dist = sample(data)
        population.append((res, dist, evaluate(dist, data, res)))
        if not i % 10:
            print(f'{i + 1} распределение создано.')
    return population
