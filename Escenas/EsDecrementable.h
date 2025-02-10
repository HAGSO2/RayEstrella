#pragma once
#include "Adicional.h"
#include "../Motor/Scene.h"
#include "../Abstractos/Cola.h"

class EsDecrementable : public Scene{
    string& lenth;
    Cola cola;

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
