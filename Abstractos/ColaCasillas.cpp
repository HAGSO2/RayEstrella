#include "ColaCasillas.h"
#include <raylib.h>
using namespace std;

#pragma region Modelo
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
#pragma endregion


#pragma region Cola Casillas
ColaCasillas::ColaCasillas(int max):ultimo{1}, 
corazon{ModeloCola(max)}
//monticulo{vector<pair<int,float>>(salto)}, posiciones{vector<int>(max+1,-1)}
{};

void ColaCasillas::Añadir(int elem, float w){
    if((int)corazon.monticulo.size() == ultimo+1)
        Alargar();
    if(corazon.posiciones[elem] != -1){
        corazon.monticulo[ultimo] = pair<int,float>(elem,w);
        corazon.posiciones[elem] = Flotar(ultimo);
    }
    else if(corazon.monticulo[corazon.posiciones[elem]].second > w){
        Cambiar(elem, w);
    };
    
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
    int otrapos = corazon.monticulo[ind].first;
    corazon.monticulo[ultimo] = pair<int,float>(0,0);
    int pos = Hundir(ind);
    corazon.posiciones[otrapos] = pos;
};

void ColaCasillas::Cambiar(int elem, float w){
    int ind = corazon.posiciones[elem];
    float antiguo = corazon.monticulo[ind].second;
    corazon.monticulo[ind].second = w;
    if(w < antiguo){
        corazon.posiciones[elem] = Flotar(ind);
    }
    else{
        corazon.posiciones[elem] = Hundir(ind);
    }
};

int ColaCasillas::MirarMínimo(){return corazon.monticulo[1].first;};
void ColaCasillas::EliminaMínimo(){Eliminar(1);};

string ColaCasillas::ToString(){
    string queue = "Montículo: \n";
    for(int i = 1; i < corazon.monticulo.size(); i++){
        queue.append( to_string(corazon.monticulo[i].first) + "|" + to_string(corazon.monticulo[i].second) + "\n");
    }
    queue.append("\nPosiciones: \n");
    for(int i = 0; i < corazon.posiciones.size(); i++){
        queue.append( to_string(i) + "|" + to_string(corazon.posiciones[i]) + "\n");
    }
    return queue;
}

#pragma region Cola interno
int ColaCasillas::Hundir(int i){
    if(i == ultimo){
        return i;
    }
    else if ((i*2) < ultimo){
        int hijo = i*2;
        if(hijo+1 < ultimo && corazon.monticulo[hijo].second > corazon.monticulo[hijo+1].second)
            hijo++;
        if(corazon.monticulo[hijo].second < corazon.monticulo[i].second){
            /*
            * <A,32> -> (<C,2>|<V,4>) ==> 
            *   <C,2> -> (<A,32|<V,4>)
            */
            corazon.posiciones[corazon.monticulo[hijo].first] = i;
            pair<int,float> aux = corazon.monticulo[hijo];
            corazon.monticulo[hijo] = corazon.monticulo[i];
            corazon.monticulo[i] = aux;
            return Hundir(hijo);
        }
        
    }     //Si es mayor que último tengo que ver
    else if(i > ultimo){
        return i/2;
    }   
    
    return i;
    
};

int ColaCasillas::Flotar(int i){
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
#pragma endregion
#pragma endregion