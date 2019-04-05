import argparse
import numpy.random as random
import matplotlib.pyplot as plt
import pandas as pd

def elegir_dist(dist):
    if(dist == "u"):
        f = random.random_integers;
    elif(dist == "n"):
        f = lambda x, y: int(((abs(random.standard_normal()) + x) * y) % y)
    else:
        f = lambda x, y: int(((random.exponential() + x) * y) % y)
    return f

def crear_datos_entrada(n, W, dist="u"):
    f = elegir_dist(dist)
    m = dict()
    l = [str(n), str(W)]
    l.extend([k for j in range(0, n) for k in (str(f(1, W)), str(f(1, 100)))])
    return " ".join(l)

def crear_datos_entrada_ordenados(n, W, dist, porTamanio=True, creciente=True):
    f = elegir_dist(dist)
    m = dict()
    l = [str(n), str(W)]
    datos = [(str(f(1, W)), str(f(1, 100))) for j in range(0, n)]
    datos.sort(key=lambda s: s[int(porTamanio)], reverse= not creciente)
    for i in datos:
        l.append(i[1])
        l.append(i[0])
    return " ".join(l)

if __name__ == "__main__":
    parser = argparse.ArgumentParser("Generador de casos aleatorios segun una distribucion dada")
    parser.add_argument("--n", help="Cantidad de elementos a seleccionar", type=int)
    parser.add_argument("--w", help="Capacidad maxima de la mochila", type=int)
    parser.add_argument("--dist", help="Tipo de distribucion de donde generar datos (u=uniforme, e=exponencial, n=normal)", default="u")

    args = parser.parse_args()
    data = crear_datos_entrada(args.n, args.w, args.dist)
    print(data)
