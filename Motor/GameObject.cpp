#include "GameObject.h"

GameObject::GameObject(){};

Sprite::Sprite(Vector2 pos, Vector2 siz, Color c): position{pos},size{siz},color{c}{}

void Sprite::DrawObject(){
    DrawRectangleV(position,size,color);
}

void Sprite::ChangeColor(Color c) {color = c;}

TextShape::TextShape(float x, float y, float width, float height, string txt, Color col):
area{Rectangle{x,y,width,height}}, color{col}, text{txt}{}

void TextShape::DrawObject(){
    DrawRectangleRec(area,color);
    DrawText(text.c_str(),area.x,area.y,10,BLACK);
};

void TextShape::ChangeColor(Color c) {color = c;}