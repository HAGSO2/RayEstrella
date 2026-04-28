#include "ProgramFlow/Application.hpp"
#include "ProgramFlow/Scene.h"
#include "CommonInfo.h"

#include "Scenes/Logo.h"
#include "Scenes/Tittle.h"
#include "Scenes/Gameplay.h"
#include "Scenes/EsDecrementable.h"

class Game : public Application
{
public:
    Game(int w, int h, int fps, string name)
    {
        screenWidth = w;
        screenHeight = h;
        FPs = fps;
        ApplicationName = name;
    }

    /********************
     * GLOBAL VARIABLES *
     ********************/
    Font font = {0};
    Music music = {};

    // TODO: Take this to the Application class, maybe with some methods to manage it?
    GameScreen currentScreen;
    Scene *gameScenes[4] = {0};
    float transAlpha = 0.0f;
    bool onTransition = false;
    bool transFadeOut = false;
    int transFromScreen = -1;
    GameScreen transToScreen = GameScreen(UNKNOWN);

    void LoadResources();
    void InitStarters();
    void UpdateDrawFrame();
    // TODO: Take this to the Application class, maybe with some methods to manage it?
    void TransitionToScreen(GameScreen screen);
    void UpdateTransition(void);
    void DrawTransition(void);

public:
    void Init() override;
    void Update() override;
    void Draw() override;
    void Unload() override;
};