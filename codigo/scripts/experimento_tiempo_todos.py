import sys
import os
from generador_input import *

def exp_todos():
    for j in range (0, 5):
        for i in range(2, 30):
            a = crear_datos_entrada(i, 100)
            p = "echo {} | ./main 8 datos/datos_random_todos.csv".format(a)
            if os.system(p) != 0:
                print(p)
                print("Error al correr main con el caso %d|%d" % (i, 100))

if __name__=="__main__":
    exp_todos()
