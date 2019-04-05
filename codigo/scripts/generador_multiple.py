import os
import generador_input

for i in range(5, 30):
    caso = generador_input.crear_datos_entrada(i, 50)
    with open(f"../casos_de_prueba/casos_para_todos/caso_{i}_50.txt", 'w') as f:
        f.write(caso)
