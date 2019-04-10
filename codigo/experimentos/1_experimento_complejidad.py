import setup
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os
import graf_comp_linea_generico as lg
import graf_comp_coef_generico as cg

data_paths = ["datos_fuerza_bruta.csv", "datos_mitm.csv", "datos_backtracking.csv", "datos_dinamica.csv", "datos_especial_dinamica.csv"]

paths = setup.preparar_entorno()

def plot_graf(path, metodo, cota):
    datos = pd.read_csv(os.path.join(paths["datos"], path))
    datos = datos.groupby("n").mean()
    datos["n"] = datos.index
    datos = datos[datos["n"] < 100]
    f_cota = lambda n, W: eval(cota)
    app = pd.Series([f_cota(i, j) for i, j in zip(datos.n, datos.W)])
    datos["cota"] = app

    cg.graficar_exp(datos)
    lg.graficar_exp(datos, metodo, cota)
    
def graf_heat(data):
    data = data.drop_duplicates(["n", "W"])
    heat_df = data.pivot("n", "W", "Tiempo")
    ax = sns.heatmap(heat_df)
    ax.invert_yaxis()
    plt.show()

def graf_lineas(data):
    fig = plt.figure()

    Ws = [50, 100, 1000]
    ns = [100, 500, 1000]

    ax1 = fig.add_subplot(211)
    for i in Ws:
        ax1 = sns.lineplot(x="n", y="Tiempo", data=data[data["W"] == i])
    ax1.legend([f"W = {i}" for i in Ws])
    plt.ylabel("Tiempo (ms)")

    ax2 = fig.add_subplot(212)
    for i in ns:
        ax2 = sns.lineplot(x="W", y="Tiempo", data=data[data["n"] == i])
    ax2.legend([f"n = {i}" for i in ns])
    plt.ylabel("Tiempo (ms)")

    plt.show()

def plot_graf_multi_dinamica(path):
    data = pd.read_csv(os.path.join(paths["datos"], path))
    data = data[data["n"] >= 100]
    data = data[data["W"] >= 100]
    f_cota = lambda n, W: n*W
    app = pd.Series([f_cota(i, j) for i, j in zip(data.n, data["W"])])
    data["cota"] = app
    graf_heat(data)
    graf_lineas(data)
    cg.graficar_exp(data)

if __name__=="__main__":
    cotas = ["n*(2**n)/1e5", "(n/2)*(2**(n/2))/1e5", "n*(2**n)/1e7", "n*W/1e4"]
    metodos = ["Fuerza Bruta", "MITM", "Backtracking con podas", "Dinamica"]
    for i, j, k in zip(data_paths[:-1], metodos[:-1], cotas[:-1]):
        plot_graf(i, j, k)
    plot_graf_multi_dinamica(data_paths[-1])
