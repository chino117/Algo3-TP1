#include "tipos_aux.h"

// Top down memoization
int Dinamica_Top_Down(const DatosProblema& dp, Matriz& m, int i, int t){
    if (m[i][t] == -1){
        if (i == 0)
            if (dp.ws[i] <= t)
                m[i][t] = dp.ps[i];
            else
                m[i][t] = 0;
        else if(dp.ws[i] > t)
            m[i][t] = Dinamica_Top_Down(dp, m, i-1, t);
        else
            m[i][t] = std::max(Dinamica_Top_Down(dp, m, i-1, t), Dinamica_Top_Down(dp, m, i-1, t - dp.ws[i]) + dp.ps[i]);
    }
    return m[i][t];
}

ResultadoProblema Dinamica_TD(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    auto start_time = std::chrono::steady_clock::now();

    assert((s.size()+1)*(dp.W+1) * sizeof(int) < 4294967292);//4gb
    // Si la matriz usa alrededor de 4GB abortamos

    Matriz m((int)s.size() + 1, dp.W + 1, -1);
    int b = Dinamica_Top_Down(dp, m, (int)s.size()-1, dp.W);

    auto end_time = std::chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    res.b = b;
    res.metodo = 7;
    res.tiempo = std::chrono::duration <double, std::milli> (diff_time);

    return res;
}
