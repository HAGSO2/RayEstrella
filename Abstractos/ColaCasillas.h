#pragma once
#include <vector>

using namespace std;

#define salto 10


class ColaCasillas{
    //Aquí hay dos tipos de índices, el externo y el interno
    //El índice externo es el que define un elemento en el array externo
    //El índice interno es el que define en el vector de posiciones dónde está situado
    // vector<pair<pair<int,int>,float>> monticulo;
    //Donde float es el peso del elemento en el montículo
    //Donde int es la posición del array de posiciones
    vector<pair<int,float>> monticulo;
    //En cada posición descansa el índice al montículo. Cada elemento del montículo va del 1 al máximo
    //Y cada una de las posiciones de este array posiciones, representa un número de ese rango. Para
    //saber la posición de un elemento i en el montículo hay que ir a posiciones[i].
    //Cada vez que la posición cambie, hay que cambiarla de aquí
    vector<int> posiciones;
    int ultimo;
public:
    ColaCasillas(int t);
    //El w (weight) es el peso que se le da al elemento
    //El ind es el indice que ocupará en el array de posisiciones
    //El punt es el puntero al elemento
    void Añadir(int ind, float w); //log(n)
    void Eliminar(int elem);
    int Cambiar(int ind, float w);
    int MirarMínimo();
private:
    void Alargar();
    int Flotar(int i);
    int Hundir(int i);
};