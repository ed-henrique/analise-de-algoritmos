from matplotlib import pyplot as plt
import pandas as pd
from collections import defaultdict

df = pd.read_csv('log.csv')

algorithms = df["algorithm_name"].unique()
ns = df["n"].unique()
orders = df["order"].unique()

figure, axis = plt.subplots(len(orders), figsize=(10, 30))
for i, order in enumerate(orders):
    xy_algs = {}
    for alg in algorithms:
        x_ns = []
        y_durations_means = []
        for n in sorted(ns):
            plot_df = df.loc[(df['algorithm_name'] == alg) & (df['n'] == n) & (df['order'] == order)]
            timings = plot_df['duration_ns'].values.tolist()
            duration_mean = sum(timings) / len(timings)
            x_ns.append(n)
            y_durations_means.append(duration_mean)
        print(order, x_ns, y_durations_means, alg)
        axis[i].plot(x_ns, y_durations_means, label=alg)
    axis[i].legend()
    axis[i].set_xlabel("n")
    axis[i].set_ylabel("duration(nanoseconds)")
plt.savefig(f"figs/test.png")
        
"""plt.plot(x_ns, y, label = "line 1") 
plt.plot(y, x, label = "line 2") 
plt.show()"""
        


"""fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2)
fig.suptitle('Sharing x per column, y per row')
ax1.plot(x, y)
ax2.plot(x, y**2, 'tab:orange')
ax3.plot(x, -y, 'tab:green')
ax4.plot(x, -y**2, 'tab:red')

for ax in fig.get_axes():
    ax.label_outer()

print(df.head())"""