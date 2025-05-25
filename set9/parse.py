import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv("results.csv")
df.columns = df.columns.str.strip()

grouped = df.groupby(["vector_type", "algorithm", "size"], as_index=False).agg({
    "time_ns": "mean",
    "comparisons": "mean"
})

vector_types = grouped["vector_type"].unique()

sns.set(style="whitegrid")

for vector_type in vector_types:
    subset = grouped[grouped["vector_type"] == vector_type]

    plt.figure(figsize=(16, 6))
    plt.suptitle(f"Тип массива: {vector_type}", fontsize=16)

    plt.subplot(1, 2, 1)
    sns.lineplot(data=subset, x="size", y="time_ns", hue="algorithm", marker="o")
    plt.title("Время сортирвки (нс)")
    plt.xlabel("Размер массива")
    plt.ylabel("Среднее время (нс)")

    plt.subplot(1, 2, 2)
    sns.lineplot(data=subset, x="size", y="comparisons", hue="algorithm", marker="o")
    plt.title("Число сравнений")
    plt.xlabel("Размер массива")
    plt.ylabel("Среднее число сравнений")

    plt.tight_layout(rect=[0, 0, 1, 0.95])
    plt.show()
