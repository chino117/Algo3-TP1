import setup
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os
import graf_comp_linea_generico as lg
import graf_comp_coef_generico as cg

data_paths = ["datos_fuerza_bruta.csv", "datos_mitm.csv", "datos_backtracking.csv", "datos_especial_backtracking.csv", "datos_dinamica.csv", "datos_especial_dinamica.csv"]

paths = setup.preparar_entorno()

def plot_graf(path, metodo, cota):
    datos = pd.read_csv(os.path.join(paths["datos"], path))

    datos = setup.filtrar_tiempos_outliers(datos)

    f_cota = lambda n, W: eval(cota)
    app = pd.Series([f_cota(i, j) for i, j in zip(datos.n, datos.W)])
    datos["cota"] = app

    cg.graficar_exp(datos)
    lg.graficar_exp(datos, metodo, cota)
    
def graf_heat(data):
    data = data.drop_duplicates(["n", "W"])
    data = data[data["n"] >= 1000]
    data = data[data["W"] >= 1000]
    heat_df = data.pivot("n", "W", "Tiempo")
    ax = sns.heatmap(heat_df)
    ax.invert_yaxis()
    plt.show()

def graf_lineas(data):
    fig = plt.figure()

    Ws = [1000, 5000, 10000]
    ns = [1000, 5000, 10000]

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
    data["cota"] = data["n"] * data["W"]

    graf_heat(data)
    graf_lineas(data)
    cg.graficar_exp(data)

def plot_graf_back(path):
    datos = pd.read_csv(os.path.join(paths["datos"], path))
    datos = datos[datos["Metodo"] != "Dinamica"]
    datos = datos[datos["n"] <= 100]
    datos = setup.filtrar_tiempos_outliers(datos)

    n = datos["n"]
    datos["cota"] = pd.Series(n) * pd.Series([(2**i)/1e6 for i in n])

    cg.graficar_exp(datos)
    lg.graficar_exp(datos, "Backtracking", "n*(2^n)/1e6")

if __name__=="__main__":
    sns.set(font_scale=1.1)
    cotas = ["n*(2**n)/1e5", "(n/2)*(2**(n/2))/5e4"]
    metodos = ["Fuerza Bruta", "MITM"]
    for i, j, k in zip(data_paths[:2], metodos, cotas):
        plot_graf(i, j, k)
    plot_graf_back(data_paths[3])
    plot_graf_back("datos_problematico_backtracking.csv")
    plot_graf_multi_dinamica(data_paths[-1])
