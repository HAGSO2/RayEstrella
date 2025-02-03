#pragma once
#include <raylib.h>

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