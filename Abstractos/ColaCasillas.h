#pragma once
#include <vector>
#include <string>

using namespace std;

#define salto 10

template<typename t>
struct ModeloCola{
    //Donde float es el peso del elemento en el montículo
    //Donde int es la posición del array de posiciones
    vector<pair<t,float>> monticulo;
    //En cada posición descansa el índice al montículo. Cada elemento del montículo va del 1 al máximo
    //Y cada una de las posiciones de este array posiciones, representa un número de ese rango. Para
    //saber la posición de un elemento i en el montículo hay que ir a posiciones[i].
    //Cada vez que la posición cambie, hay que cambiarla de aquí
    vector<int> posiciones;
    //cuando esto esté funcionando, para mayor eficiencia esto podría ser un array
    ModeloCola(int);

    string ToString();
    vector<string> SplitString();
};

template<typename t>
class ColaCasillas{
protected:
    ModeloCola corazon;
    int ultimo;
public:
    ColaCasillas(int t);
    //El w (weight) es el peso que se le da al elemento
    //El ind es el indice que ocupará en el array de posisiciones
    //El punt es el puntero al elemento
    void Añadir(t ind, float w); //log(n)
    void Eliminar(t elem);
    void Cambiar(t ind, float w);
    t MirarMínimo();
    void EliminaMínimo();
    ModeloCola* DevuelveActual() {return &corazon;}
    string ToString();
protected:
    void Alargar();
    virtual int Flotar(int i);
    virtual int Hundir(int i);
};