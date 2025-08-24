#pragma once
#include <vector>
#include <string>
#include "../Escenas/Adicional.h"

using namespace std;

#define salto 10

class ColaNodes{
    vector<pair<Node*,float>> monticulo;
    vector<int> posiciones;
    int ultimo;
    public:
    
    ColaNodes(int max);
    //El w (weight) es el peso que se le da al elemento
    //El ind es el indice que ocupará en el array de posisiciones
    //El punt es el puntero al elemento
    void Añadir(Node* ind, float w, int& cambio); //log(n)
    void Eliminar(Node* elem);
    void Cambiar(Node* ind, float w);
    Node* MirarMínimo();
    void EliminaMínimo();
    string ToString();
    int Ultimo(){return ultimo;}
private:
    void Alargar();
    int Flotar(int i);
    int Hundir(int i);
};