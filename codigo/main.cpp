#include "tipos_aux.h"
#include "fuerza_bruta.hpp"
#include "mitm.hpp"
#include "backtracking_poda_fact.hpp"
#include "backtracking_poda_opt.hpp"
#include "backtracking_poda_ambas.hpp"
#include "backtracking_simple.hpp"
#include "dinamica_bottom_up.hpp"
#include "dinamica_top_down.hpp"
#include <string>
#include <chrono>
#include <cstdlib>

void Guardar_Resultados(const std::string& path, const ResultadoProblema& res, const DatosProblema& dp){
    std::string nombres_metodos[8] = {"Fuerza Bruta", 
                                      "MITM", 
                                      "Backtracking_simple", 
                                      "Backtracking_fact", 
                                      "Backtracking_opt", 
                                      "Backtracking_ambas", 
                                      "Dinamica_Bottom_Up",
                                      "Dinamica_Top_Down"};
    std::fstream f(path, std::fstream::app | std::fstream::out);
    f<<dp.n<<","<<dp.W<<","<<res.b<<","<<res.tiempo.count()<<","<<nombres_metodos[res.metodo]<<",";
    if(res.nodos > 0)
        f<<res.nodos;
    f<<'\n';
    f.close();
}

void Mostrar_Ayuda()
{
    std::cout<<"Modo de uso: ./main <modo> [archivo de salida] <valores de entrada>"<<std::endl;
    std::cout<<"Se pueden pasar los datos de entrada com parametros (en <valores de entrada>) o por el stdin usando pipes, ej: cat test.txt | ./main <modo> [archivo salida]\n";
    std::cout<<"Valores de Modo: 0 = Fuerza bruta.\n";
    std::cout<<"                 1 = MITM.\n";
    std::cout<<"                 2 = Backtracking sin podas.\n";
    std::cout<<"                 3 = Backtracking con poda factibilidad.\n";
    std::cout<<"                 4 = Backtracking con poda optimalidad.\n";
    std::cout<<"                 5 = Backtracking ambas podas.\n";
    std::cout<<"                 6 = Programacion Dinamica Bottom-Up.\n";
    std::cout<<"                 7 = Programacion Dinamica Top-Down.\n";
    std::cout<<"                 8 = Corre todos los metodos y compara sus resultados, si alguno difiere, informa. Ignora archivo salida\n";
    std::cout<<"Archivo de salida: Debe ser un archivo de formato .csv donde se adjutaran datos del problema como n, W, Beneficio Alcanzado, Tiempo de computo y Metodo utilizado.\n";
}

int main(int argc, char** argv)
{
    DatosProblema r;
    r.n = -1;
    r.W = -1;

    std::string output;
    int modo = 8;

    if(argc == 1){
        Mostrar_Ayuda();
        return 0;
    }
    else if (argc == 2){
        // Solo nos dan modo
        r = leer_datos(std::cin);
        output = "";
        modo = (int)std::strtol(argv[1], NULL, 10);
    }
    else if(argc == 3)
    {
        // Leemos de stdin, tenemos un archivo de output y tenemos el algoritmo a usar
        r = leer_datos(std::cin);
        modo = (int)std::strtol(argv[1], NULL, 10);
        output = std::string(argv[2]);
    }
    else
    {
        // Leemos de los parametros de entrada
        modo = (int)std::strtol(argv[1], NULL, 10);
        output = std::string(argv[2]);
        r.n = (int)std::strtol(argv[3], NULL, 10);
        r.W = (int)std::strtol(argv[4], NULL, 10);
        int k = 5; 
        for(int i = 0; i < r.n;i++){
            r.ws.push_back((int)std::strtol(argv[k], NULL, 10));
            k++;
            r.ps.push_back((int)std::strtol(argv[k], NULL, 10));
            k++;
        }
    }

    if (r.n == -1){
        std::cout<<"Error al leer el input\n";
        return 1;
    }

    // Armo el conjunto original de elementos
    ConjLineal orig(r.n, 0);
    for(int i = 0;i < (int)orig.size();i++)
        orig[i] = i;

    int primer_metodo = 0;
    int ultimo_metodo = modo;

    // Si ultimo_metodo == 8, vamos a correr todos los metodos y los comparamos al final
    // Si no, solo corremos el metodo determinado por modo
    if (ultimo_metodo < 8)
        primer_metodo = ultimo_metodo;
    else
        ultimo_metodo--;

    ResultadoProblema res[8];
    for(int metodo = primer_metodo;metodo <= ultimo_metodo;metodo++){
        // Cambiar a switch
        if (metodo == 0)
            res[metodo] = Fuerza_Bruta(r, orig);
        else if (metodo == 1)
            res[metodo] = MITM(orig, r);
        else if (metodo == 2)
            res[metodo] = Backtracking_Simple(orig, r);
        else if (metodo == 3)
            res[metodo] = Backtracking_Fact(orig, r);
        else if (metodo == 4)
            res[metodo] = Backtracking_Opt(orig, r);
        else if (metodo == 5)
            res[metodo] = Backtracking_Ambas(orig, r);
        else if (metodo == 6)
            res[metodo] = Dinamica_BU(orig, r);
        else if (metodo == 7)
            res[metodo] = Dinamica_TD(orig, r);
    }

    if (modo == 8){
        bool todos_iguales = true;
        for(int i = 0;i < 8;i++){
            for(int j = i + 1;j < 8;j++){
                if(res[i].b != res[j].b){
                    std::cout<<i<<" difiere de "<<j<<"\n";
                    std::cout<<res[i].b<<" "<<res[j].b<<"\n";
                    todos_iguales = false;
                }
            }
        }

        if(!todos_iguales)
            return 1;
        // Descomentar para que guarde en el archivo output los valores para cada algoritmo
        else{
            std::cout<<res[0].b<<"\n";
            for(int i = 0; i < 8;i++)
                Guardar_Resultados(output, res[i], r);
        }
    }
    else{
        // Habilitar esto para cumplir con el enunciado
        std::cout<<res[modo].b<<"\n";
        // Descomentar para que guarde valores de tiempo y etc
        Guardar_Resultados(output, res[modo], r);
    }

    return 0;
}
