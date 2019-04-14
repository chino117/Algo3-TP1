import os
import generador_input

for i in range(30, 61):
        caso = generador_input.crear_datos_entrada(i, 50)
        with open(f"casos_de_prueba/casos_para_todos/caso_{i}_50.txt", 'w') as f:
            f.write(caso)

# for i in range(100, 10100, 100):
#     for j in range(100, 10100, 100):
#         caso = generador_input.crear_datos_entrada(i, j)
#         with open(f"casos_de_prueba/casos_especiales/dinamica/caso_{i}_{j}.txt", 'w') as f:
#             f.write(caso)

# rango = range(5, 45, 5)

# for i in rango:
#     for j in rango:
#         caso = generador_input.crear_datos_peor_backtracking(i, j)
#         with open(f"casos_de_prueba/casos_especiales/backtracking/caso_{i}_{j}_otro.txt", 'w') as f:
#             f.write(caso)

