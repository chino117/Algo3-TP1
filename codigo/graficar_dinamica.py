import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
from scipy import stats
from matplotlib import rcParams

rcParams.update({'figure.autolayout': True})
datos = pd.read_csv("datos/datos_random_dinamica.csv")
    
complejidad = datos.n * datos.W
datos["Complejidad"] = pd.Series(complejidad)

datos_corr = datos.groupby(["n", "W"]).mean()
    
g = sns.JointGrid(datos_corr.Complejidad, datos_corr.Tiempo, ratio=100)
g.plot_joint(sns.regplot)
g.annotate(stats.pearsonr)
g.ax_marg_x.set_axis_off()
g.ax_marg_y.set_axis_off()

plt.show()
