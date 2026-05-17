#pragma once
#include <string>
#include <raylib.h>

#define CELL_X 10
#define CELL_Y 6

enum CellType{
    DEFAULT = 0,
	WAY = 1,
	UNUSED_WAY = 2,
	HARDWALL = 3,
	WALL = 4,
	ENTRANCE = 5,
	EXIT = 6
};

typedef std::pair<int,int> Position;

struct Node{
    CellType type;
    Position position;
    int index;
    float F;
    int G;
    Node* father;
    public:
    Node();
};