#include "tipos_aux.h"

void Solve_Backtracking_Fact(const ConjLineal& s, const DatosProblema& dp, int b_candidato, int t_candidato, unsigned int& sol, unsigned int idx_elem, int& nodos){
    nodos++;
    if (idx_elem <= s.size() && (unsigned int)b_candidato > sol)
        sol = (unsigned int)b_candidato;
    if(idx_elem == s.size())return;
    // Si el elemento actual entra, lo agrego y busco las soluciones que lo contengan
    if(t_candidato + dp.ws[s[idx_elem]] <= dp.W){
        b_candidato += dp.ps[s[idx_elem]];
        t_candidato += dp.ws[s[idx_elem]];
        Solve_Backtracking_Fact(s, dp, b_candidato, t_candidato,sol, idx_elem+1, nodos);
        b_candidato -= dp.ps[s[idx_elem]];
        t_candidato -= dp.ws[s[idx_elem]];
    }
    // Sin considerar el item actual, si el elemento del proximo idx_elem entra
    // Vemos las soluciones de ver ese idx_elem. Si no, al estar ordenado S
    // En orden creciente por tamaño, los demas idx_elemes tampoco entran
    // Por lo que los ignoramos
    if(t_candidato + dp.ws[s[idx_elem + 1]] <= dp.W){
        Solve_Backtracking_Fact(s, dp, b_candidato, t_candidato, sol, idx_elem+1, nodos);
    }
    return;
}

ResultadoProblema Backtracking_Fact(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    ConjLineal orig(s);
    auto start_time = std::chrono::steady_clock::now();

    unsigned int b = 0;
    std::sort(orig.begin(), orig.end(), [dp](const int& a, const int& b){
            return (dp.ws[a] < dp.ws[b]);
            });
    //for(auto& a : orig)
        //std::cout<<dp.ws[a]<<" ";
    //std::cout<<'\n';
    Solve_Backtracking_Fact(orig, dp, 0, 0, b, 0, res.nodos);

    auto end_time = std::chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    //std::cout<<"Nodos recorridos backtracking fact: "<<res.nodos<<std::endl;
    res.b = b;
    res.metodo = 3;
    res.tiempo = std::chrono::duration <double, std::milli> (diff_time);

    return res;
}
