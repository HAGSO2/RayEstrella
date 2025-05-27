#include "../Escenas/Adicional.h"
#include <raylib.h>
struct NodePos{
        int index;
        Vector2 pos;
        NodePos* father;
        NodePos(Vector2 position, NodePos* f);
    };

NodePos::NodePos(Vector2 position, NodePos* f): pos{position}, index{(int)(position.y*CELL_X+position.x)}, father{f}{};