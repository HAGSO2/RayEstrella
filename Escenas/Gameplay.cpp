#include "Gameplay.h"

void ACero(void* ptr){
    Gameplay* objeto = (Gameplay*)ptr;
    objeto->TodoACero();
}

void Busqueda(void* ptr){
    Gameplay* objeto = (Gameplay*)ptr;
    objeto->EmpiezaBusqueda();
}

Gameplay::Gameplay() : nodes{}, Scene(), estrella{nodes}
{
    for(int i = 0, z = 1; i < CELL_Y; i++){
        for(int j = 0; j < CELL_X; j++){
            nodes[i][j].position = Position2{i,j};
            nodes[i][j].index = z;
            //TraceLog(LOG_DEBUG, "Index: %d",z);
            cells[i][j] = new Sprite(Vector2{WORLD_X_OFFSET+j*CELL_SIZE,WORLD_X_OFFSET+i*CELL_SIZE},Vector2{CELL_VISUAL,CELL_VISUAL}, BLUE);
            if(i == 0 || j == 0 || i == CELL_Y-1 || j == CELL_X-1){
                nodes[i][j].type = HARDWALL;
                cells[i][j]->ChangeColor(RED);
            }
            z++;
        }
    }
    canvas.AddButton(0,0,100,30,"Todo a cero",ORANGE,ACero,this);
    canvas.AddButton(0,30,100,30,"Empieza la búsqueda",GREEN,Busqueda,this);
    //"Paso"
};

void Gameplay::InitScene()
{
    nodes[ENTRANCE_Y][ENTRANCE_X].type = ENTRANCE;
    cells[ENTRANCE_Y][ENTRANCE_X]->ChangeColor(ENTRANCE_COLOR);

    nodes[END_Y][END_X].type = EXIT;
    cells[END_Y][END_X]->ChangeColor(END_COLOR);    

};

void Gameplay::TodoACero(){
    for(int i = 0,z = 0; i < CELL_Y; i++){
        for(int j = 0; j < CELL_X; j++){
            if(!(i == 0 || j == 0 || i == CELL_Y-1 || j == CELL_X-1)){
                cells[i][j]->ChangeColor(BLUE);
            }
            z++;
        }
    }

    nodes[ENTRANCE_Y][ENTRANCE_X].type = ENTRANCE;
    cells[ENTRANCE_Y][ENTRANCE_X]->ChangeColor(ENTRANCE_COLOR);

    nodes[END_Y][END_X].type = EXIT;
    cells[END_Y][END_X]->ChangeColor(END_COLOR);
}

void Gameplay::EmpiezaBusqueda(){
    TraceLog(LOG_ALL,"Empezando busqueda");
    vector<Node *> path = estrella.Pathfinding(Position2{ENTRANCE_Y,ENTRANCE_X},Position2{END_Y,END_X});

    for(int i = 0; i < path.size(); i++){
        TraceLog(LOG_ALL,"X: %d, Y: %d Father: X:%d, Y:%d",path[i]->position.j,path[i]->position.i,
        path[i]->father->position.j,path[i]->father->position.i);
        cells[path[i]->position.i][path[i]->position.j]->ChangeColor(BROWN);
    }
    // for(Node* actual = path.back(); actual != nullptr; actual = actual->father ){
    //     TraceLog(LOG_ALL,"X: %d, Y: %d",actual->position.j,actual->position.i);
    //     cells[actual->position.i][actual->position.j]->ChangeColor(BROWN);
    // }
}

void Gameplay::UpdateScreen(){
    Scene::UpdateScreen();
}

void Gameplay::OnMouseDown(){
    int i = (mousePosition.y-WORLD_Y_OFFSET);
    int j = (mousePosition.x-WORLD_X_OFFSET);
    if(i > 0 && j > 0){
        i = i / CELL_SIZE;
        j = j / CELL_SIZE;
        TraceLog(LOG_DEBUG,"X:%d Y:%d",j,i);
        if(i >= 0 && i < CELL_Y && j >= 0 && j < CELL_X)
        TraceLog(LOG_DEBUG, "Dentro");

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
            WaitTime(0.1f);
        }
    }
    
    canvas.UpdateScreen(mousePosition);
}

void Gameplay::DrawScreen()
{
    canvas.Draw();

    for(int i = 0; i < CELL_Y; i++){
        for(int j = 0; j < CELL_X; j++){
            cells[i][j]->DrawObject();
            DrawText(to_string(nodes[i][j].index).c_str(),
            j*CELL_SIZE+WORLD_X_OFFSET,i*CELL_SIZE+WORLD_X_OFFSET,
            12,BLACK);
        }
    }
};

void Gameplay::OnKeyPressed(KeyboardKey k){
    if(k == KEY_BACKSPACE){
        finishScreen = TITTLE;
    }
}

