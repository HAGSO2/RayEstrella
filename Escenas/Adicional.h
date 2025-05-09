#pragma once
#include <string>

enum CellType{
    DEFAULT = 0,
	WAY = 1,
	UNUSED_WAY = 2,
	HARDWALL = 3,
	WALL = 4,
	ENTRANCE = 5,
	EXIT = 6
};

struct Node{
    CellType type;
    int index;
    float F;
    int G;
    public:
    Node();
};

// struct TextBoxParams{
//     std::string& texto;
//     bool& enter;
//     bool& selected;
//     TextBoxParams(std::string& ref);
// };