#include "tipos_aux.h"

ResultadoProblema Fuerza_Bruta(const DatosProblema& dp, const ConjLineal& s){
    unsigned int beneficio_sol = 0;
    ResultadoProblema res;

    auto start_time = std::chrono::steady_clock::now();

    for(ID_t i = 0;i < std::pow(2, s.size());i++){
        unsigned int b = beneficio_conj_id(i, dp, s);
        unsigned int t = tamanio_conj_id(i, dp, s);
        if(b > beneficio_sol && t <= dp.W){
            beneficio_sol = b;
            res.conj_id = i;
        }
    }

    auto end_time = std::chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    res.metodo = 0;
    res.b = beneficio_sol;
    res.nodos = 0;
    res.tiempo = std::chrono::duration <double, std::milli> (diff_time);
    return res;
}
