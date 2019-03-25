#include "tipos_aux.h"

// Calculamos el beneficio maximo de una rama como si fuera parte de un problema de la mochila fraccionario
// Vamos a usar este valor como cota del beneficio que pudieramos conseguir si recorriesemos era rama en nuestro problema de la mochila
unsigned int Cota_Sup_Opt(const ConjLineal& s, const DatosProblema& dp, int b, int t, unsigned int idx_elem){
    float res = (float)b;
    int tamanio_usado = t;
    int tamanio_disponible = dp.W - tamanio_usado;
    while(idx_elem < s.size() && dp.ws[s[idx_elem]] <= tamanio_disponible){
        tamanio_disponible -= dp.ws[s[idx_elem]];
        res += (float)dp.ps[s[idx_elem]];
        idx_elem++;
    }
    if (idx_elem < s.size()){
        res += (((float)(tamanio_disponible))/(float)dp.ws[s[idx_elem]]) * (float)dp.ps[s[idx_elem]];
    }

    return (unsigned int)res;
}

void Solve_Backtracking_Opt(const ConjLineal& s, const DatosProblema& dp, int b_candidato, int t_candidato, unsigned int& sol, unsigned int idx_elem, int& nodos){
    nodos++;
    if (idx_elem == s.size() && (unsigned int)b_candidato > sol){
        sol = (unsigned int)b_candidato;
        return;
    }
    if(idx_elem == s.size())return;
    // Si el elemento actual idx_elem entra en la mochila, lo tomamos y vemos el resto de las soluciones que lo consideran
    if(t_candidato + dp.ws[s[idx_elem]] <= dp.W){
        b_candidato += dp.ps[s[idx_elem]];
        t_candidato += dp.ws[s[idx_elem]];
        Solve_Backtracking_Opt(s, dp, b_candidato, t_candidato,sol, idx_elem+1, nodos);
        b_candidato -= dp.ps[s[idx_elem]];
        t_candidato -= dp.ws[s[idx_elem]];
    }

    // Sin considerar al elemento idx_elem, vemos si hay alguna solución "buena" segun nuestra cota sup
    // Si la hay, hacemos backtracking. Si no la hay, tampoco la va a haber en algun otro idx_elem, ya que
    // Por haber ordenado los elementos en orden decreciente de b/w, idx_elem+1 va a ser el de mayor b/w
    if (Cota_Sup_Opt(s, dp, b_candidato, t_candidato, idx_elem+1) > sol)
        Solve_Backtracking_Opt(s, dp, b_candidato, t_candidato,sol, idx_elem+1, nodos);
    return;
}

ResultadoProblema Backtracking_Opt(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    ConjLineal orig(s);
    auto start_time = std::chrono::steady_clock::now();
    unsigned int b = 0;
    std::sort(orig.begin(), orig.end(), [dp](const int& a, const int& b){
            return !(((float)dp.ps[a]/(float)dp.ws[a]) < ((float)dp.ps[b]/(float)dp.ws[b]));
            });
    Solve_Backtracking_Opt(orig, dp, 0, 0, b, 0, res.nodos);

    auto end_time = std::chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    res.b = b;
    res.metodo = 4;
    res.tiempo = std::chrono::duration <double, std::milli> (diff_time);

    return res;
}
