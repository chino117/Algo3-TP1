import sys
import os
from generador_input import *

def exp_bruta():
    for i in range(2, 50):
        a = crear_datos_entrada(i, 100)
        p = "echo {} |".format(a) + "./main 0 datos/datos_random_bruta.csv "
        if os.system(p) != 0:
            print(p)
            print("Error al correr main con el caso %d|%d" % (i, 100))
        print("(%d)"% i)

if __name__=="__main__":
    exp_bruta()
