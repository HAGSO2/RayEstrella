#pragma once
#include "../Motor/Scene.h"

class Tittle : public Scene {
	int framesCounter;
	Font font;
	int click;
	
public:
	Tittle(Font f);
	void InitScene() {finishScreen = UNKNOWN;};
	void UpdateScreen() override;
	void DrawScreen();
	void UnloadScreen() {finishScreen = UNKNOWN;};
	void OnMouseDown();
	void OnKeyPressed(KeyboardKey) {};
	private:
};