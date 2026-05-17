#pragma once
#include <raylib.h>
#include "EngineObjects/UI.h"

enum GameScreen {
	UNKNOWN = -1,
	LOGO = 0,
	TITTLE = 1,
	GAMEPLAY = 2,
    DECREMENTABLE = 3
};

#define GameplayButtonText "Gameplay"
#define DecrementableButtonText "Cola decrementable"


class Scene {
protected:
	GameScreen finishScreen;
	Vector2 mousePosition;
	UI canvas;
	Color backgroundColor;
	
public:
	Scene();
	virtual void InitScene() = 0;
	virtual void UpdateScreen();
	virtual void DrawScreen() = 0;
	virtual void UnloadScreen() = 0;
	GameScreen FinishScreen() { return finishScreen; };

	virtual void OnMouseDown() = 0;
	virtual void OnKeyPressed(KeyboardKey) = 0;

	void ChangeScene(GameScreen sc){finishScreen = sc;}

private:
	void ManageInterruptions();
	
};