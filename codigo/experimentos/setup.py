import os
import subprocess
import pandas as pd
import numpy as np

def compilar(path):
    '''

    Ejecuta el Makefile que se encuentra en la carpeta indicada por el path

    '''
    prev = os.getcwd()
    os.chdir(path)
    r = subprocess.call(["make", "all"])
    os.chdir(prev)
    return r

def filtrar_tiempos_outliers(data):
    '''

    Filtra outliers de los tiempos medidos para cada n del DataFrame data.
    Asume solo un tipo de metodo y un solo valor de W.
    Ignora b.

    '''
    res = pd.DataFrame(columns=["n", "Tiempo", "Metodo", "W", "nodos"])
    res.n = sorted(data.n.unique())

    cada_n = [data[data.n == i] for i in sorted(data.n.unique())]

    # Tomamos el desvio estandar de los tiempos de cada n
    stds = pd.Series([i.Tiempo.std(ddof=0) for i in cada_n])
    stds.index = sorted(data.n.unique())

    # Para cada n, tomamos aquellos tiempos que no excedan 3 veces el desvio estandar
    tiempos_filtrados = [pd.Series([j for j in data[data.n == i].Tiempo if abs(j-data[data.n == i].Tiempo.mean()) <= 3*stds[i]])  for i in sorted(data.n.unique())]

    # Para los tiempos filtrados, tomamos la media y asignamos a cada n la media correspondiente
    tiempo_final = []
    for i in tiempos_filtrados:
        tiempo_final.append(i.mean())
    res.Tiempo = pd.Series(tiempo_final)

    if data.nodos.isna().sum() < data.nodos.count():
        # Tomamos el desvio estandar de los nodos de cada n
        stds = pd.Series([i.nodos.fillna(0).std(ddof=0) for i in cada_n])
        stds.index = sorted(data.n.unique())

        # Para cada n, tomamos aquellos tiempos que no excedan 3 veces el desvio estandar
        nodos_filtrados = [pd.Series([j for j in data[data.n == i].nodos if abs(j-data[data.n == i].nodos.mean()) <= 3*stds[i]])  for i in sorted(data.n.unique())]

        # Para los tiempos filtrados, tomamos la media y asignamos a cada n la media correspondiente
        nodos_final = []
        for i in nodos_filtrados:
            nodos_final.append(i.mean())
        res.nodos = pd.Series(nodos_final)
    else:
        res.nodos = np.nan 

    # Como todas las muestras provienen del mismo Metodo, le asignamos ese metodo al resultado
    res.Metodo = data.Metodo.unique()[0]

    # Como todas las muestras provienen del mismo W, le asignamos ese W al resultado
    res.W = data.W.unique()[0]

    return res
    
def filtrar_tiempos_outliers_mult_var(data):
    '''

    Filtra outliers de los tiempos medidos para cada n y W del DataFrame data.
    Asume solo un tipo de metodo.
    Ignora b y nodos.

    '''
    res = pd.DataFrame(columns=["n","W", "Tiempo", "Metodo"]) 
    cada_nw = data.drop_duplicates()[["n", "W"]].sort_values(["n", "W"])

    # Tomamos el desvio estandar de los tiempos de cada n y w
    stds = pd.DataFrame(columns=["n", "W", "stddev"])
    stds.n = cada_nw.n
    stds.W = cada_nw.W
    stds.stddev = stds.apply(lambda row: data[(data.n == row.n) & (data.W == row.W)].Tiempo.std(ddof=0), axis=1)

    metodo =  data.Metodo.unique()[0]
    # # Para cada n, tomamos aquellos tiempos que no excedan 3 veces el desvio estandar
    tiempos_filtrados = []
    for i in stds.itertuples():
        actual = data[(data.n == i.n) & (data.W == i.W)]
        tiempos_actual = []
        media_actual = actual.Tiempo.mean()
        for j in actual.Tiempo:
            if abs(j - media_actual) <= 3*i.stddev:
                tiempos_actual.append(j)
        media_final = pd.Series(tiempos_actual).mean()
        res.loc[len(res)] = [i.n, i.W, media_final, metodo]

    return res

def preparar_entorno():
    '''

    Compila el tp y devuelve un diccionario con los paths de cada carpeta a utilizar

    '''

    main_dir = exp_dir = os.getcwd()
    if main_dir.split(os.sep)[-1] != "codigo":
        main_dir = os.path.join("/", *main_dir.split(os.sep)[:-1])

    casos_dir = os.path.join(main_dir, "casos_de_prueba")
    casos_todos_dir = os.path.join(casos_dir, "casos_para_todos")
    casos_random_dir = os.path.join(casos_dir, "casos_random")
    casos_especiales_dir = os.path.join(casos_dir, "casos_especiales")

    datos_dir = os.path.join(main_dir, "datos")

    scripts_dir = os.path.join(main_dir, "scripts")

    if (compilar(main_dir) > 0):
        print("Error al compilar")
        exit(-1)

    return {"main": main_dir,
            "exp": exp_dir,
            "casos": casos_dir,
            "casos_todos": casos_todos_dir,
            "casos_random": casos_random_dir,
            "casos_especiales": casos_especiales_dir,
            "datos": datos_dir,
            "scripts": scripts_dir}

