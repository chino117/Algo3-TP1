import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns
import argparse

def graficar_exp(mediciones, label_mediciones, label_cota):
    '''
    Dibuja un grafico de lineas para Tiempo y cota, segun n
    '''
    n = mediciones.n.unique()
    ax1 = sns.lineplot(x="n", y="Tiempo", data=mediciones)
    ax1 = sns.lineplot(x="n", y="cota", data=mediciones)
    plt.xlim([min(n), max(n)])
    plt.ticklabel_format(style='sci', axis='y')
    plt.legend([label_mediciones, label_cota])
    plt.xlabel("n")
    plt.ylabel("Tiempo(ms)")
    plt.show()

if __name__=="__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path_data", help="Path al archivo csv que contiene los datos.")
    parser.add_argument("formula_cota", help="Fórmula de la cota, se usa para generarla.(tiene que ser codigo python valido)")
    parser.add_argument("label_mediciones", help="Etiqueta con el cual identificamos a las mediciones (nombre del algoritmo).")
    parser.add_argument("label_cota", help="Etiqueta con el cual identificamos a la cota.")
    args = parser.parse_args()

    datos = pd.read_csv(args.path_data)
    f_cota = lambda n: eval(args.formula_cota)
    datos["cota"] = datos.n.apply(f_cota)
    datos = datos.groupby("n").mean()
    datos["n"] = datos.index

    graficar_exp(datos, args.label_mediciones, args.label_cota)
