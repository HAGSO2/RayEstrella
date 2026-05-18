#include "Scenes/Tittle.h"
#include "HardcodedStrings.hpp"
#pragma region To other scenes

void ToGameplay(void *ptr)
{
    // Just change the finishScreen to the Gameplay
    ((Tittle *)ptr)->ChangeScene(GAMEPLAY);
    TraceLog(LOG_DEBUG, "Transitioning to Gameplay scene...");
};

void ToDecrementable(void *ptr)
{
    // Just change the finishScreen to the Gameplay
    ((Tittle *)ptr)->ChangeScene(DECREMENTABLE);
    TraceLog(LOG_DEBUG, "Transitioning to Decrementable scene...");
};

#pragma endregion

// Constructor
Tittle::Tittle(Font f, int w, int h) : font{f}, screenWidth{w}, screenHeight{h}
{
    // Initialize UI canvas and add buttons
    canvas = UI();
    backgroundColor = GREEN;
    // Add buttons to the canvas with their respective callback functions
    canvas.AddButton(screenWidth / 2, screenHeight / 2, 80, 60, GameplayButtonText, WHITE, ToGameplay, this);
    canvas.AddButton(screenWidth / 2, screenHeight / 2 + 70, 100, 60, DecrementableButtonText, WHITE, ToDecrementable, this);
};

void Tittle::UpdateScreen()
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen();
};

void Tittle::OnMouseDown()
{
    // Handle mouse click events here (e.g., check if buttons are clicked)
    canvas.UpdateScreen(mousePosition);
};

void Tittle::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);

    // Title text
    DrawText(TitleScreenText, 180, 200, 30, BLACK);
    //DrawTextEx(font, TitleScreenText, Vector2{20, 10}, font.baseSize * 3.0f, 4, BLACK);
    // Draw buttons and other UI elements
    canvas.Draw();
};