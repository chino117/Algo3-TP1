import random

def crear_datos_entrada(i, c):
    cant_elem = i
    capacidad = c
    m = dict()
    l = []
    l.append(str(cant_elem))
    l.append(str(capacidad))
    for j in range(0, i):
        w = str(random.randrange(1, c))
        v = str(random.randrange(1, 100))
        l.append(w)
        l.append(v)
    return " ".join(l)

def crear_datos_entrada_ordenados(i, c, porTamaño=True, creciente=True):
    cant_elem = i
    capacidad = c
    m = dict()
    l = []
    l.append(str(cant_elem))
    l.append(str(capacidad))
    datos = [(str(random.randrange(1, c)), str(random.randrange(1, 100))) for j in range(0, i)]
    datos.sort(key=lambda s: s[int(porTamaño)], reverse= not creciente)
    for i in datos:
        l.append(i[1])
        l.append(i[0])
    return " ".join(l)

if __name__ == "__main__":
    data = crear_datos_entrada(5, 20)
    print(data)
