#include "tipos_aux.h"

using namespace std;

// Top down memoization
int Dinamica(const DatosProblema& dp, Matriz& m, int i, int t){
    if (m[i][t] == -1){
        if (i == 0)
            if (dp.ws[i] <= static_cast<unsigned int>(t))
                m[i][t] = static_cast<int>(dp.ps[i]);
            else
                m[i][t] = 0;
        else if(dp.ws[i] > static_cast<unsigned int>(t))
            m[i][t] = Dinamica(dp, m, i-1, t);
        else
            m[i][t] = max(Dinamica(dp, m, i-1, t), Dinamica(dp, m, i-1, t - dp.ws[i]) + static_cast<int>(dp.ps[i]));
    }
    return m[i][t];
}

ResultadoProblema Dinamica(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    auto start_time = chrono::steady_clock::now();

    assert((s.size()+1)*(dp.W+1) * sizeof(int) < 4294967292);//4gb
    // Si la matriz usa alrededor de 4GB abortamos

    Matriz m(static_cast<int>(s.size() + 1), dp.W + 1, -1);
    res.b = static_cast<unsigned int>(Dinamica(dp, m, s.size()-1, dp.W));

    auto end_time = chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    res.metodo = 3;
    res.tiempo = chrono::duration <double, std::milli> (diff_time);

    return res;
}
