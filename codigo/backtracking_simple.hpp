#include "tipos_aux.h"

using namespace std;

// Backtracking sin podas, es parecido a fuerza bruta
void Solve_Backtracking_Simple(const ConjLineal& s, const DatosProblema& dp, unsigned int b_candidato, unsigned int t_candidato, unsigned int& sol, unsigned int idx_elem, unsigned int& nodos){
    nodos++;
    if(b_candidato + dp.ps[s[idx_elem]] > sol && t_candidato + dp.ws[s[idx_elem]] <= dp.W){
        sol = b_candidato + dp.ps[s[idx_elem]];
        /* cout<<"Cambio la solucion en nodo "<<idx_elem<<endl; */
        /* cout<<"#Nodo: "<<nodos<<"| Beneficio: "<<b_candidato<<endl; */ 
    }

    /* cout<<"Nodo idx: "<<idx_elem<<"| Beneficio: "<<dp.ps[s[idx_elem]]<<"| Peso: "<<dp.ws[s[idx_elem]]<<endl; */

    if(idx_elem < s.size()){
        // Si el elemento actual entra, lo agrego y busco las soluciones que lo contengan
        if(t_candidato + dp.ws[s[idx_elem]] <= dp.W){
            b_candidato += dp.ps[s[idx_elem]];
            t_candidato += dp.ws[s[idx_elem]];
            if(idx_elem+1 < s.size())
                Solve_Backtracking_Simple(s, dp, b_candidato, t_candidato, sol, idx_elem+1, nodos);
            b_candidato -= dp.ps[s[idx_elem]];
            t_candidato -= dp.ws[s[idx_elem]];
        }
        if(idx_elem+1 < s.size()) 
            Solve_Backtracking_Simple(s, dp, b_candidato, t_candidato, sol, idx_elem+1, nodos);
    }
}

ResultadoProblema Backtracking_Simple(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    auto start_time = chrono::steady_clock::now();

    Solve_Backtracking_Simple(s, dp, 0, 0, res.b, 0, res.nodos);

    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    //cout<<"Total nodos recorridos backtracking simple: "<<res.nodos<<endl;
    res.metodo = 2;
    res.tiempo = chrono::duration <double, milli> (diff_time);

    return res;
}
