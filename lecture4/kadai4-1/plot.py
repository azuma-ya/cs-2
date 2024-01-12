import matplotlib.pyplot as plt
import numpy as np

# データ点
n_values = [1000, 5000, 10000, 50000, 100000, 500000, 1000000]
time_shell = [
    0.000044,
    0.000218,
    0.000469,
    0.010432,
    0.007147,
    0.039094,
    0.083383,
]  # シェルソートの実行時間データ
time_quick = [
    0.000035,
    0.000204,
    0.000544,
    0.002412,
    0.006292,
    0.021945,
    0.046625,
]  # クイックソートの実行時間データ

# 対数プロット
plt.figure(figsize=(10, 6))

plt.plot(np.log(n_values), np.log(time_shell), label="Shell Sort", marker="o")
plt.plot(np.log(n_values), np.log(time_quick), label="Quick Sort", marker="o")

plt.xlabel("log(n)")
plt.ylabel("log(time)")
plt.legend()
plt.title("Algorithm Performance")

plt.savefig("plot.png")
