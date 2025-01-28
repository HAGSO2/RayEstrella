#include <raylib.h>
#include <vector>
#include <string>

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
    void AddButton(float x, float y, float width, float height, char* s, Color c, void (*Func)(void *& variable), void *&meptr);
    void Draw();
    void Update(Vector2);

};

class Button : public UIElement{
    char* texto;
    Color color;
    void *&ptr;
    
    
    public:
    Button(float x, float y, float width, float height, char* s, Color c, void (*Func)(void *& variable), void *&meptr);
    void Draw();
    private:
    //void (*funcPtr)()
    void (*ClickFunc)(void *&);
    void Update(Vector2);
};