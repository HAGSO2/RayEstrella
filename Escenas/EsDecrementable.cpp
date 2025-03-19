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
    // objeto->ActualizaActores();

};

EsDecrementable::EsDecrementable(): Scene(), canvasUpdate{false}, selected{false}, cola{ColaCasillas(CASILLAS)}
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
};

void EsDecrementable::DrawScreen(){
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), YELLOW);
    DrawText(fixedText[0].c_str(), 0,0,16,BLACK);
    DrawText(fixedText[1].c_str(), 0,65,16,BLACK);
    DrawText(fixedText[2].c_str(), 0,65,16,BLACK);
    canvas.Draw();
    for(int i = 0; i < CASILLAS ; i++){
        casillas[i]->DrawObject();
    }
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

void EsDecrementable::InsertaElemento(){
    InsertaElemento(alltext[0].c_str(), atoi(alltext[3].c_str()));
};

void EsDecrementable::InsertaElemento(const char* nombre, int prio){
    //No tengo claro que esto vaya a funcionar como quiero
    //Mi intención es que la letra a tenga el índice 0
    cola.Añadir( atoi(nombre) - atoi(minimoLetra), prio);
};

void EsDecrementable::CambiaElemento(){
    CambiaElemento(alltext[0].c_str(), atoi(alltext[3].c_str()));
};

void EsDecrementable::CambiaElemento(const char* nombre, int prio){
    //No tengo claro que esto vaya a funcionar como quiero
    //Mi intención es que la letra a tenga el índice 0
    cola.Cambiar( atoi(nombre) - atoi(minimoLetra), prio);
};

void EsDecrementable::EliminaElemento(){
    EliminaElemento(alltext[0].c_str());
};

void EsDecrementable::EliminaElemento(const char* nombre){
    //No tengo claro que esto vaya a funcionar como quiero
    //Mi intención es que la letra a tenga el índice 0
    cola.Eliminar( atoi(nombre) - atoi(minimoLetra));
};