#include "ColaCasillas.h"

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