#include "UI.h"

template <typename T>
UI<T>::UI(){};

template <typename T>
UIElement<T>::UIElement(float x, float y, float width, float height) : area(Rectangle{x,y,width,height}){};

template <typename T>
bool UIElement<T>::IsInside(Vector2 mouseButton){ return CheckCollisionPointRec(mouseButton,area);}

template <typename T>
void UI<T>::AddButton(float x, float y, float width, float height, char* s, Color c, void (T::*Func)()){
    elements.push_back(new Button<T>(x,y,width,height, s, c, Func));
};

template <typename T>
void UI<T>::Draw(){
    for(int i = 0; i < elements.size(); i++){
        elements[i]->Draw();
    }
};

template <typename T>
void UI<T>::Update(Vector2 mouseposition){
    int i = 0;
    while (i < elements.size() && !elements[i]->IsInside(mouseposition))
    {
        i++;
    }
    if(i < elements.size())
        elements[i]->Update(mouseposition);
    
}

template <typename T>
Button<T>::Button(float x, float y, float width, float height, char* s, Color c, void (T::*Func)())
: texto{s}, color{c}, ClickFunc{Func}, UIElement<T>(x,y,width,height)
{};

template <typename T>
void Button<T>::Draw(){
    //DrawRectangleRec(area, color);
    //DrawText(texto, area.x, area.y, 12, BLACK);
};

template <typename T>
void Button<T>::Update(Vector2 mouseposition){
    ClickFunc();
}