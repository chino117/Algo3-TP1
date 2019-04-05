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

    if(idx_elem+1 < s.size()){
        // Si quedan posibles soluciones por ver y el elemento actual entra, 
        // lo agrego y busco las soluciones que lo contengan
        if(t_candidato + dp.ws[s[idx_elem]] <= dp.W){
            b_candidato += dp.ps[s[idx_elem]];
            t_candidato += dp.ws[s[idx_elem]];
            Solve_Backtracking_Simple(s, dp, b_candidato, t_candidato, sol, idx_elem+1, nodos);
            b_candidato -= dp.ps[s[idx_elem]];
            t_candidato -= dp.ws[s[idx_elem]];
        }
        Solve_Backtracking_Simple(s, dp, b_candidato, t_candidato, sol, idx_elem+1, nodos);
    }
}

void Solver_Backtracking_Simple2(const ConjLineal& s, const DatosProblema& dp, vector<bool> parcial, unsigned int& nodos, bool& encontre, unsigned int& sol){
    nodos++;
    if(parcial.size() == s.size()){
        unsigned int b_sum = 0;
        unsigned int t_sum = 0;
        for(vector<bool>::size_type i = 0;i < parcial.size();i++){
            if(parcial[i]){
                b_sum += dp.ps[s[i]];
                t_sum += dp.ws[s[i]];
            }
        }
        if(b_sum > sol && t_sum <= dp.W){
            encontre = true;
            sol = b_sum;
        }
    }
    
    for(unsigned int i = 0;i < s.size();i++){
        unsigned int b_sum = 0;
        unsigned int t_sum = 0;
        for(vector<bool>::size_type i = 0;i < parcial.size();i++){
            if(parcial[i]){ 
                b_sum += dp.ps[s[i]];
                t_sum += dp.ws[s[i]];
            }
        }
        bool sirveParcial = t_sum <= dp.W; 
        if(sirveParcial){
            parcial.push_back(true);
            Solver_Backtracking_Simple2(s, dp, parcial, nodos, encontre, sol);
            parcial.pop_back();
        }
    }
}


ResultadoProblema Backtracking_Simple(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    auto start_time = chrono::steady_clock::now();

    Solve_Backtracking_Simple(s, dp, 0, 0, res.b, 0, res.nodos);
    /* vector<bool> parcial; */
    /* bool encontre; */
    /* Solver_Backtracking_Simple2(s, dp, parcial, res.nodos, encontre, res.b); */

    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    //cout<<"Total nodos recorridos backtracking simple: "<<res.nodos<<endl;
    res.metodo = 2;
    res.tiempo = chrono::duration <double, milli> (diff_time);

    return res;
}
