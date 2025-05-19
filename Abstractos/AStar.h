#pragma once
#include <vector>
#include "ColaCasillas.h"
#include "../Escenas/Adicional.h"
#include <raylib.h>
#include <raymath.h>

using namespace std;


class AStar{
    int steps = 0; 
    Vector2 currentPosition;
    vector<Vector2> open;
    vector<Vector2> closed;
    ColaCasillas cola;
    Node (&tabletop)[CELL_Y][CELL_X];
    public:
    AStar(Node (&tabletop)[CELL_Y][CELL_X]);
    vector<Node> Pathfinding(Vector2 s, Vector2 t);

    private:
    void Step();
    float Heuristic(Vector2 s, Vector2 t);
    //Añade a la lista opened los nodos colindantes
    void CalcNeightbours();
};