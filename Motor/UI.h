#include <raylib.h>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class UIElement{
protected:
    Rectangle area;
public:
    UIElement(float x, float y, float width, float height);
    bool IsInside(Vector2);
    virtual void Draw() = 0;
    virtual void Update(Vector2) = 0;
};

template <typename T>
class UI{ //Canvas
    vector<UIElement<T>*> elements;
    public:
    UI();
    void AddButton(float x, float y, float width, float height, char* s, Color c, void (T::*Func)());
    void Draw();
    void Update(Vector2);

};
template <typename T>
class Button : public UIElement<T>{
    char* texto;
    Color color;
    
    
    public:
    Button(float x, float y, float width, float height, char* s, Color c, void (T::*Func)());
    void Draw();
    private:
    //void (*funcPtr)()
    void (T::*ClickFunc)();
    void Update(Vector2);
};