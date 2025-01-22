#include "Scene.h"

Scene::Scene() :finishScreen{ UNKNOWN } {};

void Scene::ManageInterruptions(){
    if(IsMouseButtonDown(0)){
        OnMouseDown();
    }
    mousePosition = GetMousePosition();
    OnKeyPressed((KeyboardKey)GetKeyPressed());
};

void Scene::UpdateScreen(){
    ManageInterruptions();
};

Logo::Logo(){};

void Logo::InitScene()
{
	//finishScreen = 0;
	framesCounter = 0;
	lettersCount = 0;

	logoPositionX = GetScreenWidth() / 2 - 128;
	logoPositionY = GetScreenHeight() / 2 - 128;

	topSideRecWidth = 16;
	leftSideRecHeight = 16;
	bottomSideRecWidth = 16;
	rightSideRecHeight = 16;

	state = 0;
	alpha = 1.0f;
};

void Logo::UpdateScreen()
{
    if (state == 0)                 // State 0: Top-left square corner blink logic
    {
        framesCounter++;

        if (framesCounter == 80)
        {
            state = 1;
            framesCounter = 0;      // Reset counter... will be used later...
        }
    }
    else if (state == 1)            // State 1: Bars animation logic: top and left
    {
        topSideRecWidth += 8;
        leftSideRecHeight += 8;

        if (topSideRecWidth == 256) state = 2;
    }
    else if (state == 2)            // State 2: Bars animation logic: bottom and right
    {
        bottomSideRecWidth += 8;
        rightSideRecHeight += 8;

        if (bottomSideRecWidth == 256) state = 3;
    }
    else if (state == 3)            // State 3: "raylib" text-write animation logic
    {
        framesCounter++;

        if (lettersCount < 10)
        {
            if (framesCounter / 12)   // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }
        }
        else    // When all letters have appeared, just fade out everything
        {
            if (framesCounter > 200)
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    finishScreen = TITTLE;   // Jump to next screen
                }
            }
        }
    }
};

void Logo::DrawScreen()
{
    if (state == 0)         // Draw blinking top-left square corner
    {
        if ((framesCounter / 10) % 2) DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
    }
    else if (state == 1)    // Draw bars animation: top and left
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
    }
    else if (state == 2)    // Draw bars animation: bottom and right
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);

        DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
    }
    else if (state == 3)    // Draw "raylib" text-write animation + "powered by"
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));

        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));

        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, alpha));

        DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, alpha));

        if (framesCounter > 20) DrawText("powered by", logoPositionX, logoPositionY - 27, 20, Fade(DARKGRAY, alpha));
    }
};

Tittle::Tittle(Font f) : font{ f } 
{
    canvas = UI<Tittle>();
    canvas.AddButton(screenWidth/2,screenHeight/2,80,60, "Gameplay", WHITE, &Tittle::ToGameplay);
    // canvas.AddButton(screenWidth/2,screenHeight/2-70,80,60, "Decrementable", WHITE,{});
    
};

void Tittle::ToGameplay(){TraceLog(LOG_ALL,"EOEOEOEOEOEOE\n\n\n"); finishScreen = GAMEPLAY;}

void Tittle::UpdateScreen() {
    Scene::UpdateScreen();
    // if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    // {
    //     //finishScreen = 1;   // OPTIONS
    //     finishScreen = GAMEPLAY;   // GAMEPLAY
    // }
};

void Tittle::OnMouseDown(){
    canvas.Update(mousePosition);
};

void Tittle::DrawScreen() {

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), GREEN);
    Vector2 pos = { 20, 10 };
    DrawTextEx(font, "TITLE SCREEN", pos, font.baseSize * 3.0f, 4, DARKGREEN);
    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    canvas.Draw();

};