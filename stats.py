import numpy as np
import pandas as pd

import matplotlib.pyplot as plt
import seaborn as sns


stats = pd.read_csv("stats.csv")
stats["mean_num_comparisons"] = 0.0

for algo in stats["sort_algo"].unique():
    stats_algo = stats[stats["sort_algo"] == algo]
    for N in stats_algo["input_size"].unique():
        stats_algo_N = stats_algo[stats_algo["input_size"] == N]
        stats.loc[(stats["sort_algo"] == algo) & (stats["input_size"] == N),
                  ("mean_num_comparisons")] = stats_algo_N["num_comparisons"].mean()

stats_mean = stats.drop("num_comparisons", axis=1, inplace=False)
stats_mean.drop_duplicates(inplace=True)

stats_mean["mean_num_comparisons_log"] = np.log2(
    stats_mean["mean_num_comparisons"])
stats_mean["input_size_log"] = np.log2(stats_mean["input_size"])

sns.lineplot(x="input_size_log", y="mean_num_comparisons_log",
             hue="sort_algo", data=stats_mean)
plt.savefig("stats.png", dpi=300)
plt.show()
