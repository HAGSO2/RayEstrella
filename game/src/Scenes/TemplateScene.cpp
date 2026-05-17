#include "Scenes/TemplateScene.hpp"

// Constructor
TemplateScene::TemplateScene(): Scene()
{
    // Initialize UI canvas and add buttons
    canvas = UI();
    backgroundColor = GREEN;
};

void TemplateScene::InitScene() {
    // Initialize scene elements here (e.g., load textures, set up UI, etc.)
};

void TemplateScene::UpdateScreen()
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen();
};

void TemplateScene::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    // Background
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), backgroundColor);
    // Draw buttons and other UI elements
    canvas.Draw();
};

void TemplateScene::UnloadScreen() {
    // Unload scene resources here (e.g., textures, sounds, etc.)
};

void TemplateScene::OnMouseDown()
{
    // Handle mouse click events here (e.g., check if buttons are clicked)
    canvas.UpdateScreen(mousePosition);
};

void TemplateScene::OnKeyPressed(KeyboardKey k)
{
    // Handle key press events here (e.g., check if specific keys are pressed)
    canvas.UpdateKeyboard(k);
};
