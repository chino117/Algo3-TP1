#include "tipos_aux.h"

using namespace std;

// Backtracking sin podas, es parecido a fuerza bruta
void Solve_Backtracking_Simple(const ConjLineal& s, const DatosProblema& dp, ConjLineal& candidato, unsigned int& sol, unsigned int idx_elem, unsigned int& nodos){
    nodos++;

    unsigned int b_nodo = beneficio_conj(candidato, dp);
    //cout<<"Nodo: "<<nodos<<"| Beneficio: "<<b_nodo<<endl; 
    if (b_nodo > sol && tamanio_conj(candidato, dp) <= dp.W)
        sol = b_nodo;

    for(unsigned int i = idx_elem; i < s.size();i++){
        candidato.push_back(s[i]);
        Solve_Backtracking_Simple(s, dp, candidato, sol, i+1, nodos);
        candidato.pop_back();
    }
}

ResultadoProblema Backtracking_Simple(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    auto start_time = chrono::steady_clock::now();

    ConjLineal temp;
    Solve_Backtracking_Simple(s, dp, temp, res.b, 0, res.nodos);

    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    //cout<<"Total nodos recorridos backtracking simple: "<<res.nodos<<endl;
    res.metodo = 2;
    res.tiempo = chrono::duration <double, milli> (diff_time);

    return res;
}
