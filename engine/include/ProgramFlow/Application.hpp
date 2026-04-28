#pragma once
#include <string>
using namespace std;

class Application
{
protected:
    int screenWidth = 800;
    int screenHeight = 600;
    int FPs = 60;

    string ApplicationName = "Game";

public:
    void run();

protected:
    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw() {}
    virtual void Unload() {};
};