#include "Scenes/Gameplay.hpp"

void ToZero(void *ptr)
{
    Gameplay *objeto = (Gameplay *)ptr;
    objeto->AllZero();
}

void Busqueda(void *ptr)
{
    Gameplay *objeto = (Gameplay *)ptr;
    objeto->RessearchStart();
}

void Gameplay::AllZero()
{
    // Set all the nodes to default and all the sprites to blue, except the borders that are hardwalls and the entrance and exit.
    for (int i = 0, z = 0; i < CELL_Y; i++)
    {
        for (int j = 0; j < CELL_X; j++)
        {
            if (i != 0 && j != 0 && i != CELL_Y - 1 && j != CELL_X - 1)
            {
                nodes[i][j].type = DEFAULT;
                cells[i][j]->ChangeColor(BLUE);
            }
            z++;
        }
    }

    nodes[ENTRANCE_Y][ENTRANCE_X].type = ENTRANCE;
    cells[ENTRANCE_Y][ENTRANCE_X]->ChangeColor(ENTRANCE_COLOR);

    nodes[END_Y][END_X].type = EXIT;
    cells[END_Y][END_X]->ChangeColor(END_COLOR);
    estrella.Resset();
}

void Gameplay::RessearchStart()
{
    // Vector of final path aquired with A*
    vector<Node *> path = estrella.Pathfinding(Position{ENTRANCE_Y, ENTRANCE_X}, Position{END_Y, END_X});

    // Translate the path to the sprites on the screen
    // for (int i = 0; i < path.size(); i++)
    // {
    //     if(path[i]->father != nullptr)
    //         TraceLog(LOG_ALL,"X: %d, Y: %d Father: X:%d, Y:%d",path[i]->position.second,path[i]->position.first,
    //         path[i]->father->position.second,path[i]->father->position.first);
    //     cells[path[i]->position.first][path[i]->position.second]->ChangeColor(BROWN);
    // }
    for(Node* actual = path.back(); actual != nullptr && actual != &nodes[ENTRANCE_Y][ENTRANCE_X]; actual = actual->father ){
        TraceLog(LOG_ALL,"X: %d, Y: %d",actual->position.second,actual->position.first);
        cells[actual->position.first][actual->position.second]->ChangeColor(BROWN);
    }
}

// Pass by reference the array of nodes
Gameplay::Gameplay() : Scene(), estrella{nodes}
{
    for (int i = 0, z = 1; i < CELL_Y; i++)
    {
        for (int j = 0; j < CELL_X; j++)
        {
            nodes[i][j] = Node();
            nodes[i][j].position = Position{i, j};
            nodes[i][j].index = z;
            cells[i][j] = new Sprite(Vector2{WORLD_X_OFFSET + j * CELL_SIZE, WORLD_X_OFFSET + i * CELL_SIZE}, Vector2{CELL_VISUAL, CELL_VISUAL}, BLUE);
            // Are this node from the border? If so, make it a hardwall
            if (i == 0 || j == 0 || i == CELL_Y - 1 || j == CELL_X - 1)
            {
                nodes[i][j].type = HARDWALL;
                cells[i][j]->ChangeColor(RED);
            }
            z++;
        }
    }
    canvas.AddButton(0, 0, 100, 30, RessetButtonText, RessetButtonColor, ToZero, this);
    canvas.AddButton(0, 30, 100, 30, ResearchButtonText, ResearchButtonColor, Busqueda, this);
};

void Gameplay::InitScene() { AllZero(); };

void Gameplay::UpdateScreen()
{
    // Update base scene logic (e.g., handle input, update UI, etc.)
    Scene::UpdateScreen();
}

void Gameplay::DrawScreen()
{
    // Draw the title screen elements here (e.g., background, title text, buttons, etc.)
    canvas.Draw();

    for (int i = 0; i < CELL_Y; i++)
    {
        for (int j = 0; j < CELL_X; j++)
        {
            cells[i][j]->DrawObject();
            DrawText(to_string(nodes[i][j].index).c_str(),
                     j * CELL_SIZE + WORLD_X_OFFSET,
                     i * CELL_SIZE + WORLD_X_OFFSET,
                     12, BLACK);
        }
    }
};

void Gameplay::OnMouseDown()
{
    int i = (mousePosition.y - WORLD_Y_OFFSET);
    int j = (mousePosition.x - WORLD_X_OFFSET);
    if (i > 0 && j > 0)
    {
        i = i / CELL_SIZE;
        j = j / CELL_SIZE;
        TraceLog(LOG_DEBUG, "X:%d Y:%d", j, i);

        if (i >= 0 && i < CELL_Y && j >= 0 && j < CELL_X)
        {
            TraceLog(LOG_DEBUG, "Inside");
            if (nodes[i][j].type == DEFAULT)
            {
                nodes[i][j].type = WALL;
                cells[i][j]->ChangeColor(RED);
            }
            else if (nodes[i][j].type == WALL)
            {
                nodes[i][j].type = DEFAULT;
                cells[i][j]->ChangeColor(BLUE);
            }
            // For not changing the node tree times a click,
            // wait a little bit after changing the color
            WaitTime(0.1f);
        }
    }

    canvas.UpdateScreen(mousePosition);
}

void Gameplay::OnKeyPressed(KeyboardKey k)
{
    if (k == KEY_BACKSPACE)
    {
        finishScreen = TITTLE;
    }
}
