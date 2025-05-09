#pragma once
#include <vector>
#include "ColaCasillas.h"
#include "../Escenas/Adicional.h"

using namespace std;

class AStar{
    int steps;
    vector<Node> open;
    vector<Node> closed;
    ColaCasillas cola;
    Node *&tabletop[][];
    public:
    AStar();
    vector<Node> Pathfinding();

    private:
    void Step();
    void CalcNeightbours();
};