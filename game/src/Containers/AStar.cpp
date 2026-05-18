#include "Containers/AStar.h"
#include "iostream"

AStar::AStar(Node (&tabl)[CELL_Y][CELL_X]) : tabletop{tabl}, cola{ColaNodes(CELL_X * CELL_Y + 1)},
                                             steps{0}, currentPosition{nullptr}, open{vector<Node *>()}, closed{vector<Node *>()}, m_target{Position{0, 0}}
{ /*TraceLog(LOG_DEBUG,cola.ToString().c_str());*/
}

vector<Node *> AStar::Pathfinding(Position source, Position target)
{
    open = vector<Node *>();
    closed = vector<Node *>();
    currentPosition = nullptr;
    steps = 0;
    m_target = target;

    currentPosition = &tabletop[source.first][source.second];
    int aux = 0;
    cola.Añadir(currentPosition, 0, aux);
    closed.push_back(currentPosition);
    // std::cout << cola.ToString();
    cola.EliminaMínimo();
    // std::cout << cola.ToString();
    while (currentPosition->position.second != m_target.second || currentPosition->position.first != m_target.first)
    {
        /* code */
        Step();
        steps++;
    }
    return closed;
}

void AStar::Step()
{
    // TraceLog(LOG_DEBUG,"Desde: Índice: %d X:%d, Y:%d",currentPosition->index
    //     ,currentPosition->position.j,currentPosition->position.i);
    // TraceLog(LOG_DEBUG, "Target: X:%d Y:%d",m_target.j,m_target.i);
    CalcNeightbours();
    for (int i = 0; i < open.size(); i++)
    {
        // TraceLog(LOG_DEBUG, "Indice: %d Posicion: X: %d Y: %d",open[i]->index, open[i]->position.j,open[i]->position);
        float h = Heuristic(open[i]->position);
        int cambio = 0;
        cola.Añadir(open[i], h, cambio);
        if (cambio == 1)
            open[i]->father = currentPosition;
    };
    Node *best = cola.MirarMínimo();
    // TraceLog(LOG_DEBUG, "Mejor: %d", best->index);
    // std::cout << cola.ToString();
    cola.EliminaMínimo();
    closed.push_back(best);
    open = vector<Node *>();
    currentPosition = best;
    WaitTime(0.1);
}

float AStar::Heuristic(Position s)
{
    // The heuristic is the squared distance to the target, multiplied by 10 to make it more significant than the steps taken.
    float result = sqrtf((s.second - m_target.second) * (s.second - m_target.second) + (s.first - m_target.first) * (s.first - m_target.first)) * 10;
    return result + steps;
}


#pragma region Neighbours
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

void AStar::CalcNeightbours()
{
    // if((currentPosition.x > 0 && currentPosition.y > 0 && currentPosition.x < CELL_X-1 && currentPosition.y < CELL_Y-1) &&
    // tabletop[(int)currentPosition.y][(int)currentPosition.x].type != WALL ||
    // tabletop[(int)currentPosition.y][(int)currentPosition.x].type != HARDWALL){
    //     open.push_back(tabletop[(int)currentPosition.y][(int)currentPosition.x]);
    // }
    // O
    //`C
    if ((currentPosition->position.second > 0 && currentPosition->position.first > 0) &&
        (tabletop[currentPosition->position.first - 1][currentPosition->position.second - 1].type != WALL &&
         tabletop[currentPosition->position.first - 1][currentPosition->position.second - 1].type != HARDWALL))
    {
        // TraceLog(LOG_DEBUG,"AnteArriba");
        open.push_back(&tabletop[currentPosition->position.first - 1][currentPosition->position.second - 1]);
    }
    // O
    // ĉ
    if ((currentPosition->position.first > 0) &&
        (tabletop[currentPosition->position.first - 1][currentPosition->position.second].type != WALL &&
         tabletop[currentPosition->position.first - 1][currentPosition->position.second].type != HARDWALL))
    {
        // TraceLog(LOG_DEBUG,"Arriba");
        open.push_back(&tabletop[currentPosition->position.first - 1][currentPosition->position.second]);
    }
    // O
    // Ć
    if ((currentPosition->position.first > 0 && currentPosition->position.second < CELL_Y - 1) &&
        (tabletop[currentPosition->position.first - 1][currentPosition->position.second + 1].type != WALL &&
         tabletop[currentPosition->position.first - 1][currentPosition->position.second + 1].type != HARDWALL))
    {
        // TraceLog(LOG_DEBUG,"PostArriba");
        open.push_back(&tabletop[currentPosition->position.first - 1][currentPosition->position.second + 1]);
    }
    // O < C
    if ((currentPosition->position.second > 0) &&
        (tabletop[currentPosition->position.first][currentPosition->position.second - 1].type != WALL &&
         tabletop[currentPosition->position.first][currentPosition->position.second - 1].type != HARDWALL))
    {
        // TraceLog(LOG_DEBUG,"Anterior");
        open.push_back(&tabletop[currentPosition->position.first][currentPosition->position.second - 1]);
    }
    // C > O
    if ((currentPosition->position.second < CELL_X - 1) &&
        (tabletop[currentPosition->position.first][currentPosition->position.second + 1].type != WALL &&
         tabletop[currentPosition->position.first][currentPosition->position.second + 1].type != HARDWALL))
    {
        // TraceLog(LOG_DEBUG,"Posterior");
        open.push_back(&tabletop[currentPosition->position.first][currentPosition->position.second + 1]);
    }
    // C
    // Ó
    if ((currentPosition->position.second > 0 && currentPosition->position.first < CELL_Y - 1) &&
        (tabletop[currentPosition->position.first + 1][currentPosition->position.second - 1].type != WALL &&
         tabletop[currentPosition->position.first + 1][currentPosition->position.second - 1].type != HARDWALL))
    {
        // TraceLog(LOG_DEBUG,"AnteDebajo");
        open.push_back(&tabletop[currentPosition->position.first + 1][currentPosition->position.second - 1]);
    }
    // C
    // V
    // O
    if ((currentPosition->position.first < CELL_Y - 1) &&
        (tabletop[currentPosition->position.first + 1][currentPosition->position.second].type != WALL &&
         tabletop[currentPosition->position.first + 1][currentPosition->position.second].type != HARDWALL))
    {
        // TraceLog(LOG_DEBUG,"Debajo");
        open.push_back(&tabletop[currentPosition->position.first + 1][currentPosition->position.second]);
    }
    // C
    //  Ò
    if ((currentPosition->position.second < CELL_X - 1 && currentPosition->position.first < CELL_Y - 1) &&
        (tabletop[currentPosition->position.first + 1][currentPosition->position.second + 1].type != WALL &&
         tabletop[currentPosition->position.first + 1][currentPosition->position.second + 1].type != HARDWALL))
    {
        // TraceLog(LOG_DEBUG,"PostDebajo");
        open.push_back(&tabletop[currentPosition->position.first + 1][currentPosition->position.second + 1]);
    }
}

#pragma endregion