import os
import subprocess

def compilar(path):
    prev = os.getcwd()
    os.chdir(path)
    r = subprocess.call(["make", "all"])
    os.chdir(prev)
    return r

def preparar_entorno():
    main_dir = exp_dir = os.getcwd()
    if main_dir.split(os.sep)[-1] != "codigo":
        main_dir = os.path.join("/", *main_dir.split(os.sep)[:-1])

    casos_dir = os.path.join(main_dir, "casos_de_prueba")
    casos_todos_dir = os.path.join(casos_dir, "casos_para_todos")
    casos_random_dir = os.path.join(casos_dir, "casos_random")
    casos_especiales_dir = os.path.join(casos_dir, "casos_especiales")

    datos_dir = os.path.join(main_dir, "datos")

    scripts_dir = os.path.join(main_dir, "scripts")

    if (compilar(main_dir) > 0):
        print("Error al compilar")
        exit(-1)

    return {"main": main_dir,
            "exp": exp_dir,
            "casos": casos_dir,
            "casos_todos": casos_todos_dir,
            "casos_random": casos_random_dir,
            "casos_especiales": casos_especiales_dir,
            "datos": datos_dir,
            "scripts": scripts_dir}

