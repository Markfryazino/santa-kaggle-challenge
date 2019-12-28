import pandas as pd
import numpy as np

def family_gift(data, date, index):
    fees_forall = [0, 50, 50, 100, 200, 200, 300, 300, 400, 500, 500]
    fees_foreach = [0, 0, 9, 9, 9, 18, 18, 36, 36, 235, 434]

    num = data.loc[index, 'n_people']
    for i in range(10):
        if date == data.loc[index, f'choice_{i}']:
            return fees_forall[i] + fees_foreach[i] * num
    return fees_forall[10] + fees_foreach[10] * num


def penalty(dist):
    res = 0
    for d in range(100):
        first = (dist[d] - 125) / 400
        s = 0
        for j in range(1, 6):
            ind = min(99, d + j)
            s += dist[d] ** (0.5 + abs(dist[d] - dist[ind]) / 50) / j / j
        res += s * first
    return res


def evaluate(dist, data, res):
    base = sum([family_gift(data, res[i], i) for i in range(6000)])
    return base + penalty(dist)
