#ifndef TIPOS_AUX_H
#define TIPOS_AUX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <chrono>

// Estructuras utilizadas

// En realidad es un multiconjunto, pero el nombre se hacia muy largo
typedef std::vector<unsigned int> ConjLineal;

// Lo usamos para identificar a cada conjunto del conjunto de partes Partes(S)
// Cada i-esimo bit en 1 indica que el i-esimo elemento del conjunto S esta en este subconjunto
typedef long long int ID_t;

// Matriz de enteros, utilizada en programacion dinamica
struct Matriz{
    int* datos;
    int cant_columnas;
    int cant_filas;

    Matriz(int f, int c, int v){
        assert(f > 0 && c > 0);
        cant_columnas = c;
        cant_filas = f;
        datos = new int[f*c];
        for(int i = 0; i < f*c;i++)
            datos[i] = v;
    }
    ~Matriz(){
        delete[] datos;
    }
    inline int cols() const{return cant_columnas;};
    inline int filas() const{return cant_filas;};

    int* operator[](int i){
        assert(i >= 0 && i < cant_filas);
        return (i*cant_columnas)+datos;
    };

    const int* operator[](int i) const{
        assert(i >= 0 && i < cant_filas);
        return (i*cant_columnas)+datos;
    };
};

// Estructura que contiene un conjunto entero o su identificador(ver PartesAux) y el tamaño y beneficio asociado
// Lo usamos para evitar recalcular estas cosas todo el tiempo
struct Tupla_ConjBT{
    int b_total;
    int t_total;
    ID_t conjL_id;

    Tupla_ConjBT(){
        b_total = -1;
        t_total = -1;
        conjL_id = -1;
    };

    Tupla_ConjBT(ID_t id, int b, int t){
        conjL_id = id;
        b_total = b;
        t_total = t;    
    }
};

// Estructura que devuelven los algoritmos pedidos
// Contiene beneficio de la solucion encontrada, metodo utilizado y el tiempo que tardo
struct ResultadoProblema{
    int b;
    int metodo;
    std::chrono::duration<double, std::milli> tiempo;
    int nodos;
    ID_t conj_id;
    ConjLineal conj;

    ResultadoProblema(){
        b = 0;
        metodo = 0;
        nodos = 0;
        conj_id = 0;
    };
};

// Estructura que, como dice el nombre, contiene los datos de entrada del problema

struct DatosProblema
{
    int n;
    int W;
    std::vector<int> ws;
    std::vector<int> ps;
};

// Operaciones de DatosProblema

std::istream& operator>>(std::istream& is, DatosProblema& d)
{
    is>>d.n;
    is>>d.W;

    if (d.n < 0 || d.W < 0)
    {
        std::cout<<"ERROR: Valores asignados a DatosProblema invalidos"<<std::endl;
        return is;
    }

    d.ws.resize(d.n);
    d.ps.resize(d.n);

    for(int i = 0; i < d.n;i++)
    {
        is>>d.ws[i];
        is>>d.ps[i];
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const DatosProblema& d)
{
    os<<d.n<<" "<<d.W<<std::endl;

    for(int i = 0;i < d.n;i++)
        os<<d.ws[i]<<" "<<d.ps[i]<<std::endl;

    return os;
}

DatosProblema leer_datos(std::istream& is)
{
    DatosProblema res;

    res.n = -1;
    res.W = -1;

    is>>res;

    return res;
}

// Operaciones de ConjLineal

// Calcula beneficio total de un conjunto
int beneficio_conj(const ConjLineal& c, const DatosProblema& r){
    int res = 0;
    for(int i : c)
        res += r.ps[i];
    return res;
}

int beneficio_conj_id(ID_t id, const DatosProblema& r, const ConjLineal& s){
    assert((int)sizeof(ID_t)*8 >= s.size());
    int res = 0;

    for(int i = 0;i < (int)s.size();i++){
        if (id % 2 == 1)
            res += r.ps[s[i]];
        id = id >> 1;
    }
    return res;
}

// Calcula tamaño total de un conjunto
int tamanio_conj(const ConjLineal& c, const DatosProblema& r){
    int res = 0;
    for(int i : c)
        res += r.ws[i];
    return res;
}

int tamanio_conj_id(ID_t id, const DatosProblema& r, const ConjLineal& s){
    assert((int)sizeof(ID_t)*8 >= (ID_t)s.size());
    int res = 0;

    for(int i = 0;i < (int)s.size();i++){
        if (id % 2 == 1)
            res += r.ws[s[i]];
        id = id >> 1;
    }
    return res;
}

// Genera un subconjunto de conj:total en base a los bits en 1 de size_conj
// Esto permite identificar a univocamente a cada subconjunto con un entero
ConjLineal Partes_Aux(ID_t size_conj, const ConjLineal& conj_total){
    ConjLineal res;
    for(int i = 0;i < (int)conj_total.size();i++){
        if (size_conj % 2 == 1)
            res.push_back(conj_total[i]);

        size_conj = size_conj >> 1;
    }
    return res;
}
#endif
