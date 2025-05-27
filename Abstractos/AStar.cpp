#include "AStar.h"



AStar::AStar(Node (&tabl)[CELL_Y][CELL_X]): tabletop{tabl}, cola{ColaCasillas(CELL_X*CELL_Y)}, 
steps{0},currentPosition{NodePos{Vector2{0,0},nullptr}},  open{vector<NodePos>()}, closed{vector<NodePos>()}
{};

vector<Node> AStar::Pathfinding(Vector2 source, Vector2 target){
    vector<Node> finalList;
    open = vector<NodePos>();
    closed = vector<NodePos>();

    currentPosition.pos = source;
    open.push_back(currentPosition);

    while (currentPosition.pos.x != target.x && currentPosition.pos.y != target.y)
    {
        /* code */
        Step(target);
        steps++;
    }
    
    

    return finalList;
}

void AStar::Step(Vector2 target){
    CalcNeightbours();
    for(int i = 0; i < open.size(); i++){
        cola.Añadir(open[i], Heuristic(open[i].pos,target));
    };
    int cual = cola.MirarMínimo();
    cola.EliminaMínimo();
    open = vector<NodePos>();
    

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
    if((currentPosition.pos.x > 0 && currentPosition.pos.y > 0) &&
    tabletop[(int)currentPosition.pos.x-1][(int)currentPosition.pos.y-1].type != WALL ||
    tabletop[(int)currentPosition.pos.x-1][(int)currentPosition.pos.y-1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //O
    //ĉ
    if((currentPosition.pos.y > 0 ) &&
    tabletop[(int)currentPosition.pos.x][(int)currentPosition.pos.y-1].type != WALL ||
    tabletop[(int)currentPosition.pos.x][(int)currentPosition.pos.y-1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    // O
    //Ć
    if((currentPosition.pos.y > 0 && currentPosition.pos.x < CELL_X-1) &&
    tabletop[(int)currentPosition.pos.x+1][(int)currentPosition.pos.y-1].type != WALL ||
    tabletop[(int)currentPosition.pos.x+1][(int)currentPosition.pos.y-1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //O < C
    if((currentPosition.pos.x > 0) &&
    tabletop[(int)currentPosition.pos.x-1][(int)currentPosition.pos.y].type != WALL ||
    tabletop[(int)currentPosition.pos.x-1][(int)currentPosition.pos.y].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //C > O
    if((currentPosition.pos.x < CELL_X-1) &&
    tabletop[(int)currentPosition.pos.x+1][(int)currentPosition.pos.y].type != WALL ||
    tabletop[(int)currentPosition.pos.x+1][(int)currentPosition.pos.y].type != HARDWALL){
        open.push_back(currentPosition);
    }
    // C
    //Ó
    if((currentPosition.pos.x > 0 && currentPosition.pos.y < CELL_Y-1) &&
    tabletop[(int)currentPosition.pos.x-1][(int)currentPosition.pos.y+1].type != WALL ||
    tabletop[(int)currentPosition.pos.x-1][(int)currentPosition.pos.y+1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //C
    //V
    //O
    if((currentPosition.pos.y < CELL_Y-1) &&
    tabletop[(int)currentPosition.pos.x][(int)currentPosition.pos.y+1].type != WALL ||
    tabletop[(int)currentPosition.pos.x][(int)currentPosition.pos.y+1].type != HARDWALL){
        open.push_back(currentPosition);
    }
    //C
    // Ò
    if((currentPosition.pos.x < CELL_X-1 && currentPosition.pos.y < CELL_Y-1) &&
    tabletop[(int)currentPosition.pos.x+1][(int)currentPosition.pos.y+1].type != WALL ||
    tabletop[(int)currentPosition.pos.x+1][(int)currentPosition.pos.y+1].type != HARDWALL){
        open.push_back(currentPosition);
    }
}