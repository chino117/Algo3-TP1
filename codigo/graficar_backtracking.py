import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Graficos Nodos x n para las variantes de backtracking

back = ["Backtracking_simple", "Backtracking_fact", "Backtracking_opt", "Backtracking_ambas"]
paths = ["datos/datos_random_backtracking_simple.csv", "datos/datos_random_backtracking_fact.csv", "datos/datos_random_backtracking_opt.csv", "datos/datos_random_backtracking_ambas.csv"]

data = []

for i in range(0, len(paths)):
    data.append(pd.read_csv(paths[i]).dropna().groupby("n").mean())

for i in data:
    i["n"] = pd.Series(range(0, i.shape[0]))

colores = ["red", "blue", "green", "gray"]

#for i in range(0, len(data)):
#    if i == 0:
#        ax = data[i].plot(x="n", y="Nodos", color=colores[i], logy=True, label=back[i], grid=True)
#    else:
#        data[i].plot(x="n", y="Nodos", color=colores[i], logy=True, label=back[i], grid=True, ax=ax)
#plt.ylabel("Nodos")
#plt.xlim((2, max(data[0].n)))
#plt.legend()
#plt.show()

#for i in range(1, len(data)):
#    if i == 1:
#        ax = data[i].plot(x="n", y="Nodos", color=colores[i], logy=True, label=back[i], grid=True)
#    else:
#        data[i].plot(x="n", y="Nodos", color=colores[i], logy=True, label=back[i], grid=True, ax=ax)

#plt.ylabel("Nodos")
#plt.xlim((2, max(data[1].n)))
#plt.legend()
#plt.show()

for i in range(2, len(data)):
    if i == 2:
        ax = data[i].plot(x="n", y="Nodos", color=colores[i], logy=True, label=back[i], grid=True)
    else:
        data[i].plot(x="n", y="Nodos", color=colores[i], logy=True, label=back[i], grid=True, ax=ax)

plt.ylabel("Nodos")
plt.xlim((2, max(data[-1].n)))
plt.legend()
plt.show()
