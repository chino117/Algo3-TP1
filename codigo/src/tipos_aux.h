#ifndef TIPOS_AUX_H
#define TIPOS_AUX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cassert>
#include <chrono>

using namespace std;

// Estructuras utilizadas

// En realidad es un multiconjunto, pero el nombre se hacia muy largo
typedef vector<unsigned int> ConjLineal;

// Lo usamos para identificar a cada conjunto del conjunto de partes Partes(S)
// Cada i-esimo bit en 1 indica que el i-esimo elemento del conjunto S esta en este subconjunto
typedef long long unsigned int ID_t;

// Matriz de enteros, utilizada en programacion dinamica
struct Matriz{
    int* datos;
    int cant_columnas;
    int cant_filas;

    Matriz(int f, int c, int v){
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
    unsigned int b_total;
    unsigned int t_total;
    ID_t conjL_id;

    Tupla_ConjBT(){
        b_total = 0;
        t_total = 0;
        conjL_id = 0;
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
    unsigned int b;
    unsigned int metodo;
    chrono::duration<double, milli> tiempo;
    unsigned int nodos;
    ID_t conj_id;
    ConjLineal conj;

    ResultadoProblema(){
        b = 0;
        metodo = 0;
        nodos = 0;
        conj_id = 0;
    };
};

// Estructura que contiene los datos de entrada del problema

struct DatosProblema
{
    unsigned int n;
    unsigned int W;
    vector<unsigned int> ws;
    vector<unsigned int> ps;
};

// Operaciones de DatosProblema

istream& operator>>(istream& is, DatosProblema& d)
{
    is>>d.n;
    is>>d.W;

    if (d.n < 0 || d.W < 0)
    {
        cout<<"ERROR: Valores asignados a DatosProblema invalidos"<<endl;
        return is;
    }

    d.ws.resize(d.n);
    d.ps.resize(d.n);

    for(unsigned int i = 0; i < d.n;i++)
    {
        is>>d.ws[i];
        is>>d.ps[i];
    }

    return is;
}

ostream& operator<<(ostream& os, const DatosProblema& d)
{
    os<<d.n<<" "<<d.W<<endl;

    for(unsigned int i = 0;i < d.n;i++)
        os<<d.ws[i]<<" "<<d.ps[i]<<endl;

    return os;
}

DatosProblema leer_datos(istream& is)
{
    DatosProblema res;
    is>>res;
    return res;
}

// Operaciones de ConjLineal

// Calcula beneficio total de un conjunto
unsigned int beneficio_conj(const ConjLineal& c, const DatosProblema& r){
    unsigned int res = 0;
    for(unsigned int i : c)
        res += r.ps[i];
    return res;
}

unsigned int beneficio_conj_id(ID_t id, const DatosProblema& r, const ConjLineal& s){
    unsigned int res = 0;

    for(ConjLineal::size_type i = 0;i < s.size();i++){
        if (id % 2 == 1)
            res += r.ps[s[i]];
        id = id >> 1;
    }
    return res;
}

// Calcula tamaño total de un conjunto
unsigned int tamanio_conj(const ConjLineal& c, const DatosProblema& r){
    unsigned int res = 0;
    for(unsigned int i : c)
        res += r.ws[i];
    return res;
}

unsigned int tamanio_conj_id(ID_t id, const DatosProblema& r, const ConjLineal& s){
    unsigned int res = 0;

    for(ConjLineal::size_type i = 0;i < s.size();i++){
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
    for(ConjLineal::size_type i = 0;i < conj_total.size();i++){
        if (size_conj % 2 == 1)
            res.push_back(conj_total[i]);

        size_conj = size_conj >> 1;
    }
    return res;
}
#endif
