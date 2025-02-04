#pragma once
#include "../Motor/Scene.h"

class EsDecrementable : public Scene{
    string& lenth;

    bool canvasUpdate;
    bool selected;
    public:
    EsDecrementable(string& ref);
    void InitScene() {finishScreen = UNKNOWN;};
	void UpdateScreen() override;
	void DrawScreen();
	void UnloadScreen() {};
    void OnMouseDown();
    void OnKeyPressed(KeyboardKey);

};
