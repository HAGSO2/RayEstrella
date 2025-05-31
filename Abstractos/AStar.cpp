#include "AStar.h"



AStar::AStar(Node (&tabl)[CELL_Y][CELL_X]): tabletop{tabl}, cola{ColaCasillas<Node*>(CELL_X*CELL_Y)}, 
steps{0},currentPosition{nullptr},  open{vector<Node*>()}, closed{vector<Node*>()}
{};

vector<Node*> AStar::Pathfinding(Position2 source, Position2 target){
    open = vector<Node*>();
    closed = vector<Node*>();

    currentPosition = tabletop[source.j,source.i];
    open.push_back(currentPosition);

    while (currentPosition->position.j != target.j && currentPosition->position.i != target.i)
    {
        /* code */
        Step(target);
        steps++;
    }
    return closed;
}

void AStar::Step(Position2 target){
    CalcNeightbours();
    for(int i = 0; i < open.size(); i++){
        cola.Añadir(open[i], Heuristic(open[i]->position,target));
    };
    Node* best = cola.MirarMínimo();
    cola.EliminaMínimo();
    closed.push_back(best);
    open = vector<Node*>();
    currentPosition = best;

};

float AStar::Heuristic(Position2 s, Position2 t){
    float result = sqrtf((s.j - t.j)*(s.j - t.j) + (s.i - t.i)*(s.i - t.i));
    return result + steps;
};

/*  
    *******
    *O O O*
    *^ ^ ^*
    *` | ´*
    *O<C>O*
    *´ | `*
    *v v v*
    *O O O*
    *******
*/

void AStar::CalcNeightbours(){
    // if((currentPosition.x > 0 && currentPosition.y > 0 && currentPosition.x < CELL_X-1 && currentPosition.y < CELL_Y-1) &&
    // tabletop[(int)currentPosition.x][(int)currentPosition.y].type != WALL ||
    // tabletop[(int)currentPosition.x][(int)currentPosition.y].type != HARDWALL){
    //     open.push_back(tabletop[(int)currentPosition.x][(int)currentPosition.y]);
    // }
    //O
    //`C
    if((currentPosition->position.j > 0 && currentPosition->position.i > 0) &&
    tabletop[currentPosition->position.j-1][currentPosition->position.i-1].type != WALL ||
    tabletop[currentPosition->position.j-1][currentPosition->position.i-1].type != HARDWALL){
        open.push_back(&tabletop[currentPosition->position.j-1][currentPosition->position.i-1]);
    }
    //O
    //ĉ
    if((currentPosition->position.i > 0 ) &&
    tabletop[currentPosition->position.j][currentPosition->position.i-1].type != WALL ||
    tabletop[currentPosition->position.j][currentPosition->position.i-1].type != HARDWALL){
        open.push_back(&tabletop[currentPosition->position.j][currentPosition->position.i-1]);
    }
    // O
    //Ć
    if((currentPosition->position.i > 0 && currentPosition->position.j < CELL_X-1) &&
    tabletop[currentPosition->position.j+1][currentPosition->position.i-1].type != WALL ||
    tabletop[currentPosition->position.j+1][currentPosition->position.i-1].type != HARDWALL){
        open.push_back(&tabletop[currentPosition->position.j+1][currentPosition->position.i-1]);
    }
    //O < C
    if((currentPosition->position.j > 0) &&
    tabletop[currentPosition->position.j-1][currentPosition->position.i].type != WALL ||
    tabletop[currentPosition->position.j-1][currentPosition->position.i].type != HARDWALL){
        open.push_back(&tabletop[currentPosition->position.j-1][currentPosition->position.i]);
    }
    //C > O
    if((currentPosition->position.j < CELL_X-1) &&
    tabletop[currentPosition->position.j+1][currentPosition->position.i].type != WALL ||
    tabletop[currentPosition->position.j+1][currentPosition->position.i].type != HARDWALL){
        open.push_back(&tabletop[currentPosition->position.j+1][currentPosition->position.i]);
    }
    // C
    //Ó
    if((currentPosition->position.j > 0 && currentPosition->position.i < CELL_Y-1) &&
    tabletop[currentPosition->position.j-1][currentPosition->position.i+1].type != WALL ||
    tabletop[currentPosition->position.j-1][currentPosition->position.i+1].type != HARDWALL){
        open.push_back(&tabletop[currentPosition->position.j-1][currentPosition->position.i+1]);
    }
    //C
    //V
    //O
    if((currentPosition->position.i < CELL_Y-1) &&
    tabletop[currentPosition->position.j][currentPosition->position.i+1].type != WALL ||
    tabletop[currentPosition->position.j][currentPosition->position.i+1].type != HARDWALL){
        open.push_back(&tabletop[currentPosition->position.j][currentPosition->position.i+1]);
    }
    //C
    // Ò
    if((currentPosition->position.j < CELL_X-1 && currentPosition->position.i < CELL_Y-1) &&
    tabletop[currentPosition->position.j+1][currentPosition->position.i+1].type != WALL ||
    tabletop[currentPosition->position.j+1][currentPosition->position.i+1].type != HARDWALL){
        open.push_back(&tabletop[currentPosition->position.j+1][currentPosition->position.i+1]);
    }
}