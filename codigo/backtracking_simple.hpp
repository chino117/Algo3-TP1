#include "tipos_aux.h"

using namespace std;

// Backtracking sin podas, es parecido a fuerza bruta
void Solve_Backtracking_Simple(const ConjLineal& s, const DatosProblema& dp, ConjLineal& candidato, unsigned int& sol, int idx_elem, unsigned int& nodos){
    nodos++;
    cout<<"Nodo: "<<nodos<<"| Beneficio: "<<beneficio_conj(candidato, dp)<<endl; 
    if (beneficio_conj(candidato, dp) > sol && tamanio_conj(candidato, dp) <= dp.W)
        sol = beneficio_conj(candidato, dp);
    for(int i = idx_elem; i < (int)s.size();i++){
        candidato.push_back(s[i]);
        Solve_Backtracking_Simple(s, dp, candidato, sol, i+1, nodos);
        candidato.pop_back();
    }
    return;
}

ResultadoProblema Backtracking_Simple(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    auto start_time = chrono::steady_clock::now();

    ConjLineal temp;
    Solve_Backtracking_Simple(s, dp, temp, res.b, 0, res.nodos);

    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    cout<<"Total nodos recorridos backtracking simple: "<<res.nodos<<endl;
    res.metodo = 2;
    res.tiempo = chrono::duration <double, milli> (diff_time);

    return res;
}
