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
def quick_sort_worst(n, a=1.0, b=1.0):
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

plt.scatter(n_values, time_shell, label="Shell Sort (Actual Data)", marker="o")
plt.scatter(n_values, time_quick, label="Quick Sort (Actual Data)", marker="o")

plt.plot(
    n_values, theory_shell, label="Shell Sort (Theoretical Complexity)", linestyle="--"
)
plt.plot(
    n_values, theory_quick, label="Quick Sort (Theoretical Complexity)", linestyle="--"
)

plt.plot(
    n_values,
    worst_shell,
    label="Shell Sort (Worst Computational Complexity)",
    linestyle="--",
)
plt.plot(
    n_values,
    worst_quick,
    label="Quick Sort (Worst Computational Complexity)",
    linestyle="--",
)

plt.plot(
    n_values,
    best_shell,
    label="Shell Sort (Best Computational Complexity)",
    linestyle="--",
)
plt.plot(
    n_values,
    best_quick,
    label="Quick Sort (Best Computational Complexity)",
    linestyle="--",
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
    color="green",
)

plt.xscale("log")
plt.yscale("log")
plt.xlabel("Data Size (n)")
plt.ylabel("Execution Time (seconds)")
plt.legend()
plt.title("Algorithm Complexity Comparison")

plt.savefig("plot.png")

# 傾きの比較
print(
    "Shell Sort Slope (Theoretical):",
    shell_sort_complexity((n_values[1])) / shell_sort_complexity((n_values[0])),
    "Shell Sort Slope (Execution):",
    time_shell[1] / time_shell[0],
)
print(
    "Shell Sort Slope (Theoretical):",
    shell_sort_complexity((n_values[2])) / shell_sort_complexity((n_values[0])),
    "Shell Sort Slope (Execution):",
    time_shell[2] / time_shell[0],
)
print(
    "Shell Sort Slope (Theoretical):",
    shell_sort_complexity((n_values[3])) / shell_sort_complexity((n_values[0])),
    "Shell Sort Slope (Execution):",
    time_shell[3] / time_shell[0],
)
print(
    "Shell Sort Slope (Theoretical):",
    shell_sort_complexity((n_values[4])) / shell_sort_complexity((n_values[0])),
    "Shell Sort Slope (Execution):",
    time_shell[4] / time_shell[0],
)
print(
    "Shell Sort Slope (Theoretical):",
    shell_sort_complexity((n_values[5])) / shell_sort_complexity((n_values[0])),
    "Shell Sort Slope (Execution):",
    time_shell[5] / time_shell[0],
)
print(
    "Shell Sort Slope (Theoretical):",
    shell_sort_complexity((n_values[6])) / shell_sort_complexity((n_values[0])),
    "Shell Sort Slope (Execution):",
    time_shell[6] / time_shell[0],
)

print("Shell Sort Slope (Fit):", slope_shell_fit)

print(
    "Quick Sort Slope (Theoretical):",
    quick_sort_complexity((n_values[1])) / quick_sort_complexity((n_values[0])),
    "Quick Sort Slope (Execution):",
    time_quick[1] / time_quick[0],
)
print(
    "Quick Sort Slope (Theoretical):",
    quick_sort_complexity((n_values[2])) / quick_sort_complexity((n_values[0])),
    "Quick Sort Slope (Execution):",
    time_quick[2] / time_quick[0],
)
print(
    "Quick Sort Slope (Theoretical):",
    quick_sort_complexity((n_values[3])) / quick_sort_complexity((n_values[0])),
    "Quick Sort Slope (Execution):",
    time_quick[3] / time_quick[0],
)
print(
    "Quick Sort Slope (Theoretical):",
    quick_sort_complexity((n_values[4])) / quick_sort_complexity((n_values[0])),
    "Quick Sort Slope (Execution):",
    time_quick[4] / time_quick[0],
)
print(
    "Quick Sort Slope (Theoretical):",
    quick_sort_complexity((n_values[5])) / quick_sort_complexity((n_values[0])),
    "Quick Sort Slope (Execution):",
    time_quick[5] / time_quick[0],
)
print(
    "Quick Sort Slope (Theoretical):",
    quick_sort_complexity((n_values[6])) / quick_sort_complexity((n_values[0])),
    "Quick Sort Slope (Execution):",
    time_quick[6] / time_quick[0],
)

print("Quick Sort Slope (Fit):", slope_quick_fit)
