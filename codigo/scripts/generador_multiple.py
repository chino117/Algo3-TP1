import os
import generador_input

for i in range(100, 10100, 100):
    for j in range(100, 10100, 100):
        caso = generador_input.crear_datos_entrada(i, j)
        with open(f"casos_de_prueba/casos_especiales/dinamica/caso_{i}_{j}.txt", 'w') as f:
            f.write(caso)
