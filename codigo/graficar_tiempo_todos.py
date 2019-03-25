import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Grafico de tiempo en funcion de n para todos los algoritmos

a = pd.read_csv("datos/datos_random_todos.csv")
metodos = ["Fuerza Bruta", "MITM", "Backtracking_simple", "Backtracking_fact", "Backtracking_opt", "Backtracking_ambas","Dinamica_Top_Down"]
por_metodo = []

for i in metodos:
    por_metodo.append(a[a.Metodo == i].groupby("n").mean())
    por_metodo[-1]["n"] = pd.Series(range(min(a.n), max(a.n)+1))

colores = ["red", "blue", "green", "gray", "cyan", "orange", "brown", "black"]
for i in range(0, len(por_metodo)):
    if i == 0:
        ax = por_metodo[i].plot(x="n", y="Tiempo", color=colores[i], logy=True, label=metodos[i], grid=True)
    else:
        por_metodo[i].plot(x="n", y="Tiempo", color=colores[i], logy=True, label=metodos[i], grid=True, ax=ax)
plt.legend()
plt.show()
