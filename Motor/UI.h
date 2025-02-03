#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include "CommonInfo.h"

/*Tengo que sacar gameScreen del botón y hacerlo genérico*/

using namespace std;

class UIElement{
protected:
    Rectangle area;
public:
    UIElement(float x, float y, float width, float height);
    bool IsInside(Vector2);
    virtual void Draw() = 0;
    virtual void UpdateScreen(Vector2) = 0;
    virtual void UpdateKeyboard(KeyboardKey) = 0;
};

class UI{ //Canvas
    vector<UIElement*> elements;
    public:
    UI();
    void AddButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen &meptr);
    void AddTextBox(float x, float y, float width, float height, char* s, bool & enter);
    void Draw();
    void UpdateScreen(Vector2);
    void UpdateKeyboard(KeyboardKey);

};

class SceneButton : public UIElement{
    char* texto;
    Color color;
    GameScreen &ptr;
    
    
    public:
    SceneButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen &meptr);
    void Draw();
    private:
    //void (*funcPtr)()
    void (*ClickFunc)(GameScreen &);
    void UpdateScreen(Vector2);
    void UpdateKeyboard(KeyboardKey){};
};

class TextBox: public UIElement{
    char* container;
    bool &enterPressed;

    public:
    TextBox(float x, float y, float width, float height, char* s, bool & enter);
    void Draw();
    void UpdateScreen(Vector2) {};
    void UpdateKeyboard(KeyboardKey);
    void (*ClickFunc)();
};