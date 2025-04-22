#pragma once
#include <raylib.h>
#include <string>

using namespace std;

class GameObject{
    Transform transform;
public:
    GameObject();
    Transform GetTransform() {return transform;};
    virtual void DrawObject() = 0;
};

class Sprite : public GameObject{
    Vector2 position;
    Vector2 size;
    Color color;
public:
    Sprite(Vector2 f, Vector2 s, Color c);
    void ChangeColor(Color c);
    void DrawObject();
};

class TextShape : public GameObject{
    Rectangle area;
    string text;
    int note;
    Color color;
    public:
    TextShape(float x, float y, float width, float height, string txt, Color col);
    void ChangeColor(Color c);
    void ChangeText(string newText);
    void DrawObject();
};