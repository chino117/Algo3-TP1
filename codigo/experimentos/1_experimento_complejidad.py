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

def plot_graf(path, metodo, cota):
    datos = pd.read_csv(os.path.join(paths["datos"], path))
    f_cota = lambda n, W: eval(cota)
    app = pd.Series([f_cota(i, j) for i, j in zip(datos.n, datos["W"])])
    datos["cota"] = app
    datos = datos.groupby("n").mean()
    datos["n"] = datos.index

    cg.graficar_exp(datos)
    lg.graficar_exp(datos, metodo, cota)
    

if __name__=="__main__":
    cotas = ["n*(2**n)/1e5", "(n/2)*(2**(n/2))/1e5", "n*(2**n)/1e5", "n*(2**n)/1e6", "n*W/1e4"]
    metodos = ["Fuerza Bruta", "MITM", "Backtracking sin podas", "Backtracking con podas", "Dinamica"]
    for i, j, k in zip(data_paths, metodos, cotas):
        print(j)
        plot_graf(i, j, k)
