import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
from scipy.stats import linregress


# selectの平均計算量オーダーの関数
def select_sort_complexity(n, a=1.0, b=1.0):
    return a * n**b


# lselectの平均計算量オーダーの関数
def lselect_sort_complexity(n, a=1.0, b=1.0):
    return a * n**b


# データ点
n_values = np.array([20000, 200000, 2000000, 20000000])
time_select = np.array([0.001062, 0.003149, 0.011438, 0.198137])
time_lselect = np.array([0.001519, 0.009418, 0.083409, 0.820737])


# 最小二乗法での近似関数
def fit_function(x, a, b):
    return a * x + b


# シェルソートの最小二乗法による近似
params_select, _ = curve_fit(fit_function, np.log(n_values), np.log(time_select))
slope_select_fit = params_select[0]

# クイックソートの最小二乗法による近似
params_lselect, _ = curve_fit(fit_function, np.log(n_values), np.log(time_lselect))
slope_lselect_fit = params_lselect[0]

# シェルソートとクイックソートの平均計算量オーダーを計算
mean_select = select_sort_complexity(n_values)
mean_lselect = lselect_sort_complexity(n_values)

# プロット
plt.figure(figsize=(10, 6))

plt.scatter(
    n_values,
    time_select,
    label="select Sort (Actual Data)",
    marker="o",
    color="orange",
)
plt.scatter(
    n_values,
    time_lselect,
    label="lselect Sort (Actual Data)",
    marker="o",
    color="blue",
)

# 最小二乗法による近似曲線をプロット
plt.plot(
    n_values,
    np.exp(fit_function(np.log(n_values), *params_select)),
    label="select Sort (Fit Line)",
    linestyle="-.",
    color="orange",
)
plt.plot(
    n_values,
    np.exp(fit_function(np.log(n_values), *params_lselect)),
    label="lselect Sort (Fit Line)",
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
ratio_select_mean = [n / mean_select[0] for n in mean_select[1:]]
ratio_lselect_mean = [n / mean_lselect[0] for n in mean_lselect[1:]]
ratio_select_time = [n / time_select[0] for n in time_select[1:]]
ratio_lselect_time = [n / time_lselect[0] for n in time_lselect[1:]]

# 棒の配置位置、ラベルを用意
x = np.array([1, 2, 3])

# 各系列のデータを用意
data1 = [ratio_select_mean, ratio_select_time]

data2 = [ratio_lselect_mean, ratio_lselect_time]

# マージンを設定
margin = 0.2  # 0 <margin< 1
totoal_width = 1 - margin

plt.figure()

# 棒グラフをプロット
for i, h in enumerate(data1):
    pos = x - totoal_width * (1 - (2 * i + 1) / len(data1)) / 2
    plt.bar(pos, np.log(h), width=totoal_width / len(data1))

plt.title("Ratio of 20000 to n times the number of data (select)")
# ラベルの設定
plt.xticks(x, ratio_n_values)
plt.xlabel("n times.")
plt.ylabel("ratio (log)")
plt.legend(
    (
        "mean computational complexity",
        "Actual measurement results",
    )
)
plt.savefig("ratio_select_plot.png")

plt.figure()

# 棒グラフをプロット
for i, h in enumerate(data2):
    pos = x - totoal_width * (1 - (2 * i + 1) / len(data2)) / 2
    plt.bar(pos, np.log(h), width=totoal_width / len(data2))

plt.title("Ratio of 20000 to n times the number of data (l-select)")
# ラベルの設定
plt.xticks(x, ratio_n_values)
plt.xlabel("n times.")
plt.ylabel("ratio (log)")
plt.legend(
    (
        "mean computational complexity",
        "Actual measurement results",
    )
)
plt.savefig("ratio_lselect_plot.png")
