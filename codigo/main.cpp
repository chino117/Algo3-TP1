#include "tipos_aux.h"
#include "fuerza_bruta.hpp"
#include "mitm.hpp"
#include "backtracking_simple.hpp"
#include "backtracking_poda_fact.hpp"
#include "backtracking_poda_opt.hpp"
#include "backtracking_poda_ambas.hpp"
#include "dinamica_top_down.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <sstream>

using namespace std;

const unsigned int CANT_MODOS = 8;
const string red("\033[0;31m");
const string green("\033[1;32m");
const string yellow("\033[1;33m");
const string cyan("\033[0;36m");
const string magenta("\033[0;35m");
const string reset("\033[0m");
const string nombres_metodos[CANT_MODOS] = {"Fuerza Bruta", 
                                            "MITM", 
                                            "Backtracking_simple", 
                                            "Backtracking_fact", 
                                            "Backtracking_opt", 
                                            "Backtracking_ambas", 
                                            "Dinamica_Top_Down",
                                            "Todos"};

void Guardar_Resultados(const string& path, const ResultadoProblema& res, const DatosProblema& dp){
    fstream f(path, fstream::app | fstream::out);
    f<<dp.n<<","<<dp.W<<","<<res.b<<","<<res.tiempo.count()<<","<<nombres_metodos[res.metodo]<<",";
    if(res.nodos > 0)
        f<<res.nodos;
    f<<'\n';
    f.close();
}

void Mostrar_Ayuda()
{
    cout<<"Modo de uso: ./main <modo> [archivo de salida] <valores de entrada>\n"
    <<"Se pueden pasar los datos de entrada con parametros (en <valores de entrada>) o por el stdin usando pipes, ej: cat test.txt | ./main <modo> [archivo salida]\n"
    <<"Valores de Modo:\n";
    for(unsigned int i = 0; i < CANT_MODOS;i++)
        cout<<setw(18)<<i<<" = "<<nombres_metodos[i]<<".\n";
    cout<<"Cuando ejecuta todos los metodos (metodo 7), compara los resultados e informa cuándo difieren y cuáles métodos difieren\n";
    cout<<"Archivo de salida: Debe ser un archivo de formato .csv donde se adjutaran datos del problema como n, W, Beneficio Alcanzado, Tiempo de computo, Metodo utilizado y, para los metodos de backtracking, cantidad de nodos recorridos."<<endl;
}

int main(int argc, char** argv)
{
    DatosProblema r;

    string output;
    unsigned int modo = CANT_MODOS;

    if(argc == 1){
        Mostrar_Ayuda();
        return 0;
    }
    else if (argc == 2){
        // Solo nos dan modo
        r = leer_datos(cin);
        output = "";
        string a(argv[1]);
        stringstream modo_s(a);
        modo_s >> modo;
    }
    else if(argc == 3)
    {
        // Leemos de stdin, tenemos un archivo de output y tenemos el algoritmo a usar
        r = leer_datos(cin);
        string a(argv[1]);
        stringstream modo_s(a);
        modo_s >> modo;
        output = string(argv[2]);
    }
    else
    {
        // Leemos de los parametros de entrada
        string a(argv[1]);
        stringstream modo_s(a);
        modo_s >> modo;

        output = string(argv[2]);

        modo_s << argv[3] << ' ' << argv[4];

        modo_s >> r.n;
        modo_s >> r.W;

        int k = 5; 

        for(unsigned int i = 0; i < r.n;i++){
            unsigned int temp;
            modo_s << argv[k];
            modo_s >> temp;
            r.ws.push_back(temp);
            k++;
            modo_s << argv[k];
            modo_s >> temp;
            r.ps.push_back(temp);
            k++;
        }
    }

    if (r.n == 0){
        cout<<"Error al leer el input"<<endl;
        return 1;
    }

    // Armo el conjunto original de elementos
    ConjLineal orig(r.n, 0);
    for(ConjLineal::size_type i = 0;i < orig.size();i++)
        orig[i] = i;

    unsigned int primer_metodo = 0;
    unsigned int ultimo_metodo = modo;

    // Si ultimo_metodo == 7, vamos a correr todos los metodos y los comparamos al final
    // Si no, solo corremos el metodo determinado por modo
    if (ultimo_metodo < CANT_MODOS - 1)
        primer_metodo = ultimo_metodo;
    else
        ultimo_metodo--;

    ResultadoProblema res[CANT_MODOS - 1];
    for(unsigned int metodo = primer_metodo;metodo <= ultimo_metodo;metodo++){
        cout<<"Ejecutando metodo "<<nombres_metodos[metodo]<<endl;
        switch (metodo){
            case 0: 
                res[metodo] = Fuerza_Bruta(r, orig);
                break;
            case 1:
                res[metodo] = MITM(orig, r);
                break;
            case 2:
                res[metodo] = Backtracking_Simple(orig, r);
                break;
            case 3:
                res[metodo] = Backtracking_Fact(orig, r);
                break;
            case 4:
                res[metodo] = Backtracking_Opt(orig, r);
                break;
            case 5:
                res[metodo] = Backtracking_Ambas(orig, r);
                break;
            case 6:
                res[metodo] = Dinamica_TD(orig, r);
                break;
            default:
                break;
        }
    }

    //Comparo resultados de todos los metodos para ver si difieren
    if (modo == CANT_MODOS-1){
        bool todos_iguales = true;
        for(unsigned int i = 0;i < CANT_MODOS-1;i++){
            for(unsigned int j = i + 1;j < CANT_MODOS-1;j++){
                if(res[i].b != res[j].b){
                    cout<<red<<"ERROR: "
                    <<nombres_metodos[i]<<" difiere de "<<nombres_metodos[j]<<"\n"
                    <<res[i].b<<" "<<res[j].b<<"\n"
                    <<reset;
                    todos_iguales = false;
                }
            }
        }

        if(!todos_iguales)
            return 1;
        else{
            cout<<res[0].b<<"\n";
            for(unsigned int i = 0; i < CANT_MODOS-1;i++)
                Guardar_Resultados(output, res[i], r);
        }
    }
    else{
        // Habilitar esto para cumplir con el enunciado
        cout<<res[modo].b<<"\n";
        // Descomentar para que guarde valores de tiempo y etc
        Guardar_Resultados(output, res[modo], r);
    }
    return 0;
}
