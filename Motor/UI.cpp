#include "UI.h"

UI::UI(){};

UIElement::UIElement(float x, float y, float width, float height) : area(Rectangle{x,y,width,height}){};

void UI::AddButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen & meptr){
    elements.push_back(new SceneButton(x,y,width,height, s, c, Func, meptr));
};

void UI::AddTextBox(float x, float y, float width, float height, char* s, bool & enter){
    elements.push_back(new TextBox(x, y, width, height,s, enter));
}

bool UIElement::IsInside(Vector2 mouseButton){ return CheckCollisionPointRec(mouseButton,area);}

void UI::Draw(){
    for(int i = 0; i < elements.size(); i++){
        elements[i]->Draw();
    }
};

void UI::UpdateScreen(Vector2 mouseposition){
    int i = 0;
    TraceLog(LOG_ALL,"Comprobando...");
    while (i < elements.size() && !elements[i]->IsInside(mouseposition))
    {
        i++;
    }
    if(i < elements.size())
        elements[i]->UpdateScreen(mouseposition);
    
}

SceneButton::SceneButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen & meptr)
: texto{s}, color{c}, ClickFunc{Func}, UIElement(x,y,width,height), ptr{meptr}
{};

void SceneButton::Draw(){
    DrawRectangleRec(area, color);
    DrawText(texto, area.x, area.y, 12, BLACK);
};

void SceneButton::UpdateScreen(Vector2 mouseposition){
    ClickFunc(ptr);
};

TextBox::TextBox(float x, float y, float width, float height, char* s, bool &enter): container{s}, enterPressed{enter}
, UIElement(x,y,width,height) {};

void TextBox::Draw(){
    DrawRectangleRec(area,WHITE);
    DrawText(container,area.x,area.y,12,BLACK);
}

void TextBox::UpdateKeyboard(KeyboardKey k){
    if(k == KEY_KP_ENTER){
        enterPressed = true;
    }
    else{
        container += k;
    }
}