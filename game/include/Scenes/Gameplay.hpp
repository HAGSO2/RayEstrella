#pragma once
#include "ProgramFlow/Scene.h"
#include "EngineObjects/GameObject.h"
#include "Containers/AStar.h"
#include "CommonInfo.hpp"
#include "HardcodedStrings.hpp"

#pragma region Definitions
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
#define RessetButtonColor ORANGE
#define ResearchButtonColor GREEN
#pragma endregion


class Gameplay : public Scene{
    Node nodes[CELL_Y][CELL_X];
    Sprite* cells[CELL_Y][CELL_X];
    AStar estrella;

public:
    Gameplay();
    void InitScene() override;
	void UpdateScreen() override;
	void DrawScreen() override;
	void UnloadScreen() override {};
    void OnMouseDown() override;
    void OnKeyPressed(KeyboardKey) override;
    
    //This methos are public due the need of being called by the buttons in the UI, but they are not intended to be used outside of this class.
    void AllZero();
    void RessearchStart();
    
};