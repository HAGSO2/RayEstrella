#pragma once
#include <vector>
#include "ColaCasillas.h"
#include "../Escenas/Adicional.h"
#include <raylib.h>
#include <raymath.h>

using namespace std;


class AStar{
    
    int steps = 0; 
    Node* currentPosition;
    vector<Node*> open;
    vector<Node*> closed;
    ColaCasillas<Node*> cola;
    Node (&tabletop)[CELL_Y][CELL_X];
    public:
    AStar(Node (&tabletop)[CELL_Y][CELL_X]);
    vector<Node*> Pathfinding(Position2 s, Position2 t);

    private:
    void Step(Position2 target);
    float Heuristic(Position2 s, Position2 t);
    //Añade a la lista opened los nodos colindantes
    void CalcNeightbours();
};