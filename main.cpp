#include <iostream>
#include <raylib.h>
#include "./Escenas/EsDecrementable.h"

GameScreen currentScreen;
Scene* gameScenes[3] = {0};

Font font = { 0 };
Music music = { 0 };
Sound fxCoin = { 0 };


char TITTLE_OF_THE_GAME[] = "A estrella";

static float transAlpha = 0.0f;
static bool onTransition = false;
static bool transFadeOut = false;
static int transFromScreen = -1;
static GameScreen transToScreen = GameScreen(UNKNOWN);
static void InitStarters();
static void LoadResources();
static void UpdateDrawFrame();
static void TransitionToScreen(GameScreen screen);
static void UpdateTransition(void);
static void DrawTransition(void);

//Argumentos contemplados:
//Primer argumento: 1 debug ;2 normal
int main(int argc, char *argv[]) {
    InitWindow(screenWidth, screenHeight, TITTLE_OF_THE_GAME);
    SetTraceLogLevel(LOG_ALL);
    TraceLog(LOG_DEBUG,"\n\n\nDebugging ...\n\n\n");
    // if(argc >= 1 && atoi(argv[0])== 1){
        
    // }
    InitStarters();
    LoadResources();

    SetMusicVolume(music, 1.0f);
    PlayMusicStream(music);

    gameScenes[currentScreen]->InitScene();

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
    }

    gameScenes[currentScreen]->UnloadScreen();

    CloseAudioDevice();     // Close audio context

    CloseWindow();

    return 0;
}


static void InitStarters() { 
    SetTargetFPS(60);
    InitAudioDevice();
    

    gameScenes[LOGO] = new Logo();
    gameScenes[TITTLE] = new Tittle(font);
    gameScenes[GAMEPLAY] = new Gameplay();

    currentScreen = GameScreen(LOGO);
    
}

static void LoadResources() {
    font = LoadFont("resources/mecha.png");
    music = LoadMusicStream("resources/ambient.ogg");
    fxCoin = LoadSound("resources/coin.wav");
}

static void UpdateDrawFrame() {
    // Update
    //----------------------------------------------------------------------------------
    UpdateMusicStream(music);       // NOTE: Music keeps playing between screens

    if (!onTransition)
    {
        gameScenes[currentScreen]->UpdateScreen();
        GameScreen afterFinish = gameScenes[currentScreen]->FinishScreen();
        if (afterFinish != UNKNOWN) { TransitionToScreen(afterFinish); }
    }
    else UpdateTransition();    // Update transition (fade-in, fade-out)
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(RAYWHITE);

    gameScenes[currentScreen]->DrawScreen();

    // Draw full screen rectangle in front of everything
    if (onTransition) DrawTransition();

    //DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

static void TransitionToScreen(GameScreen screen)
{
    onTransition = true;
    transFadeOut = false;
    transFromScreen = currentScreen;
    transToScreen = screen;
    transAlpha = 0.0f;
}

static void UpdateTransition(void)
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
    else  // Transition fade out logic
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

// Draw transition effect (full-screen rectangle)
static void DrawTransition(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, transAlpha));
}