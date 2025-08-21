#include "AStar.h"



AStar::AStar(Node (&tabl)[CELL_Y][CELL_X]): tabletop{tabl}, cola{ColaNodes(CELL_X*CELL_Y+1)}, 
steps{0},currentPosition{nullptr},  open{vector<Node*>()}, closed{vector<Node*>()}, target{Position2(0,0)}
{};

vector<Node*> AStar::Pathfinding(Position2 source, Position2 t){
    open = vector<Node*>();
    closed = vector<Node*>();
    target = t;

    currentPosition = tabletop[source.j,source.i];
    closed.push_back(currentPosition);

    while (currentPosition->position.j != target.j || currentPosition->position.i != target.i)
    {
        TraceLog(LOG_ALL,"Paso");
        /* code */
        Step();
        steps++;
    }
    return closed;
}

void AStar::Step(){
    TraceLog(LOG_DEBUG,"Desde: X:%d, Y:%d",currentPosition->position.j,currentPosition->position.i);
    CalcNeightbours();
    for(int i = 0; i < open.size(); i++){
        //TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open[i]->index, open[i]->position.j,open[i]->position);
        open[i]->father = currentPosition;
        cola.Añadir(open[i], Heuristic(open[i]->position));
    };
    Node* best = cola.MirarMínimo();
    TraceLog(LOG_DEBUG,"Mira mínimo");
    TraceLog(LOG_DEBUG, "Mejor: %d", best->index);
    cola.EliminaMínimo();
    TraceLog(LOG_DEBUG,"Minimo eliminado");
    closed.push_back(best);
    open = vector<Node*>();
    currentPosition = best;

};

float AStar::Heuristic(Position2 s){
    float result = sqrtf((s.j - target.j)*(s.j - target.j) + (s.i - target.i)*(s.i - target.i));
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
    (tabletop[currentPosition->position.i-1][currentPosition->position.j-1].type != WALL &&
     tabletop[currentPosition->position.i-1][currentPosition->position.j-1].type != HARDWALL)){
        TraceLog(LOG_DEBUG,"AnteArriba");
        open.push_back(&tabletop[currentPosition->position.i-1][currentPosition->position.j-1]);
        TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open.back()->index, open.back()->position.j,open.back()->position.i);
    }
    //O
    //ĉ
    if((currentPosition->position.i > 0 ) &&
    (tabletop[currentPosition->position.i-1][currentPosition->position.j].type != WALL &&
     tabletop[currentPosition->position.i-1][currentPosition->position.j].type != HARDWALL)){
        TraceLog(LOG_DEBUG,"Arriba");
        open.push_back(&tabletop[currentPosition->position.i-1][currentPosition->position.j]);
        TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open.back()->index, open.back()->position.j,open.back()->position.i);
    }
    // O
    //Ć
    if((currentPosition->position.i > 0 && currentPosition->position.j < CELL_X-1) &&
    (tabletop[currentPosition->position.i-1][currentPosition->position.j+1].type != WALL &&
     tabletop[currentPosition->position.i-1][currentPosition->position.j+1].type != HARDWALL)){
        TraceLog(LOG_DEBUG,"PostArriba");
        open.push_back(&tabletop[currentPosition->position.i-1][currentPosition->position.j+1]);
        TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open.back()->index, open.back()->position.j,open.back()->position.i);
    }
    //O < C
    if((currentPosition->position.j > 0) &&
    (tabletop[currentPosition->position.i][currentPosition->position.j-1].type != WALL &&
     tabletop[currentPosition->position.i][currentPosition->position.j-1].type != HARDWALL)){
        TraceLog(LOG_DEBUG,"Anterior");
        open.push_back(&tabletop[currentPosition->position.i][currentPosition->position.j-1]);
        TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open.back()->index, open.back()->position.j,open.back()->position.i);
    }
    //C > O
    if((currentPosition->position.j < CELL_X-1) &&
    (tabletop[currentPosition->position.i][currentPosition->position.j+1].type != WALL &&
     tabletop[currentPosition->position.i][currentPosition->position.j+1].type != HARDWALL)){
        TraceLog(LOG_DEBUG,"Posterior");
        open.push_back(&tabletop[currentPosition->position.i][currentPosition->position.j+1]);
        TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open.back()->index, open.back()->position.j,open.back()->position.i);
    }
    // C
    //Ó
    if((currentPosition->position.j > 0 && currentPosition->position.i < CELL_Y-1) &&
    (tabletop[currentPosition->position.i+1][currentPosition->position.j-1].type != WALL &&
     tabletop[currentPosition->position.i+1][currentPosition->position.j-1].type != HARDWALL)){
        TraceLog(LOG_DEBUG,"AnteDebajo");
        open.push_back(&tabletop[currentPosition->position.i+1][currentPosition->position.j-1]);
        TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open.back()->index, open.back()->position.j,open.back()->position.i);
    }
    //C
    //V
    //O
    if((currentPosition->position.i < CELL_Y-1) &&
    (tabletop[currentPosition->position.i+1][currentPosition->position.j].type != WALL &&
     tabletop[currentPosition->position.i+1][currentPosition->position.j].type != HARDWALL)){
        TraceLog(LOG_DEBUG,"Debajo");
        open.push_back(&tabletop[currentPosition->position.i+1][currentPosition->position.j]);
        TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open.back()->index, open.back()->position.j,open.back()->position.i);
    }
    //C
    // Ò
    if((currentPosition->position.j < CELL_X-1 && currentPosition->position.i < CELL_Y-1) &&
    (tabletop[currentPosition->position.i+1][currentPosition->position.j+1].type != WALL &&
     tabletop[currentPosition->position.i+1][currentPosition->position.j+1].type != HARDWALL)){
        TraceLog(LOG_DEBUG,"PostDebajo");
        open.push_back(&tabletop[currentPosition->position.i+1][currentPosition->position.j+1]);
        TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open.back()->index, open.back()->position.j,open.back()->position.i);
    }
}