#include "EsDecrementable.h"

void ActualizaEscena(void* ptr){
    TraceLog(LOG_ALL,"Actualizando...");
    EsDecrementable* objeto = (EsDecrementable*)ptr;
    //Insertar
    //Se inserta un elemento con un nombre alltext[0], y una prioridad alltext[3]
    objeto->InsertaElemento();

    //Cambiar
    objeto->CambiaElemento();

    //Eliminar
    objeto->EliminaElemento();

    //Finalmente actualizar
    //objeto->ActualizaActores();

    objeto->RessetText();

    string cola = objeto->DevuelveCola();
    //TraceLog(LOG_DEBUG, cola.c_str());

};

void EsDecrementable::InsertaElemento(){
    InsertaElemento(alltext[0].c_str(), atoi(alltext[3].c_str()));
};

void EsDecrementable::InsertaElemento(const char* nombre, int prio){
    int resta = (int)*nombre - (int)minimoLetra;
    if(nombre != "" && resta > -1 ){
        cola.Añadir( resta, prio);
    }
    RessetText();
};

void EsDecrementable::CambiaElemento(){
    CambiaElemento(alltext[1].c_str(), atoi(alltext[4].c_str()));
};

void EsDecrementable::CambiaElemento(const char* nombre, int prio){
    TraceLog(LOG_DEBUG,"Desde aquí");
    //No tengo claro que esto vaya a funcionar como quiero
    //Mi intención es que la letra a tenga el índice 0
    int resta = (int)*nombre - (int)minimoLetra;
    if(nombre != "" && resta > -1){
        char charternombre = *nombre;
        cola.Cambiar( resta, prio);
    }
        
};

void EsDecrementable::EliminaElemento(){
    EliminaElemento(alltext[2].c_str());
};

void EsDecrementable::EliminaElemento(const char* nombre){
    //No tengo claro que esto vaya a funcionar como quiero
    //Mi intención es que la letra a tenga el índice 0
    int resta = (int)*nombre - (int)minimoLetra;
    if(nombre != "" && resta > -1){
        char charternombre = *nombre;
        cola.Eliminar( resta);
    }
};

void EsDecrementable::RessetText(){
    for(int i = 0; i < 5; i++){
        alltext[i] = "";
    }
    
};
//Si el compilador falla, quitar el const de aquí
void EsDecrementable::ActualizaActores(const vector<ModeloCola*>& vect){
    for(int i = 0; i < size(vect); i++){
        FijaNumeroActores(size(vect[i]->monticulo));
        FijaTextoActores(vect[i]->SplitString());
        WaitTime(velocidad);
    } 
    
};

void EsDecrementable::FijaNumeroActores(int num){
    if(num > active){//Si hay que activar más:
        while (num > active)
        {
            casillas[active]->ChangeColor(RED);
            casillas[active]->ChangeText("");
            active++;
        }
    }
    else{
        while (num > active)
        {
            casillas[active]->ChangeColor(BLACK);
            casillas[active]->ChangeText("");
            active--;
        }
        
    }
};

//Tengo que hacer esto desde el principio para no tener
// que mover los actores, cambio el texto y cambia el actor
void EsDecrementable::FijaTextoActores(vector<string> nombr)
{
    for(int i = 0; i < active; i++){
        casillas[i]->ChangeText(nombr[i]);
    }
};

EsDecrementable::EsDecrementable(): Scene(), active{0}, selected{false}, cola{ColaCasillas(CASILLAS)}
//,casillas{nullptr}
{
    canvas.AddTextBox(90,0,80,60,alltext[0]);
    canvas.AddTextBox(90,65,80,60,alltext[1]);
    canvas.AddTextBox(90,130,80,60,alltext[2]);

    canvas.AddTextBox(180,0,80,60,alltext[3]);
    canvas.AddTextBox(180,65,80,60,alltext[4]);
    
    canvas.AddButton(360,0,80,60,"Actualizar",RED,ActualizaEscena,this);
    
    for(int i = 0; i < CASILLAS; i++){
        casillas[i] = new TextShape{75*i+75,275,50,50,"",BLACK};
    };
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
    
}