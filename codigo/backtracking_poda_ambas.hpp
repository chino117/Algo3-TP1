#include "tipos_aux.h"
#include <algorithm>

using namespace std;

// Calculamos el beneficio maximo de una rama como si fuera parte de un problema de la mochila fraccionario
// Vamos a usar este valor como cota del beneficio que pudieramos conseguir si recorriesemos era rama en nuestro problema de la mochila
unsigned int Cota_Sup_Ambas(const ConjLineal& s, const DatosProblema& dp, int b, int t, unsigned int idx_elem){
    float res = static_cast<float>(b);
    unsigned int tamanio_usado = t;
    unsigned int tamanio_disponible = dp.W - tamanio_usado;
    while(idx_elem < s.size() && dp.ws[s[idx_elem]] <= tamanio_disponible){
        tamanio_disponible -= dp.ws[s[idx_elem]];
        res += static_cast<float>(dp.ps[s[idx_elem]]);
        idx_elem++;
    }
    if (idx_elem < s.size()){
        res += ((static_cast<float>(tamanio_disponible))/(static_cast<float>(dp.ws[s[idx_elem]])) * static_cast<float>(dp.ps[s[idx_elem]]));
    }

    return static_cast<unsigned int>(res);
}

void Solve_Backtracking_Ambas(const ConjLineal& s, const DatosProblema& dp, unsigned int b_candidato, unsigned int t_candidato, unsigned int& sol, unsigned int idx_elem, unsigned int& nodos){
    nodos++;

    if (b_candidato + dp.ps[s[idx_elem]] > sol && t_candidato + dp.ws[s[idx_elem]] <= dp.W){
        sol = b_candidato + dp.ps[s[idx_elem]];

        /* cout<<"Cambio la solucion en nodo "<<idx_elem<<endl; */
        /* cout<<"#Nodo: "<<nodos<<"| Beneficio: "<<b_candidato + dp.ps[s[idx_elem]] <<endl; */ 
    }

    /* cout<<"Nodo idx: "<<idx_elem<<"| Beneficio: "<<dp.ps[s[idx_elem]]<<"| Peso: "<<dp.ws[s[idx_elem]]<<endl; */

    if (idx_elem < s.size()){
        if(t_candidato + dp.ws[s[idx_elem]] <= dp.W){
            b_candidato += dp.ps[s[idx_elem]];
            t_candidato += dp.ws[s[idx_elem]];
            Solve_Backtracking_Ambas(s, dp, b_candidato, t_candidato,sol, idx_elem+1, nodos);
            b_candidato -= dp.ps[s[idx_elem]];
            t_candidato -= dp.ws[s[idx_elem]];

        }
        if (Cota_Sup_Ambas(s, dp, b_candidato, t_candidato, idx_elem+1) > sol) 
            Solve_Backtracking_Ambas(s, dp, b_candidato, t_candidato,sol, idx_elem+1, nodos);
    }
}

ResultadoProblema Backtracking_Ambas(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    ConjLineal orig(s);
    auto start_time = chrono::steady_clock::now();

    sort(orig.begin(), orig.end(), [dp](const int& a, const int& b){
            return !((static_cast<float>(dp.ps[a])/static_cast<float>(dp.ws[a])) < (static_cast<float>(dp.ps[b])/static_cast<float>(dp.ws[b])));
            });
    Solve_Backtracking_Ambas(orig, dp, 0, 0, res.b, 0, res.nodos);

    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    /* cout<<"Nodos recorridos backtracking ambas: "<<res.nodos<<endl; */

    res.metodo = 5;
    res.tiempo = chrono::duration <double, milli> (diff_time);

    return res;
}
