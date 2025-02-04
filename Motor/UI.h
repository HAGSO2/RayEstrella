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
    virtual void IsOut() = 0;
    virtual void Draw() = 0;
    virtual void UpdateScreen(Vector2) = 0;
    virtual void UpdateKeyboard(KeyboardKey) = 0;
};

class UI{ //Canvas
    vector<UIElement*> elements;
    public:
    UI();
    void AddButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen &meptr);
    void AddTextBox(float x, float y, float width, float height, string& s, bool & enter, bool & selec);
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
    void IsOut(){};
    void (*ClickFunc)(GameScreen &);
    void UpdateScreen(Vector2);
    void UpdateKeyboard(KeyboardKey){};
};

class TextBox: public UIElement{
    string &container;
    bool &enterPressed;
    bool &selected;

    public:
    TextBox(float x, float y, float width, float height, string& s, bool & enter, bool & selec);
    void IsOut() {selected = false;}
    void Draw();
    void UpdateScreen(Vector2) {selected = !selected; WaitTime(0.1f);};
    void UpdateKeyboard(KeyboardKey);
};