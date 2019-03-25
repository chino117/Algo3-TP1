#include "tipos_aux.h"

// Bottom-up
int Dinamica_Bottom_Up(const DatosProblema& dp, Matriz& m, int n, int t){
    int t_0 = dp.ws[0];
    for(int j = 0;j <= t;j++)
        if(t_0 <= j)
            m[0][j] = dp.ps[0];
        else
            m[0][j] = 0;

    for(int i = 1;i <= n;i++){
        for(int j = 0;j <= t;j++){
            if(dp.ws[i] > j)
                m[i][j] = m[i-1][j];
            else
                m[i][j] = std::max(m[i-1][j], m[i-1][j - dp.ws[i]] + dp.ps[i]);
        }
    }
    return m[n][t];
}

ResultadoProblema Dinamica_BU(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    auto start_time = std::chrono::steady_clock::now();

    assert((s.size()+1)*(dp.W+1) * sizeof(int) < 4294967292);//4gb
    // Si la matriz usa alrededor de 4GB abortamos

    Matriz m((int)s.size() + 1, dp.W + 1, -1);
    int b = Dinamica_Bottom_Up(dp, m, (int)s.size()-1, dp.W);

    auto end_time = std::chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    res.b = b;
    res.metodo = 6;
    res.tiempo = std::chrono::duration <double, std::milli> (diff_time);

    return res;
}


