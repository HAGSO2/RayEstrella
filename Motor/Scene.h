#include <raylib.h>
#include "UI.h"

enum GameScreen {
	UNKNOWN = -1,
	LOGO = 0,
	TITTLE = 1,
	GAMEPLAY = 2
};

    const int screenWidth = 800;
    const int screenHeight = 600;


class Scene {
protected:
	GameScreen finishScreen;
	Vector2 mousePosition;
	
public:
	Scene();
	virtual void InitScene() = 0;
	virtual void UpdateScreen();
	virtual void DrawScreen() = 0;
	virtual void UnloadScreen() = 0;
	GameScreen FinishScreen() { return finishScreen; };

	virtual void OnMouseDown() = 0;
	virtual void OnKeyPressed(KeyboardKey) = 0;

private:
	void ManageInterruptions();
	
};

class Logo : public Scene {
	int framesCounter;

	int logoPositionX;
	int logoPositionY;

	int lettersCount;

	int topSideRecWidth;
	int leftSideRecHeight;

	int bottomSideRecWidth;
	int rightSideRecHeight;

	int state;
	float alpha;
public:
	Logo();
	void InitScene();
	void UpdateScreen() override;
	void DrawScreen();
	void UnloadScreen() {};
	void OnMouseDown() {};
	void OnKeyPressed(KeyboardKey) {};
};

class Tittle : public Scene {
	int framesCounter;
	Font font;
	int click;

	UI<Tittle> canvas;

	
public:
	Tittle(Font f);
	void InitScene() {finishScreen = UNKNOWN;};
	void UpdateScreen() override;
	void DrawScreen();
	void UnloadScreen() {finishScreen = UNKNOWN;};
	void OnMouseDown();
	void OnKeyPressed(KeyboardKey) {};
	private:
	void ToGameplay();
};