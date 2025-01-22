#include "../Motor/Scene.h"
#include "../Motor/GameObject.h"

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

enum CellType{
    DEFAULT = 0,
	WAY = 1,
	UNUSED_WAY = 2,
	HARDWALL = 3,
	WALL = 4,
	ENTRANCE = 5,
	EXIT = 6
};

struct Node{
    CellType type;
    bool visited;
    float weight;
    public:
    Node();
};

class Gameplay : public Scene{
    UI<Gameplay> canvas;
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