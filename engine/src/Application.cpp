#include "ProgramFlow/Application.hpp"
#include <raylib.h>

void Application::run()
{
    // Main application loop code here
    Init();

    while (!WindowShouldClose())
    {
        Update();

        Draw();
    }

    Unload();

    CloseWindow();
}