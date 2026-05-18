#pragma once
#include <vector>
#include <string>
#include "CommonInfo.hpp"

using namespace std;

#define jump 10


struct QueueModel{
    //Where float is the weight of the element in the heap
    //Where int is the position in the positions array
    vector<pair<int,float>> heap;
    //Each position of this array represents an element, and the value is the index in the heap where it is located.
    //If the value is -1, it means that the element is not in the heap.
    //For example, if we want to know the position of element 5 in the heap, we look at positions[5],
    //and it gives us the index in the monticulo where it is located.
    vector<int> positions;
    QueueModel(int max);

    //Small debug methods
    string ToString();
    vector<string> SplitString();
};


class ColaCasillas{
protected:
    QueueModel heart;
    int last;
public:
    ColaCasillas(int max);
    //Weight will determine the position of the element in the heap
    //Elem is the value of the element
    void Add(int elem, float weight); //log(n)
    void Delete(int elem);
    void Change(int ind, float w);
    int SeekMinimum();
    void DeleteMinimum();
    QueueModel* ReturnCurrent() {return &heart;}
    void Resset() { last = 1; heart = QueueModel(heart.heap.size()); };
    string ToString();
protected:
    void Enlarge();
    int Float(int i);
    int Sink(int i);
};