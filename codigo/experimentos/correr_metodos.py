import setup
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os
import subprocess

metodos = ["datos_fuerza_bruta.csv", "datos_mitm.csv", "datos_backtracking.csv", "datos_dinamica.csv"]

paths = setup.preparar_entorno()
exe = os.path.join(paths["main"],"main")

def correr_metodos(desde, hasta, path_datos, out_name=None):
    for i in os.listdir(path_datos):
        for j in range(desde, hasta):
            print(f"Corriendo exp {i} con metodo {j}")
            inp = os.path.join(path_datos, i)
            out = os.path.join(paths["datos"], out_name if out_name else metodos[j])
            command = f"cat {inp} | ./main {j} {out}"
            status = os.system(command) 
            if(status > 0):
                print(f"ERROR al ejecutar el caso {i} con metodo {j}")

def correr_todos_metodos():
    print("Corriendo experimentos de todos los metodos")
    correr_metodos(0, len(metodos), paths["casos_todos"])
    print("Fin experimentos")

def correr_mitm():
    print("Corriendo experimentos de todos los metodos")
    correr_metodos(1, 2, paths["casos_todos"])
    print("Fin experimentos")

def correr_back_y_dinamica():
    print("Corriendo experimentos de back y dinamica")
    correr_metodos(2, len(metodos), paths["casos_random"])
    print("Fin experimentos")

def correr_comparar_back_y_dinamica():
    print("Corriendo experimentos de back y dinamica")
    correr_metodos(5, 6, paths["casos_random"], "derp.csv")
    print("Fin experimentos")

def correr_exp_especial_back():
    print("Corriendo experimentos de input especial de back")
    correr_metodos(2, 3, os.path.join(paths["casos_especiales"], "backtracking"), "datos_problematico_backtracking.csv")
    print("Fin experimentos")

def correr_exp_especial_dinamica():
    print("Corriendo experimentos de input especial de dinamica")
    correr_metodos(3, 4, os.path.join(paths["casos_especiales"], "dinamica"), "datos_especial_dinamica.csv")
    print("Fin experimentos")

if __name__=="__main__":
    # correr_mitm()
    # correr_todos_metodos()
#     correr_back_y_dinamica()
    # correr_exp_especial_back()
#     correr_exp_especial_dinamica()
#     # correr_comparar_back_y_dinamica()
