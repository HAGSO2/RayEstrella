#include "Scenes/Tittle.h"

void ToGameplay(void *ptr)
{
    ((Tittle *)ptr)->ChangeScene(GAMEPLAY);
};

void ToDecrementable(void *ptr)
{
    ((Tittle *)ptr)->ChangeScene(DECREMENTABLE);
    TraceLog(LOG_DEBUG, "Transitioning to Decrementable scene...");
};

Tittle::Tittle(Font f, int w, int h) : font{f}, screenWidth{w}, screenHeight{h}
{
    canvas = UI();
    canvas.AddButton(screenWidth / 2, screenHeight / 2, 80, 60, "Gameplay", WHITE, ToGameplay, this);
    canvas.AddButton(screenWidth / 2, screenHeight / 2 + 70, 100, 60, "Cola decrementable", WHITE, ToDecrementable, this);
    //canvas.AddButton(screenWidth / 2, screenHeight / 2 - 70, 80, 60, "Decrementable", WHITE, {},this);
};

void Tittle::UpdateScreen()
{
    Scene::UpdateScreen();
    // if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    // {
    //     //finishScreen = 1;   // OPTIONS
    //     finishScreen = GAMEPLAY;   // GAMEPLAY
    // }
};

void Tittle::OnMouseDown()
{
    canvas.UpdateScreen(mousePosition);
};

void Tittle::DrawScreen()
{

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    Vector2 pos = {20, 10};
    DrawTextEx(font, "TITLE SCREEN", pos, font.baseSize * 3.0f, 4, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    canvas.Draw();
};