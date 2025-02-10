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
    bool visited;
    int index;
    float weight;
    public:
    Node();
};
//Implementación en gameplay cpp