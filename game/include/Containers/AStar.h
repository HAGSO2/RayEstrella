#pragma once
#include <vector>
#include "ColaNodes.h"
#include "CommonInfo.hpp"
#include <raylib.h>
#include <raymath.h>

using namespace std;


class AStar{
    
    int steps = 0; 
    Node* currentPosition;
    vector<Node*> open;
    vector<Node*> closed;
    Position target;
    ColaNodes cola;
    Node (&tabletop)[CELL_Y][CELL_X];
    public:
    AStar(Node (&tabletop)[CELL_Y][CELL_X]);
    vector<Node*> Pathfinding(Position s, Position t);
    private:
    void Step();
    float Heuristic(Position s);
    //Añade a la lista opened los nodos colindantes
    void CalcNeightbours();
};