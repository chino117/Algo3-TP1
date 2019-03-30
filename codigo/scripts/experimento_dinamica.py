import sys
import os
from generador_input import *

def exp_dinamica():
    for c in range(1000, 100000, 1000):
        for i in range(1000, 10000, 1000):
            a = crear_datos_entrada(i, c)
            p = "echo {} | ./main 7 datos/datos_random_dinamica.csv ".format(a)
            if os.system(p) != 0:
                print("Error al correr main con el caso %d|%d" % (i, c))
            print("(%d %d)"% (c, i))

if __name__=="__main__":
    exp_dinamica()
