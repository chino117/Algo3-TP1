#include "tipos_aux.h"
#include <algorithm>

ResultadoProblema MITM(const ConjLineal& s, const DatosProblema& dp){
    ResultadoProblema res;
    auto mitad = s.size()/2;

    std::vector<Tupla_ConjBT> A;
    std::vector<Tupla_ConjBT> B;

    auto start_time = std::chrono::steady_clock::now();

    ConjLineal div1(s.cbegin(), s.cbegin() + mitad);
    ConjLineal div2(s.cbegin() + mitad, s.cend());

    // Genero subconjuntos de la primer mitad, me guardo el numero con el que los cree(i) y su beneficio y tamanio totales
    for(ID_t i = 0;i < std::pow(2, div1.size());i++){
        unsigned int t = tamanio_conj_id(i, dp, div1);
        if (t <= dp.W){
            unsigned int b = beneficio_conj_id(i, dp, div1);
            A.emplace_back(i, b, t);
        }
    }

    // Genero subconjuntos de la segunda mitad, me guardo el numero con el que los cree(i) y su beneficio y tamanio totales
    for(ID_t i = 0;i < std::pow(2, div2.size());i++){
        unsigned int t = tamanio_conj_id(i, dp, div2);
        if (t <= dp.W){
            unsigned int b = beneficio_conj_id(i, dp, div2);
            B.emplace_back(i, b, t);
        }
    }

    // Ordeno elementos de la segunda mitad por tamaño
    std::sort(B.begin(), B.end(), [](const Tupla_ConjBT& a, const Tupla_ConjBT& b){
        return a.t_total < b.t_total;
    });

    // Armo una lista que contenga en cada indice i, el indice j al elemento de mayor beneficio en el rango (0, i) de la segunda mitad
    std::vector<ConjLineal::size_type> maximos_div2(B.size(), -1);
    maximos_div2[0] = 0;

    for(ConjLineal::size_type idx = 1; idx < B.size();idx++){
        if (B[idx].b_total > B[maximos_div2[idx-1]].b_total)
            maximos_div2[idx] = idx;
        else
            maximos_div2[idx] = maximos_div2[idx - 1];
    }

    unsigned int beneficio_sol = 0; 

    for(auto j = A.begin(); j != A.end(); j++){

        // Buscamos de forma binaria el primero elemento de la division 2 que no cumple la restriccion para el j actual
        auto techo_restriccion = std::upper_bound(B.cbegin(),B.cend(), (*j), [dp](const Tupla_ConjBT& a, const Tupla_ConjBT& b){
            return b.t_total + a.t_total > dp.W;
        });

        // Buscamos el maximo beneficio en el rango (0, techo-1)
        int candidato = maximos_div2[std::distance(B.cbegin(), techo_restriccion-1)];

        // Si es mejor que el actual, lo guardamos
        if (B[candidato].b_total + j->b_total > beneficio_sol)
            beneficio_sol = j->b_total + B[candidato].b_total;
    }

    auto end_time = std::chrono::steady_clock::now();
    auto diff_time = end_time - start_time;

    res.b = beneficio_sol;
    res.metodo = 1;
    res.nodos = 0;
    res.tiempo = std::chrono::duration <double, std::milli> (diff_time);

    return res;
}

