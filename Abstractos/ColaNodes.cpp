#include "ColaNodes.h"
#include <raylib.h>
#include "iostream"

#pragma region Cola Casillas
ColaNodes::ColaNodes(int m):ultimo{1}, 
monticulo{vector<pair<Node*,float>>(salto)}, 
posiciones{vector<int>(m,-1)}, max{m}
{};

void ColaNodes::Resset(){
    ultimo = 1;
    monticulo.clear();
    posiciones.clear();
    monticulo = vector<pair<Node*,float>>(salto);
    posiciones = vector<int>(max,-1);
};

void ColaNodes::Añadir(Node* elem, float w, int & cambio){
    //TraceLog(LOG_DEBUG,"Añadiendo...");
    if((int)monticulo.size() == ultimo+1)
        Alargar();
    if(posiciones[elem->index] == -1){// Si no se encuentra en las posicioines:
        monticulo[ultimo] = pair<Node*,float>(elem,w); //Se añade el último y
        posiciones[elem->index] = Flotar(ultimo); //Flota desde allí y guarda posicións
        cambio = 1;
        ultimo++;
    }
    else if(monticulo[posiciones[elem->index]].second > w){//Si está actualmente dentro de la cola:
        Cambiar(elem, w);
        cambio = 1;
    };
    //TraceLog(LOG_DEBUG,"Añadido en: %d",posiciones[elem->index]);
    //TraceLog(LOG_DEBUG, "Último: %d",ultimo);
    //std::cout << ToString();
};

void ColaNodes::Alargar(){
    vector<pair<Node*,float>> aux = vector<pair<Node*,float>>(monticulo.size()+salto);
    for(int i = 0; i < (int)monticulo.size(); i++){
        aux[i] = monticulo[i];
    }
    monticulo = aux;
};

void ColaNodes::Eliminar(Node* elem){
    int ind = posiciones[elem->index];
    posiciones[elem->index] = -2;
    ultimo--;
    monticulo[ind] = monticulo[ultimo];
    int otrapos = monticulo[ind].first->index;
    //monticulo[ultimo] = pair<Node*,float>(nullptr,0);
    int pos = Hundir(ind);
    posiciones[otrapos] = pos;
};

void ColaNodes::Cambiar(Node* elem, float w){
    int ind = posiciones[elem->index];
    float antiguo = monticulo[ind].second;
    monticulo[ind].second = w;
    if(w < antiguo){
        posiciones[elem->index] = Flotar(ind);
    }
    else{
        posiciones[elem->index] = Hundir(ind);
    }
};
Node* ColaNodes::MirarMínimo(){return monticulo[1].first;};
void ColaNodes::EliminaMínimo(){Eliminar(monticulo[1].first);};

string ColaNodes::ToString(){
    string queue = "\nMontículo: \n";
    for(int i = 1; i < monticulo.size() ;i++){
        if(monticulo[i].first != nullptr)
            queue.append( "["+to_string(monticulo[i].first->index) + "|" + to_string(monticulo[i].second) + "]\n");
        else
            queue.append("[|]\n");
    }
    queue.append("Posiciones: \n");
    for(int i = 1,j = 0; i < posiciones.size(); i++){
        queue.append( to_string(i) + "|" + to_string(posiciones[i]) + "\t");
        j++;
        if(j == 10){
            queue.append("\n");
            j = 0;
        }
    }
    queue.append("\n");
    return queue;
}

#pragma region Cola interno
int ColaNodes::Hundir(int i){
    if(i == ultimo){
        return i;
    }
    else if ((i*2) < ultimo){
        int hijo = i*2;
        if(hijo+1 < ultimo && monticulo[hijo].second > monticulo[hijo+1].second)
            hijo++;
        if(monticulo[hijo].second < monticulo[i].second){
            /*
            * <A,32> -> (<C,2>|<V,4>) ==> 
            *   <C,2> -> (<A,32|<V,4>)
            */
            posiciones[monticulo[hijo].first->index] = i;
            pair<Node*,float> aux = monticulo[hijo];
            monticulo[hijo] = monticulo[i];
            monticulo[i] = aux;
            return Hundir(hijo);
        }
        
    }     //Si es mayor que último tengo que ver
    else if(i > ultimo){
        return i/2;
    }   
    
    return i;
    
};

int ColaNodes::Flotar(int i){
    int padre = i/2;
    if(i == 1){
        return 1;
    }
    else if(monticulo[padre].second > monticulo[i].second){
        posiciones[monticulo[padre].first->index] = i;
        pair<Node*,float> aux = monticulo[padre];
        monticulo[padre] = monticulo[i];
        monticulo[i] = aux;
        return Flotar(padre);
    }
    else{
        return i;
    }
    
};
#pragma endregion
#pragma endregion