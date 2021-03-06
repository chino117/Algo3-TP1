#! /usr/bin/python3
import setup
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os
import subprocess

metodos = ["datos_fuerza_bruta.csv", "datos_backtracking.csv", "datos_dinamica.csv"]

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
    correr_metodos(0, 3, paths["casos_todos"])
    print("Fin experimentos")

def correr_back_y_dinamica():
    print("Corriendo experimentos de back y dinamica")
    correr_metodos(1, 3, paths["casos_random"])
    print("Fin experimentos")

def correr_exp_problematico_backtracking():
    print("Corriendo experimentos de input problematico de backtracking")
    correr_metodos(1, 2, os.path.join(paths["casos_especiales"], "backtracking"), "datos_problematico_backtracking.csv")
    print("Fin experimentos")

def correr_exp_especial_dinamica():
    print("Corriendo experimentos de input especial de dinamica")
    correr_metodos(2, 3, os.path.join(paths["casos_especiales"], "dinamica"), "datos_especial_dinamica.csv")
    print("Fin experimentos")

def correr_exp_especial_backtracking():
    print("Corriendo experimentos de input especial de backtracking")
    correr_metodos(1, 2, os.path.join(paths["casos_especiales"], "dinamica"), "datos_especial_backtracking.csv")
    print("Fin experimentos")

if __name__=="__main__":
    # correr_todos_metodos()
#     correr_back_y_dinamica()
    # correr_exp_problematico_backtracking()
#     correr_exp_especial_dinamica()
    correr_exp_especial_backtracking()
