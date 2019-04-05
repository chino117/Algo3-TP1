#include "tipos_aux.h"
#include <algorithm>

using namespace std;

void Solve_Backtracking_Fact(const ConjLineal& s, const DatosProblema& dp, unsigned int b_candidato, unsigned int t_candidato, unsigned int& sol, unsigned int idx_elem, unsigned int& nodos){
    nodos++;

    if(b_candidato + dp.ps[s[idx_elem]] > sol && t_candidato + dp.ws[s[idx_elem]] <= dp.W){
        sol = b_candidato + dp.ps[s[idx_elem]];
        /* cout<<"Cambio la solucion en nodo "<<idx_elem<<endl; */
        /* cout<<"#Nodo: "<<nodos<<"| Beneficio: "<<b_candidato<<endl; */ 
    }

    /* cout<<"Nodo idx: "<<idx_elem<<"| Beneficio: "<<dp.ps[s[idx_elem]]<<"| Peso: "<<dp.ws[s[idx_elem]]<<endl; */

    if(idx_elem+1 < s.size()){
        // Si el elemento actual entra, lo agrego y busco las soluciones que lo contengan
        // Ademas si el elemento del proximo idx_elem entra
        // vemos las soluciones de ver ese idx_elem. Si no, al estar ordenado S
        // En orden creciente por tamaño, las demas soluciones tampoco entran
        // Por lo que los ignoramos

        if(t_candidato + dp.ws[s[idx_elem]] <= dp.W){
            b_candidato += dp.ps[s[idx_elem]];
            t_candidato += dp.ws[s[idx_elem]];
            if(t_candidato + dp.ws[s[idx_elem+1]] <= dp.W) 
                Solve_Backtracking_Fact(s, dp, b_candidato, t_candidato, sol, idx_elem+1, nodos);
            b_candidato -= dp.ps[s[idx_elem]];
            t_candidato -= dp.ws[s[idx_elem]];
        }
        // Sin considerar el item actual, si el elemento del proximo idx_elem entra
        // Vemos las soluciones de ver ese idx_elem. Si no, al estar ordenado S
        // En orden creciente por tamaño, las demas soluciones tampoco entran
        // Por lo que los ignoramos
        if(t_candidato + dp.ws[s[idx_elem+1]] <= dp.W) 
            Solve_Backtracking_Fact(s, dp, b_candidato, t_candidato, sol, idx_elem+1, nodos);
    }
}

ResultadoProblema Backtracking_Fact(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    ConjLineal orig(s);
    auto start_time = chrono::steady_clock::now();

    sort(orig.begin(), orig.end(), [dp](const int& a, const int& b){
            return (dp.ws[a] < dp.ws[b]);
            });

    Solve_Backtracking_Fact(orig, dp, 0, 0, res.b, 0, res.nodos);

    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    /* cout<<"Nodos recorridos backtracking fact: "<<res.nodos<<endl; */
    res.metodo = 3;
    res.tiempo = chrono::duration <double, milli> (diff_time);

    return res;
}
