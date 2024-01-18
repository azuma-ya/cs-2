import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
from scipy.stats import linregress


# シェルソートの理論的な計算量オーダーの関数
def shell_sort_complexity(n, a=1.0, b=(3.0 / 2.0)):
    return a * n**b


# シェルソートの最悪な計算量オーダーの関数
def shell_sort_worst(n, a=1.0, b=2):
    return a * n**b


# シェルソートの最良な計算量オーダーの関数
def shell_sort_best(n, a=1.0, b=1):
    return a * n**b


# クイックソートの理論的な計算量オーダーの関数
def quick_sort_complexity(n, a=1.0, b=1.0):
    return a * n * np.log2(n) ** b


# クイックソートの最悪な計算量オーダーの関数
def quick_sort_worst(n, a=1.0, b=2.0):
    return a * n**b


# クイックソートの最良な計算量オーダーの関数
def quick_sort_best(n, a=1.0, b=1.0):
    return a * n * np.log2(n) ** b


# データ点
n_values = np.array([1000, 5000, 10000, 50000, 100000, 500000, 1000000])
time_shell = np.array(
    [
        0.000044,
        0.000218,
        0.000469,
        0.010432,
        0.007147,
        0.039094,
        0.083383,
    ]
)

time_quick = np.array(
    [
        0.000035,
        0.000204,
        0.000544,
        0.002412,
        0.006292,
        0.021945,
        0.046625,
    ]
)


# 最小二乗法での近似関数
def fit_function(x, a, b):
    return a * x + b


# シェルソートの最小二乗法による近似
params_shell, _ = curve_fit(fit_function, np.log(n_values), np.log(time_shell))
slope_shell_fit = params_shell[0]

# クイックソートの最小二乗法による近似
params_quick, _ = curve_fit(fit_function, np.log(n_values), np.log(time_quick))
slope_quick_fit = params_quick[0]

# シェルソートとクイックソートの理論的な計算量オーダーを計算
theory_shell = shell_sort_complexity(n_values)
theory_quick = quick_sort_complexity(n_values)

# シェルソートとクイックソートの最悪な計算量オーダーを計算
worst_shell = shell_sort_worst(n_values)
worst_quick = quick_sort_worst(n_values)

# シェルソートとクイックソートの最良な計算量オーダーを計算
best_shell = shell_sort_best(n_values)
best_quick = quick_sort_best(n_values)

# プロット
plt.figure(figsize=(10, 6))

plt.scatter(
    n_values,
    time_shell,
    label="Shell Sort (Actual Data)",
    marker="o",
    color="orange",
)
plt.scatter(
    n_values,
    time_quick,
    label="Quick Sort (Actual Data)",
    marker="o",
    color="blue",
)

# 最小二乗法による近似曲線をプロット
plt.plot(
    n_values,
    np.exp(fit_function(np.log(n_values), *params_shell)),
    label="Shell Sort (Fit Line)",
    linestyle="-.",
    color="orange",
)
plt.plot(
    n_values,
    np.exp(fit_function(np.log(n_values), *params_quick)),
    label="Quick Sort (Fit Line)",
    linestyle="-.",
    color="blue",
)

plt.xscale("log")
plt.yscale("log")
plt.xlabel("Data Size (n)")
plt.ylabel("Execution Time (seconds)")
plt.legend()
plt.title("Algorithm Complexity Comparison")

plt.savefig("plot.png")

ratio_n_values = [n / n_values[0] for n in n_values[1:]]
ratio_shell_theory = [n / theory_shell[0] for n in theory_shell[1:]]
ratio_quick_theory = [n / theory_quick[0] for n in theory_quick[1:]]
ratio_shell_worst = [n / worst_shell[0] for n in worst_shell[1:]]
ratio_quick_worst = [n / worst_quick[0] for n in worst_quick[1:]]
ratio_shell_best = [n / best_shell[0] for n in best_shell[1:]]
ratio_quick_best = [n / best_quick[0] for n in best_quick[1:]]
ratio_shell_time = [n / time_shell[0] for n in time_shell[1:]]
ratio_quick_time = [n / time_quick[0] for n in time_quick[1:]]

# 棒の配置位置、ラベルを用意
x = np.array([1, 2, 3, 4, 5, 6])

# 各系列のデータを用意
data1 = [
    ratio_shell_theory,
    ratio_shell_worst,
    ratio_shell_best,
    ratio_shell_time,
]

data2 = [
    ratio_quick_theory,
    ratio_quick_worst,
    ratio_quick_best,
    ratio_quick_time,
]

# マージンを設定
margin = 0.2  # 0 <margin< 1
totoal_width = 1 - margin

plt.figure()

# 棒グラフをプロット
for i, h in enumerate(data1):
    pos = x - totoal_width * (1 - (2 * i + 1) / len(data1)) / 2
    plt.bar(pos, np.log(h), width=totoal_width / len(data1))

plt.title("Ratio of 1000 to n times the number of data (Shell)")
# ラベルの設定
plt.xticks(x, ratio_n_values)
plt.xlabel("n times.")
plt.ylabel("ratio (log)")
plt.legend(
    (
        "mean computational complexity",
        "worst computational complexity",
        "best computational complexity",
        "Actual measurement results",
    )
)
plt.savefig("ratio_shell_plot.png")

plt.figure()

# 棒グラフをプロット
for i, h in enumerate(data2):
    pos = x - totoal_width * (1 - (2 * i + 1) / len(data2)) / 2
    plt.bar(pos, np.log(h), width=totoal_width / len(data2))

plt.title("Ratio of 1000 to n times the number of data (Quick)")
# ラベルの設定
plt.xticks(x, ratio_n_values)
plt.xlabel("n times.")
plt.ylabel("ratio (log)")
plt.legend(
    (
        "mean computational complexity",
        "worst computational complexity",
        "best computational complexity",
        "Actual measurement results",
    )
)
plt.savefig("ratio_quick_plot.png")
