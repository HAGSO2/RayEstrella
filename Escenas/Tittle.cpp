#include "Tittle.h"

void ToGameplay(GameScreen & ptr){
    ptr = GAMEPLAY;
};

void ToDecrementable(GameScreen & ptr){
    ptr = DECREMENTABLE;
};

Tittle::Tittle(Font f) : font{ f } 
{
    canvas = UI();
    canvas.AddButton(screenWidth/2,screenHeight/2,80,60, "Gameplay", WHITE, ToGameplay, finishScreen);
    canvas.AddButton(screenWidth/2,screenHeight/2 + 70,100,60, "Cola decrementable", WHITE, ToDecrementable, finishScreen);
    // canvas.AddButton(screenWidth/2,screenHeight/2-70,80,60, "Decrementable", WHITE,{});
    
};


void Tittle::UpdateScreen() {
    Scene::UpdateScreen();
    // if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    // {
    //     //finishScreen = 1;   // OPTIONS
    //     finishScreen = GAMEPLAY;   // GAMEPLAY
    // }
};

void Tittle::OnMouseDown(){
    canvas.UpdateScreen(mousePosition);
};

void Tittle::DrawScreen() {

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "TITLE SCREEN", pos, font.baseSize * 3.0f, 4, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    canvas.Draw();

};