import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns
import argparse

def graficar_exp(mediciones):
    coef = "r = %.5f" % mediciones.drop(columns=["W", "b"]).corr()["cota"][0]
    ax1 = sns.lmplot(x="Tiempo", y="cota", data=mediciones)
    ax1.fig.text(0.5, 0.85, coef, horizontalalignment="left", size="medium", color="black")
    plt.ylabel("Cota")
    plt.xlabel("Tiempo(n)")
    plt.show()

if __name__=="__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path_data", help="Path al archivo csv que contiene los datos.")
    parser.add_argument("formula_cota", help="Fórmula de la cota, se usa para generarla.")
    args = parser.parse_args()

    datos = pd.read_csv(args.path_data).dropna()
    f_cota = lambda n: eval(args.formula_cota)
    datos["cota"] = datos.n.apply(f_cota)
    datos = datos.groupby("n").mean()


    graficar_exp(datos)
