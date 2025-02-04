#include "EsDecrementable.h"

EsDecrementable::EsDecrementable(string& ref): lenth{ref}, Scene(), canvasUpdate{false}, selected{false}
{
    canvas.AddTextBox(0,0,80,60,lenth,canvasUpdate,selected);
};

void EsDecrementable::DrawScreen(){
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), YELLOW);
    canvas.Draw();
};

void EsDecrementable::UpdateScreen(){
    Scene::UpdateScreen();
    // if(canvasUpdate) // Le he dado a enter en la textbox
    //     TraceLog(LOG_DEBUG, lenth);
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