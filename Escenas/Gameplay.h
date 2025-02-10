#pragma once
#include "../Motor/Scene.h"
#include "../Motor/GameObject.h"
#include "Adicional.h"

#pragma once
#pragma region Definitions
#define CELL_X 10
#define CELL_Y 6
#define WORLD_X_OFFSET 75.0f
#define WORLD_Y_OFFSET 75.0f
#define CELL_SIZE 50
#define CELL_VISUAL 45
#define ENTRANCE_X 0
#define ENTRANCE_Y 2
#define ENTRANCE_COLOR YELLOW
#define END_X   9
#define END_Y   2
#define END_COLOR PURPLE
#pragma endregion


class Gameplay : public Scene{
    Node nodes[CELL_Y][CELL_X];
    Sprite* cells[CELL_Y][CELL_X];

public:
    Gameplay();
    void InitScene();
	void UpdateScreen() override;
	void DrawScreen();
	void UnloadScreen() {};
    void OnMouseDown();
    void OnKeyPressed(KeyboardKey);
};