#include "Gameplay.h"

Node::Node(): type{DEFAULT}, visited{false}, weight{0}{};

Gameplay::Gameplay() : nodes{}
{
    for(int i = 0; i < CELL_Y; i++){
        for(int j = 0; j < CELL_X; j++){
            cells[i][j] = new Sprite(Vector2{WORLD_X_OFFSET+j*CELL_SIZE,WORLD_X_OFFSET+i*CELL_SIZE},Vector2{CELL_VISUAL,CELL_VISUAL}, BLUE);
        }
    }
    canvas = UI<Gameplay>();
};

void Gameplay::InitScene()
{
    for(int i = 0; i < CELL_Y; i++){
        for(int j = 0; j < CELL_X; j++){
            if(i == 0 || j == 0 || i == CELL_Y-1 || j == CELL_X-1){
                nodes[i][j].type = HARDWALL;
                cells[i][j]->ChangeColor(RED);
            }
        }
    }

    nodes[ENTRANCE_Y][ENTRANCE_X].type = ENTRANCE;
    nodes[ENTRANCE_Y][ENTRANCE_X].visited = true;
    cells[ENTRANCE_Y][ENTRANCE_X]->ChangeColor(ENTRANCE_COLOR);

    nodes[END_Y][END_X].type = EXIT;
    cells[END_Y][END_X]->ChangeColor(END_COLOR);    

    // canvas.AddButton(0, 0, 100, 30, "Resset", ORANGE);
    // canvas.AddButton(100, 0, 100, 30, "Empezar", GREEN);
};

void Gameplay::UpdateScreen(){
    Scene::UpdateScreen();
    canvas.Update(mousePosition);
    //Depende dónde haya tocado el ratón
    //hay que actualizar un sprite si es
    //posible por el tipo de nodo, y por
    //si no se ha comenzado a buscar
}

void Gameplay::OnMouseDown(){
    int i = (mousePosition.y-WORLD_Y_OFFSET) / CELL_SIZE;
    int j = (mousePosition.x-WORLD_X_OFFSET) / CELL_SIZE;
    TraceLog(LOG_DEBUG,"X:%d Y:%d",j,i);

    if(i >= 0 && i < CELL_Y && j >= 0 && j < CELL_X){
        TraceLog(LOG_DEBUG,"DENTRO");
        if(nodes[i][j].type == DEFAULT){
            nodes[i][j].type = WALL;
            cells[i][j]->ChangeColor(RED);
        }
        else if(nodes[i][j].type == WALL){
            nodes[i][j].type = DEFAULT;
            cells[i][j]->ChangeColor(BLUE);
        }
        
    }
    WaitTime(0.1f);
}

void Gameplay::DrawScreen()
{
    // canvas.Draw();

    for(int i = 0; i < CELL_Y; i++){
        for(int j = 0; j < CELL_X; j++){
            cells[i][j]->DrawObject();
        }
    }
};

void Gameplay::OnKeyPressed(KeyboardKey k){
    if(k == KEY_BACKSPACE){
        finishScreen = TITTLE;
    }
}

