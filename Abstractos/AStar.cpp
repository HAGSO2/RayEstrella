#include "AStar.h"

AStar::AStar(Node (&tabl)[CELL_Y][CELL_X]): tabletop{tabl}, cola{ColaCasillas(CELL_X*CELL_Y)}, 
steps{0}, open{vector<Node>()}, closed{vector<Node>()}
{};

vector<Node> AStar::Pathfinding(Vector2 source, Vector2 target){
    vector<Node> finalList;
    open = vector<Vector2>();
    closed = vector<Vector2>();

    currentPosition = source;
    open.push_back(currentPosition);

    while (currentPosition.x != target.x && currentPosition.y != target.y)
    {
        /* code */
        Step();
        steps++;
    }
    
    

    return finalList;
}

void AStar::Step(){
    CalcNeightbours();
    Vector2 current = open[0];
    //open.erase(current);
};

float AStar::Heuristic(Vector2 s, Vector2 t){
    return Vector2Distance(s,t) + steps;
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
    if((currentPosition.x > 0 && currentPosition.y > 0) &&
    tabletop[(int)currentPosition.x-1][(int)currentPosition.y-1].type != WALL ||
    tabletop[(int)currentPosition.x-1][(int)currentPosition.y-1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //O
    //ĉ
    if((currentPosition.y > 0 ) &&
    tabletop[(int)currentPosition.x][(int)currentPosition.y-1].type != WALL ||
    tabletop[(int)currentPosition.x][(int)currentPosition.y-1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    // O
    //Ć
    if((currentPosition.y > 0 && currentPosition.x < CELL_X-1) &&
    tabletop[(int)currentPosition.x+1][(int)currentPosition.y-1].type != WALL ||
    tabletop[(int)currentPosition.x+1][(int)currentPosition.y-1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //O < C
    if((currentPosition.x > 0) &&
    tabletop[(int)currentPosition.x-1][(int)currentPosition.y].type != WALL ||
    tabletop[(int)currentPosition.x-1][(int)currentPosition.y].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //C > O
    if((currentPosition.x < CELL_X-1) &&
    tabletop[(int)currentPosition.x+1][(int)currentPosition.y].type != WALL ||
    tabletop[(int)currentPosition.x+1][(int)currentPosition.y].type != HARDWALL){
        open.push_back(currentPosition);
    }
    // C
    //Ó
    if((currentPosition.x > 0 && currentPosition.y < CELL_Y-1) &&
    tabletop[(int)currentPosition.x-1][(int)currentPosition.y+1].type != WALL ||
    tabletop[(int)currentPosition.x-1][(int)currentPosition.y+1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //C
    //V
    //O
    if((currentPosition.y < CELL_Y-1) &&
    tabletop[(int)currentPosition.x][(int)currentPosition.y+1].type != WALL ||
    tabletop[(int)currentPosition.x][(int)currentPosition.y+1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //C
    // Ò
    if((currentPosition.x < CELL_X-1 && currentPosition.y < CELL_Y-1) &&
    tabletop[(int)currentPosition.x+1][(int)currentPosition.y+1].type != WALL ||
    tabletop[(int)currentPosition.x+1][(int)currentPosition.y+1].type != HARDWALL){
        open.push_back(currentPosition);
    }
}