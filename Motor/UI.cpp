#include "UI.h"

UI::UI(){};

UIElement::UIElement(float x, float y, float width, float height) : area(Rectangle{x,y,width,height}){};

SceneButton::SceneButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen & meptr)
: texto{s}, color{c}, ClickFunc{Func}, UIElement(x,y,width,height), ptr{meptr}
{};

void UI::AddButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen & meptr){
    elements.push_back(new SceneButton(x,y,width,height, s, c, Func, meptr));
};


bool UIElement::IsInside(Vector2 mouseButton){ return CheckCollisionPointRec(mouseButton,area);}

void UI::Draw(){
    for(int i = 0; i < elements.size(); i++){
        elements[i]->Draw();
    }
};

void UI::Update(Vector2 mouseposition){
    int i = 0;
    TraceLog(LOG_ALL,"Comprobando...");
    while (i < elements.size() && !elements[i]->IsInside(mouseposition))
    {
        i++;
    }
    if(i < elements.size())
        elements[i]->Update(mouseposition);
    
}



void SceneButton::Draw(){
    DrawRectangleRec(area, color);
    DrawText(texto, area.x, area.y, 12, BLACK);
};

void SceneButton::Update(Vector2 mouseposition){
    ClickFunc(ptr);
}