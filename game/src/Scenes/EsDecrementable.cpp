#include "Scenes/EsDecrementable.h"

void ActualizaEscena(void* ptr){
    EsDecrementable* objeto = (EsDecrementable*)ptr;
    //Insertar
    //Se inserta un elemento con un nombre alltext[0], y una prioridad alltext[3]
    objeto->InsertaElemento();

    //Cambiar
    objeto->CambiaElemento();

    //Eliminar
    objeto->EliminaElemento();

    //Finalmente actualizar
    objeto->ActualizaActores();

    //Pone los textbox vacíos
    objeto->RessetText();

    //string cola = objeto->DevuelveCola();
    //TraceLog(LOG_DEBUG, cola.c_str());

};

#pragma region Elemet managment

void EsDecrementable::InsertaElemento(){
    InsertaElemento(alltext[0].c_str(), atoi(alltext[3].c_str()));
};

void EsDecrementable::InsertaElemento(const char* nombre, int prio){
    int resta = (int)*nombre - (int)minimoLetra;
    if(nombre != "" && resta > -1 ){
        cola.Añadir( resta, prio);
        active++;
    };
};

void EsDecrementable::CambiaElemento(){
    CambiaElemento(alltext[1].c_str(), atoi(alltext[4].c_str()));
};

void EsDecrementable::CambiaElemento(const char* nombre, int prio){
    int resta = (int)*nombre - (int)minimoLetra;
    if(nombre != "" && resta > -1){
        //TraceLog(LOG_DEBUG,"Cambiando: %d a %d",resta, prio);
        cola.Cambiar( resta, prio);
    }
        
};

void EsDecrementable::EliminaElemento(){
    EliminaElemento(alltext[2].c_str());
};

void EsDecrementable::EliminaElemento(const char* nombre){
    int resta = (int)*nombre - (int)minimoLetra;
    if(nombre != "" && resta > -1){
        //TraceLog(LOG_DEBUG,"Eliminando: %d",resta);
        cola.Eliminar( resta);
        active--;
    }
};

void EsDecrementable::RessetText(){
    for(int i = 0; i < 5; i++){
        alltext[i] = "";
    }
    
};

#pragma endregion

#pragma region Actor managment
void EsDecrementable::ActualizaActores(){
    //Cuando quiera que se haga en diferentes pasos, hay que revisar esta línea
    vector<ModeloCola*> vect = {cola.DevuelveActual()};
    //->
    for(int i = 0; i < vect.size(); i++){
        FijaNumeroActores();
        FijaTextoActores(vect[i]->SplitString());
        //WaitTime(velocidad);
    } 
    
};

void EsDecrementable::FijaNumeroActores(){
    for(int i = 0; i < CASILLAS; i++){
        if(i < active){
            casillas[i]->ChangeColor(RED);
            casillas[i]->ChangeText("");
        }
        else{
            casillas[i]->ChangeColor(GRAY);
            casillas[i]->ChangeText("");
        }
    };
};

//Tengo que hacer esto desde el principio para no tener
// que mover los actores, cambio el texto y cambia el actor
void EsDecrementable::FijaTextoActores(vector<string> nombr)
{
    for(int i = 0; i < nombr.size(); i++){
        //TraceLog(LOG_DEBUG,nombr[i].c_str());
        casillas[i]->ChangeText(nombr[i]);
    }
};

#pragma region Scene managment

EsDecrementable::EsDecrementable(): Scene(), active{0}, selected{false}, cola{ColaCasillas(CASILLAS)}
{
    canvas.AddTextBox(90,0,80,60,alltext[0]);
    canvas.AddTextBox(90,65,80,60,alltext[1]);
    canvas.AddTextBox(90,130,80,60,alltext[2]);

    canvas.AddTextBox(180,0,80,60,alltext[3]);
    canvas.AddTextBox(180,65,80,60,alltext[4]);
    
    canvas.AddButton(360,0,80,60,"Actualizar",RED,ActualizaEscena,this);
    for(int i = 0; i < 3; i++){//3x8 = 24
        for(int j = 0; j < 8; j++){
            casillas[j+i*8] = new TextShape{(float)75*j+75,(float)220 + i*75,50,50,"",GRAY};
        }
    }
    casillas[24] = new TextShape{75,220+3*75,50,50,"",BLACK};
    casillas[25] = new TextShape{75+75,220+3*75,50,50,"",BLACK};
    casillas[26] = new TextShape{75+75*2,220 + 3*75,50,50,"",BLACK};
    // for(int i = 0; i < CASILLAS; i++){
    //     casillas[i] = new TextShape{75*i+75,275,50,50,"",BLACK};
    // };
    //TraceLog(LOG_DEBUG, DevuelveCola().c_str());
};

void EsDecrementable::DrawScreen(){
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), YELLOW);
    DrawText(fixedText[0].c_str(), 0,0,16,BLACK);
    DrawText(fixedText[1].c_str(), 0,65,16,BLACK);
    DrawText(fixedText[2].c_str(), 0,135,16,BLACK);
    canvas.Draw();
    for(int i = 0; i < active ; i++){
        casillas[i]->DrawObject();
    }
};

void EsDecrementable::UpdateScreen(){
    Scene::UpdateScreen();
};

void EsDecrementable::OnMouseDown(){
    canvas.UpdateScreen(mousePosition);
}

void EsDecrementable::OnKeyPressed(KeyboardKey k){

    
    if(k != KEY_NULL){
        // TraceLog(LOG_DEBUG, "Decrementable: %c, %d",(char)k,k);
        if(!selected && k == KEY_BACKSPACE)
            finishScreen = TITTLE;
        else
            canvas.UpdateKeyboard(k);
    }
    
};

#pragma endregion