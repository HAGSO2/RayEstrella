#pragma once
#include <raylib.h>
#include <vector>
#include <string>

/*Tengo que sacar gameScreen del botón y hacerlo genérico*/

using namespace std;

class UIElement{
protected:
    Rectangle area;
public:
    UIElement(float x, float y, float width, float height);
    bool IsInside(Vector2);
    virtual void SetOut() = 0;
    virtual void Draw() = 0;
    virtual void UpdateScreen(Vector2) = 0;
    virtual void UpdateKeyboard(KeyboardKey) = 0;
};

class UI{ //Canvas
    vector<UIElement*> elements;
    public:
    UI();
    void AddButton(float x, float y, float width, float height, const char* s, Color c, void (*Func)(void*), void* miptr);
    //void AddButtonScene(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen &meptr);
    void AddTextBox(float x, float y, float width, float height, string& reftxt);
    void Draw();
    void UpdateScreen(Vector2);
    void UpdateKeyboard(KeyboardKey);

};

class CallBack{
    void* ptr;
    void (*ClickFunk)(void*);
    public:
    CallBack(void (*Func)(void*), void* miptrs);
    void Execute() {ClickFunk(ptr);}
};

class Button : public UIElement{
    const char* texto;
    Color color;
    CallBack callback;

    public:
    Button(float x, float y, float width, float height, const char* s, Color c, void (*Func)(void*), void* miptrs);
    void Draw();
    void SetOut() {};
    void UpdateScreen(Vector2);
    void UpdateKeyboard(KeyboardKey){};
};

#define NO_SELECCIONADO ORANGE
#define SELECCIONADO GREEN
class TextBox: public UIElement{
    string& texto;
    bool seleccionado;

    public:
    TextBox(float x, float y, float width, float height, string& reftxt);
    void Draw();
    void SetOut() {seleccionado = false;};
    void UpdateScreen(Vector2) ;
    void UpdateKeyboard(KeyboardKey);
};

