#include "EngineObjects/UI.h"

#pragma region  Comun
UI::UI(){};

UIElement::UIElement(float x, float y, float width, float height) : area(Rectangle{x,y,width,height}){};

void UI::AddButton(float x, float y, float width, float height,const char* s, Color c, void (*Func)(void*), void* ptr){
    elements.push_back(new Button(x,y,width,height,s,c,Func,ptr));
}

void UI::AddTextBox(float x, float y, float width, float height, string& reftxt)
 {
    elements.push_back(new TextBox(x,y,width,height, reftxt));
 };


bool UIElement::IsInside(Vector2 mouseButton){ return CheckCollisionPointRec(mouseButton,area);}

void UI::Draw(){
    for(int i = 0; i < elements.size(); i++){
        elements[i]->Draw();
    }
};

void UI::UpdateScreen(Vector2 mouseposition){
    int i = 0;
    // TraceLog(LOG_ALL,"Comprobando...");
    while (i < elements.size() && !elements[i]->IsInside(mouseposition))
    {
        elements[i]->SetOut();
        i++;
    }
    if(i < elements.size()){
        elements[i]->UpdateScreen(mouseposition);
        i++;
    }
    while (i < elements.size())
    {
        elements[i]->SetOut();
        i++;
    }
    
    
};

void UI::UpdateKeyboard(KeyboardKey k){
    for(int i = 0; i< elements.size(); i++){elements[i]->UpdateKeyboard(k);};
};

#pragma endregion

CallBack::CallBack(void (*Func)(void*), void* miptrs): ClickFunk{Func}, ptr{miptrs}{};

#pragma region Botón

Button::Button(float x, float y, float width, float height, const char* s, Color c, void (*Func)(void*), void* miptr):
UIElement(x,y,width,height), texto{s}, color{c}
, callback{CallBack(Func, miptr)}
{
    // ClickFunk = Func;
    // ptr = miptr;
}

void Button::Draw(){
    DrawRectangleRec(area, color);
    DrawText(texto, area.x, area.y, 12, BLACK);
};

void Button::UpdateScreen(Vector2 p){
    callback.Execute();
    WaitTime(0.1f);
}

#pragma endregion

#pragma region TextBox

TextBox::TextBox(float x, float y, float width, float height, string& reftxt): 
UIElement(x,y,width,height), seleccionado{false}, texto{reftxt}{};

void TextBox::Draw(){
    if(!seleccionado)
        DrawRectangleRec(area, NO_SELECCIONADO);
    else
        DrawRectangleRec(area, SELECCIONADO);
    DrawText(texto.c_str(), area.x, area.y, 12, BLACK);
};

void TextBox::UpdateScreen(Vector2 mouseposition){
    seleccionado = true;
}

void TextBox::UpdateKeyboard(KeyboardKey k){
    //bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
    if(seleccionado && (
    (KEY_A <= k && k <= KEY_Z) || 
    (KEY_ZERO <= k && KEY_NINE <= k) ||
    (KEY_KP_0 <= k && k <= KEY_KP_9)))
    {
        //TraceLog(LOG_ALL,"%d",(int)k);
        if(k > 320 && k < 329){
            texto.push_back((char)k-272);
        }
        else{
            texto.push_back((char)k);
        }
        
    }
}

#pragma endregion