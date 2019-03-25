import sys
import os
from generador_input import *

paths = {2: "datos/datos_random_backtracking_simple.csv",
         3: "datos/datos_random_backtracking_fact.csv", 
         4: "datos/datos_random_backtracking_opt.csv", 
         5: "datos/datos_random_backtracking_ambas.csv"}

def exp_backtracking():
    for i in range(2, 30):
        a = crear_datos_entrada(i, 100)
        for j in range(2, 6):
            p = "echo {} |".format(a) + "./main %d %s" % (j, paths[j])
            if os.system(p) != 0:
                print(p)
                print("Error al correr main con el caso %d|%d" % (i, 100))

def exp_backtracking_solo_podas():
    for i in range(2, 160):
        a = crear_datos_entrada(i, 100)
        for j in range(3, 6):
            p = "echo {} |".format(a) + "./main %d %s" % (j, paths[j])
            if os.system(p) != 0:
                print(p)
                print("Error al correr main con el caso %d|%d" % (i, 100))

def exp_backtracking_solo_opt_y_ambas():
    for i in range(2, 2000):
        a = crear_datos_entrada(i, 100)
        for j in range(4, 6):
            p = "echo {} |".format(a) + "./main %d %s" % (j, paths[j])
            if os.system(p) != 0:
                print(p)
                print("Error al correr main con el caso %d|%d" % (i, 100))

if __name__=="__main__":
    exp_backtracking()
    exp_backtracking_solo_podas()
    exp_backtracking_solo_opt_y_ambas()
