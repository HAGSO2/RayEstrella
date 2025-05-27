#pragma once
#include <vector>
#include "ColaCasillas.h"
#include "../Escenas/Adicional.h"
#include <raylib.h>
#include <raymath.h>
#include "NodePos.h"

using namespace std;


class AStar{
    
    int steps = 0; 
    NodePos currentPosition;
    vector<NodePos> open;
    vector<NodePos> closed;
    ColaCasillas<NodePos*> cola;
    Node (&tabletop)[CELL_Y][CELL_X];
    public:
    AStar(Node (&tabletop)[CELL_Y][CELL_X]);
    vector<Node> Pathfinding(Vector2 s, Vector2 t);

    private:
    void Step(Vector2 target);
    float Heuristic(Vector2 s, Vector2 t);
    //Añade a la lista opened los nodos colindantes
    void CalcNeightbours();
};