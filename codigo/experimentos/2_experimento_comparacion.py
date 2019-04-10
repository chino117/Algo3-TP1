import setup
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os
import graf_comp_linea_generico as lg
import graf_comp_coef_generico as cg

data_paths = ["datos_fuerza_bruta.csv", "datos_mitm.csv", "datos_backtracking_simple.csv", "datos_backtracking_podas.csv", "datos_dinamica.csv"]

paths = setup.preparar_entorno()

def comparar_todos(data):
    for i in data["Metodo"].unique():
        ax1 = sns.lineplot(x="n", y="Tiempo", data=data[data["Metodo"] == i])
    plt.xlabel("n")
    plt.ylabel("Tiempo(ms)")
    plt.legend(data["Metodo"].unique())
    plt.show()

def comparar_back_din(data):
    for i in data["Metodo"].unique():
        ax1 = sns.lineplot(x="n", y="Tiempo", data=data[data["Metodo"] == i])
    plt.xlabel("n")
    plt.ylabel("Tiempo(ms)")
    plt.legend(data["Metodo"].unique())
    plt.show()

if __name__=="__main__":
    todos = [pd.read_csv(os.path.join(paths["datos"], i)) for i in data_paths]
    data = pd.concat(todos, sort=False)

    comparar_todos(data[data["n"] < 100])
    comparar_back_din(data[data["Metodo"].isin(["Backtracking_podas", "Dinamica"])])
