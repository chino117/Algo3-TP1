import sys
import os
from generador_input import *

def exp_mitm():
    for i in range(2, 80):
        a = crear_datos_entrada(i, 100)
        p = "echo {} |".format(a) + "./main 1 datos/datos_random_mitm.csv "
        if os.system(p) != 0:
            print(p)
            print("Error al correr main con el caso %d|%d" % (i, 100))
        print("(%d)"% i)

if __name__=="__main__":
    exp_mitm()
