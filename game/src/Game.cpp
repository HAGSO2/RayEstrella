#include "Game.hpp"
#include <raylib.h>
#include "AssetsPath.hpp"

void Game::LoadResources()
{
    // Load game resources here (e.g., textures, sounds, etc.)
    // TODO: Make this more generic, maybe with a ResourceManager class?
    //font = LoadFont(Font);
    music = LoadMusicStream(Music);
}

void Game::InitStarters()
{
    SetTargetFPS(FPs);
    //  Audio device must be initialized before loading any sound/music
    InitAudioDevice();
    //  Initialize game scenes and other necessary components here
    gameScenes[LOGO] = new Logo();
    gameScenes[TITTLE] = new Tittle(font, screenWidth, screenHeight);
    gameScenes[GAMEPLAY] = new Gameplay();
    gameScenes[DECREMENTABLE] = new EsDecrementable();

    currentScreen = LOGO;
}

//  Init Game
void Game::Init()
{
    // Initialize window and traces log.
    InitWindow(screenWidth, screenHeight, ApplicationName.c_str());
    SetTraceLogLevel(LOG_ALL);

    // Initialize game resources here
    InitStarters();
    LoadResources();

    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    gameScenes[currentScreen]->InitScene();
}
// Update logic (input, music, etc.)
void Game::Update()
{
    UpdateMusicStream(music); // NOTE: Music keeps playing between screens

    if (!onTransition)
    {
        gameScenes[currentScreen]->UpdateScreen();
        GameScreen afterFinish = gameScenes[currentScreen]->FinishScreen();
        if (afterFinish != UNKNOWN)
        {
            TransitionToScreen(afterFinish);
        }
    }
    else
        UpdateTransition(); // Update transition (fade-in, fade-out)
}
// Draw game elements on the screen
void Game::Draw()
{
    // Draw game elements here
    BeginDrawing();

    ClearBackground(RAYWHITE);
    // Draw current screen
    gameScenes[currentScreen]->DrawScreen();

    // Draw full screen rectangle in front of everything
    if (onTransition)
        DrawTransition();

    // DrawFPS(10, 10);

    EndDrawing();
}
// Unload game resources and close the game
void Game::Unload()
{
    gameScenes[currentScreen]->UnloadScreen();

    CloseAudioDevice(); // Close audio context
}

#pragma region Transition Methods

void Game::TransitionToScreen(GameScreen screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

void Game::UpdateTransition()
{
    if (!transFadeOut)
    {
        transAlpha += 0.05f;

        // NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
        // For that reason we compare against 1.01f, to avoid last frame loading stop
        if (transAlpha > 1.01f)
        {
            transAlpha = 1.0f;

            // Unload current screen
            gameScenes[currentScreen]->UnloadScreen();
            currentScreen = transToScreen;
            // Load next screen
            gameScenes[currentScreen]->InitScene();

            currentScreen = transToScreen;

            // Activate fade out effect to next loaded screen
            transFadeOut = true;
        }
    }
    else // Transition fade out logic
    {
        transAlpha -= 0.02f;

        if (transAlpha < -0.01f)
        {
            transAlpha = 0.0f;
            transFadeOut = false;
            onTransition = false;
            transFromScreen = -1;
            transToScreen = GameScreen(UNKNOWN);
        }
    }
}

void Game::DrawTransition()
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}

#pragma endregion