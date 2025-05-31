#include "ColaCasillas.h"
#pragma region Int
template<>
void ColaCasillas<int>::Añadir(int elem, float w){
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

template<>
void ColaCasillas<int>::Eliminar(int elem){
    int ind = corazon.posiciones[elem];
    corazon.posiciones[elem] = -1;
    ultimo--;
    corazon.monticulo[ind] = corazon.monticulo[ultimo];
    int otrapos = corazon.monticulo[ind].first;
    corazon.monticulo[ultimo] = pair<int,float>(0,0);
    int pos = Hundir(ind);
    corazon.posiciones[otrapos] = pos;
};

template<>
void ColaCasillas<int>::Cambiar(int elem, float w){
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

template<>
int ColaCasillas<int>::Hundir(int i){
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

template<>
int ColaCasillas<int>::Flotar(int i){
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

#pragma region NodePos
template<>
void ColaCasillas<Node*>::Añadir(Node* elem, float w){
    if((int)corazon.monticulo.size() == ultimo+1)
        Alargar();
    if(corazon.posiciones[elem->index] != -1){
        corazon.monticulo[ultimo] = pair<Node*,float>(elem,w);
        corazon.posiciones[elem->index] = Flotar(ultimo);
    }
    else if(corazon.monticulo[corazon.posiciones[elem->index]].second > w){
        Cambiar(elem, w);
    };
    
    ultimo++;
};

template<>
void ColaCasillas<Node*>::Eliminar(Node* elem){
    int ind = corazon.posiciones[elem->index];
    corazon.posiciones[elem->index] = -1;
    ultimo--;
    corazon.monticulo[ind] = corazon.monticulo[ultimo];
    int otrapos = corazon.monticulo[ind].first->index;
    corazon.monticulo[ultimo] = pair<Node*,float>(0,0);
    int pos = Hundir(ind);
    corazon.posiciones[otrapos] = pos;
};

template<>
void ColaCasillas<Node*>::Cambiar(Node* elem, float w){
    int ind = corazon.posiciones[elem->index];
    float antiguo = corazon.monticulo[ind].second;
    corazon.monticulo[ind].second = w;
    if(w < antiguo){
        corazon.posiciones[elem->index] = Flotar(ind);
    }
    else{
        corazon.posiciones[elem->index] = Hundir(ind);
    }
};

template<>
int ColaCasillas<Node*>::Hundir(int i){
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
            corazon.posiciones[((Node*)corazon.monticulo[hijo].first)->index] = i;
            pair<Node*,float> aux = corazon.monticulo[hijo];
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

template<>
int ColaCasillas<Node*>::Flotar(int i){
    //¡Flota varias veces sin motivo!
    int padre = i/2;
    if(i == 1){
        return 1;
    }
    else if(corazon.monticulo[padre].second > corazon.monticulo[i].second){
        corazon.posiciones[((Node*)corazon.monticulo[padre].first)->index] = i;
        pair<Node*,float> aux = corazon.monticulo[padre];
        corazon.monticulo[padre] = corazon.monticulo[i];
        corazon.monticulo[i] = aux;
        return Flotar(padre);
    }
    else{
        return i;
    }
    
};
#pragma endregion