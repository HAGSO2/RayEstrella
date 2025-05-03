#pragma once
#include "Adicional.h"
#include "../Motor/Scene.h"
#include "../Abstractos/ColaCasillas.h"
#include "../Motor/GameObject.h"

#define CASILLAS 27 
//El tamaño de la cola debe ser tan grande como posibilidades de elementos puede tener.
//Es decir que si en la cola voy a meter letras, la cola debe ser tan grande para meterlas a todas.
class EsDecrementable : public Scene{
    const char minimoLetra = 'A';
    string fixedText[3] = {"Insertar elemento", "Cambiar elemento", "Eliminar elemento"};
    string alltext[5] = {"","","","",""};
    ColaCasillas cola;
    TextShape* casillas[CASILLAS];
    int active;
    int velocidad = 1;

    bool selected;
    public:
    EsDecrementable();
    void InitScene() {finishScreen = UNKNOWN;};
	void UpdateScreen() override;
	void DrawScreen();
	void UnloadScreen() {};
    void OnMouseDown();
    void OnKeyPressed(KeyboardKey);

    // int ReturnInt(){return 1;};

    // //El los parámetros de estos métodos se encuentran en el array de alltext
    // //por lo que no es necesario que tengan parámetros al llamarlos.
    void InsertaElemento();
    void CambiaElemento();
    void EliminaElemento();

    //Cada modelo cola, es un paso que deben seguir los actores

    void ActualizaActores();

    string DevuelveCola() {return cola.ToString();}

    void RessetText();

    private:
    void InsertaElemento(const char* nombre, int prio);
    void CambiaElemento(const char* nombre, int prio);
    void EliminaElemento(const char* nombre);

    void FijaNumeroActores();
    void FijaTextoActores(vector<string>);
    
    void CambiaVelocidad(int vel) {velocidad = vel;}

};
