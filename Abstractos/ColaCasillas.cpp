#include "ColaCasillas.h"
#include <raylib.h>
using namespace std;

ModeloCola::ModeloCola(int max): monticulo{vector<pair<int,float>>(salto)}, posiciones{vector<int>(max+1,-1)}{};

string ModeloCola::ToString(){
    string mensaje;
    for(int i = 0; i < monticulo.size(); i++){
        pair<int,float> elem = monticulo[i];
        mensaje.push_back('[');
        mensaje.append(to_string(elem.first));
        mensaje.push_back('|');
        mensaje.append(to_string(elem.second));
        mensaje.push_back(']');
    }
}

vector<string> ModeloCola::SplitString(){
    vector<string> mensaje;
    for(int i = 1; i < monticulo.size(); i++){
        char c = (char)(monticulo[i].first+65);
        string aux = "[";
        aux.push_back(c);
        mensaje.push_back(aux + "|" + to_string(monticulo[i].second) + "]");
    }
    return mensaje;
}

ColaCasillas::ColaCasillas(int max):ultimo{1}, 
corazon{ModeloCola(max)}
//monticulo{vector<pair<int,float>>(salto)}, posiciones{vector<int>(max+1,-1)}
{};

void ColaCasillas::Añadir(int elem, float w){
    if((int)corazon.monticulo.size() == ultimo+1)
        Alargar();
    corazon.monticulo[ultimo] = pair<int,float>(elem,w);
    corazon.posiciones[elem] = Flotar(ultimo);
    ultimo++;
};

void ColaCasillas::Alargar(){
    vector<pair<int,float>> aux = vector<pair<int,float>>(corazon.monticulo.size()+salto);
    for(int i = 0; i < (int)corazon.monticulo.size(); i++){
        aux[i] = corazon.monticulo[i];
    }
    corazon.monticulo = aux;
};

void ColaCasillas::Eliminar(int elem){
    int ind = corazon.posiciones[elem];
    corazon.posiciones[elem] = -1;
    ultimo--;
    corazon.monticulo[ind] = corazon.monticulo[ultimo];
    int otrapos = corazon.monticulo[ultimo].first;
    corazon.posiciones[otrapos] = Hundir(ind);

};

void ColaCasillas::Cambiar(int elem, float w){
    int ind = corazon.posiciones[elem];
    float antiguo = corazon.monticulo[ind].second;
    corazon.monticulo[ind].second = w;
    if(antiguo > w){
        corazon.posiciones[elem] = Flotar(ind);
    }
    else{
        corazon.posiciones[elem] = Hundir(ind);
    }
};

int ColaCasillas::Hundir(int i){
    TraceLog(LOG_DEBUG,"Posición: %d, Cuál: %d",i,corazon.monticulo[i].first);
    if(i == ultimo || i*2 >= ultimo)
        return i;
    else{
        int hijo = i*2;
        if(hijo+1 < ultimo && corazon.monticulo[hijo].second > corazon.monticulo[hijo+1].second)
            hijo++;
        if(corazon.monticulo[hijo].second > corazon.monticulo[i].second){
            /*
            * <A,32> -> (<C,2>|<V,4>) ==> 
            *   <C,2> -> (<A,32|<V,4>)
            */
            pair<int,float> aux = corazon.monticulo[hijo];
            corazon.monticulo[hijo] = corazon.monticulo[i];
            corazon.monticulo[i] = aux;
            corazon.posiciones[aux.first] = i;
            return Hundir(hijo);
        }
        
    }
    return i;
    
};

int ColaCasillas::Flotar(int i){
    //TraceLog(LOG_DEBUG, "Flotando desde %d",i);
    //¡Flota varias veces sin motivo!
    int padre = i/2;
    if(i == 1){
        return 1;
    }
    else if(corazon.monticulo[padre].second > corazon.monticulo[i].second){
        corazon.posiciones[corazon.monticulo[padre].first] = i;
        pair<int,float> aux = corazon.monticulo[padre];
        corazon.monticulo[padre] = corazon.monticulo[i];
        corazon.monticulo[i] = aux;
        return Flotar(padre);
    }
    else{
        return i;
    }
    
};

string ColaCasillas::ToString(){
    string queue = "Montículo: \n";
    for(int i = 0; i < corazon.monticulo.size(); i++){
        queue.append( to_string(corazon.monticulo[i].first) + "|" + to_string(corazon.monticulo[i].second) + "\n");
    }
    queue.append("Posiciones: \n");
    for(int i = 0; i < corazon.posiciones.size(); i++){
        queue.append( to_string(i) + "|" + to_string(corazon.posiciones[i]) + "\n");
    }
    return queue;
}