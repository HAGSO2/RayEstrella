#include "ColaCasillas.h"
#include <raylib.h>
using namespace std;

ColaCasillas::ColaCasillas(int max):ultimo{1}, monticulo{vector<pair<int,float>>(salto)}, posiciones{vector<int>(max+1,-1)}{}

void ColaCasillas::Añadir(int elem, float w){
    if((int)monticulo.size() == ultimo+1)
        Alargar();
    monticulo[ultimo] = pair<int,float>(elem,w);
    posiciones[elem] = Flotar(ultimo);
    TraceLog(LOG_DEBUG, "BUM!");
    ultimo++;
};

void ColaCasillas::Alargar(){
    vector<pair<int,float>> aux = vector<pair<int,float>>(monticulo.size()+salto);
    for(int i = 0; i < (int)monticulo.size(); i++){
        aux[i] = monticulo[i];
    }
    monticulo = aux;
};

void ColaCasillas::Eliminar(int elem){
    monticulo[elem] = monticulo[ultimo];
    ultimo--;
    Hundir(1);

};

int ColaCasillas::Cambiar(int ind, float w){
    float antiguo = monticulo[ind].second;
    monticulo[ind].second = w;
    if(antiguo > w){
        return Flotar(ind);
    }
    else{
        return Hundir(ind);
    }
    return ind;
};

int ColaCasillas::Hundir(int i){
    if(i == ultimo || i*2 >= ultimo)
        return i;
    else{
        int hijo = i*2;
        if(hijo+1 < ultimo && monticulo[hijo].second > monticulo[hijo+1].second)
            hijo++;
        if(monticulo[hijo].second > monticulo[i].second){
            posiciones[monticulo[hijo].second] = i;
            pair<int,float> aux = monticulo[hijo];
            monticulo[hijo] = monticulo[i];
            monticulo[i] = aux;
            return Hundir(hijo);
        }
        
    }
    return i;
    
};

int ColaCasillas::Flotar(int i){
    TraceLog(LOG_DEBUG, "Flotando desde %d",i);
    //¡Flota varias veces sin motivo!
    int padre = i/2;
    if(i == 1){
        return 1;
    }
    else if(monticulo[padre].second > monticulo[i].second){
        posiciones[monticulo[padre].second] = i;
        pair<int,float> aux = monticulo[padre];
        monticulo[padre] = monticulo[i];
        monticulo[i] = aux;
        return Flotar(padre);
    }
    else{
        return i;
    }
    
};

string ColaCasillas::ToString(){
    string queue = "Montículo: \n";
    for(int i = 0; i < monticulo.size(); i++){
        queue.append( to_string(monticulo[i].first) + "|" + to_string(monticulo[i].second) + "\n");
    }
    queue.append("Posiciones: \n");
    for(int i = 0; i < posiciones.size(); i++){
        queue.append( to_string(i) + "|" + to_string(posiciones[i]) + "\n");
    }
    return queue;
}