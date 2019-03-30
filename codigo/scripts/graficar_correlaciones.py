import numpy as np
import pandas as pd
import seaborn as sns
from matplotlib import rcParams
import matplotlib.pyplot as plt
import sys
from scipy import stats

rcParams.update({'figure.autolayout': True})
# Grafico de correlacion tiempo-complejidad para todos los algoritmos menos dinamica
# Dinamica tiene su propio script para graficar
metodos = ["Fuerza Bruta", "MITM", "Backtracking_simple", "Backtracking_fact", "Backtracking_opt", "Backtracking_ambas"]

complejidades = {"Fuerza Bruta": lambda x: x*(2**x), 
                 "MITM": lambda x: (x/2)*(2**(x/2)),
                 "Backtracking_simple": lambda x: (x**2)*(2**x),
                 "Backtracking_fact": lambda x: (x)*(2**x),
                 "Backtracking_opt": lambda x: (x)*(2**x),
                 "Backtracking_ambas": lambda x: (x)*(2**x),
                 }

paths = {"Fuerza Bruta": "datos/datos_random_bruta.csv", 
         "MITM": "datos/datos_random_mitm.csv",
         "Backtracking_simple": "datos/datos_random_backtracking_simple.csv",
         "Backtracking_fact": "datos/datos_random_backtracking_fact.csv",
         "Backtracking_opt": "datos/datos_random_backtracking_opt.csv",
         "Backtracking_ambas": "datos/datos_random_backtracking_ambas.csv",
         } 



def dibujar_corr(path, metodo):
    a = pd.read_csv(path).dropna()
    por_metodo = a[a.Metodo == metodo]
    por_metodo["Complejidad"] = [complejidades[metodo](i) if complejidades[metodo](i) <= sys.maxsize else np.NaN for i in por_metodo.n]
    por_metodo = por_metodo.dropna()
    por_metodo = por_metodo[por_metodo.Tiempo < por_metodo.Tiempo.quantile(0.99)]
    
    g = sns.JointGrid(por_metodo.Complejidad, por_metodo.Tiempo, ratio=100)
    g.plot_joint(sns.regplot)
    g.annotate(stats.pearsonr)
    g.ax_marg_x.set_axis_off()
    g.ax_marg_y.set_axis_off()

    plt.suptitle("Complejidad vs Tiempos obtenido para %s" % metodo)
    plt.show()

for i in metodos:
    dibujar_corr(paths[i],i)
