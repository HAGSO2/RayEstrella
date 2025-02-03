#include <raylib.h>
#include <vector>
#include <string>
#include "CommonInfo.h"

using namespace std;

class UIElement{
protected:
    Rectangle area;
public:
    UIElement(float x, float y, float width, float height);
    bool IsInside(Vector2);
    virtual void Draw() = 0;
    virtual void Update(Vector2) = 0;
};

class UI{ //Canvas
    vector<UIElement*> elements;
    public:
    UI();
    void AddButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(GameScreen & variable), GameScreen &meptr);
    void Draw();
    void Update(Vector2);

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
    void Update(Vector2);
};