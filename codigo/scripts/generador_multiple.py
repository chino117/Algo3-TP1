import os
import generador_input

for i in range(100, 10100, 100):
    caso = generador_input.crear_datos_entrada(i, 50)
    with open(f"casos_de_prueba/casos_especiales/dinamica/caso_{i}_50.txt", 'w') as f:
        f.write(caso)
    caso = generador_input.crear_datos_entrada(50, i)
    with open(f"casos_de_prueba/casos_especiales/dinamica/caso_50_{i}.txt", 'w') as f:
        f.write(caso)
