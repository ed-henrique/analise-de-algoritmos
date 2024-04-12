from matplotlib import pyplot as plt
import pandas as pd

df = pd.read_csv('log.csv')

algorithms = df["algorithm_name"].unique()
ns = df["n"].unique()
orders = df["order"].unique()

figure, axis = plt.subplots(len(orders), figsize=(10, 15))
for i, order in enumerate(orders):
        for alg in algorithms:
            x_ns = []
            y_durations_means = []
            for n in sorted(ns):
                plot_df = df.loc[(df['algorithm_name'] == alg) & (df['n'] == n) & (df['order'] == order)]
                timings = plot_df['duration_ns'].values.tolist()
                if len(timings) > 0:
                    duration_mean = sum(timings) / len(timings)
                    x_ns.append(n)
                    y_durations_means.append(duration_mean)
            print(order, x_ns, y_durations_means, alg)
            axis[i].plot(x_ns, y_durations_means, label=alg)
        axis[i].legend()
        axis[i].set_xlabel("n")
        axis[i].set_ylabel("duration(nanoseconds)")
plt.savefig(f"figs/test.png")