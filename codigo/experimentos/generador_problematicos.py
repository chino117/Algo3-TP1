import setup
import os 

paths = setup.preparar_entorno()

def crear_caso_problematico_backtracking(n, W):
    '''
    Crea un caso problematico para nuestra implementacion de backtracking segun n y W.
    Requiere n <= W
    '''
    head = [f"{n} {W}"]
    sol = [f"{W} {W*n}"]

    # (W/n) (<= W) para (1, n-1)
    otros = [f"{int(W/n)} {W}" for i in range(0, n-1)]

    elems = head + sol + otros

    return "\n".join(elems)

if __name__=="__main__":
    for i in range(5, 41):
        path = os.path.join(paths["casos_especiales"], os.path.join("backtracking", f"caso_problematico_{i}_50.txt"))
        with open(path, 'w') as f:
            problema = crear_caso_problematico_backtracking(i, 50)
            f.write(problema)

