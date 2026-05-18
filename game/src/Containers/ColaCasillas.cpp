#include "Containers/ColaCasillas.h"
#include <raylib.h>

#pragma region Model

QueueModel::QueueModel(int max) : heap{vector<pair<int, float>>(jump)},
                                  positions{vector<int>(max + 1, -1)} {};

string QueueModel::ToString()
{
    string message;
    for (int i = 0; i < heap.size(); i++)
    {
        pair<int, float> elem = heap[i];
        message.push_back('[');
        message.append(to_string(elem.first));
        message.push_back('|');
        message.append(to_string(elem.second));
        message.push_back(']');
    }
    return message;
}

vector<string> QueueModel::SplitString()
{
    vector<string> message;
    for (int i = 1; i < heap.size(); i++)
    {
        char c = (char)(heap[i].first + 65);
        string aux = "[";
        aux.push_back(c);
        message.push_back(aux + "|" + to_string(heap[i].second) + "]");
    }
    return message;
}
#pragma endregion

#pragma region Public Queue Methods
ColaCasillas::ColaCasillas(int max) : last{1},
                                      heart{QueueModel(max)}
{};

void ColaCasillas::Add(int elem, float weight)
{
    if ((int)heart.heap.size() == last + 1)
        Enlarge();

    //Is the element already in the heap?
    if (heart.positions[elem] == -1)
    {
        heart.heap[last] = pair<int, float>(elem, weight);
        heart.positions[elem] = Float(last);
        last++;
    }
    //Is the element already in the heap but with a higher weight?
    else if (heart.heap[heart.positions[elem]].second > weight)
    {
        Change(elem, weight);
    };
};

void ColaCasillas::Enlarge()
{
    vector<pair<int, float>> aux = vector<pair<int, float>>(heart.heap.size() + jump);
    for (int i = 0; i < (int)heart.heap.size(); i++)
    {
        aux[i] = heart.heap[i];
    }
    heart.heap = aux;
};

void ColaCasillas::Delete(int elem)
{
    //Is it posible for the array to contain the element?
    if (heart.positions.size() < elem)
        return;
    int index = heart.positions[(int)elem];
    if (index == -1) // The element was not in the heap
        return;
    heart.positions[(int)elem] = -1;
    last--;
    //Replace the element with the last one and sink it down
    heart.heap[index] = heart.heap[last];
    int otherpos = heart.heap[index].first;
    //Set to zero the last element, just for debugging purposes
    heart.heap[last] = pair<int, float>(0, 0);
    int pos = Sink(index);
    heart.positions[otherpos] = pos;
};

void ColaCasillas::Change(int elem, float weight)
{
    if (heart.positions.size() < elem)
        return;
    int index = heart.positions[(int)elem];
    if (index == -1) // The element was not in the heap
        return;
    //Get the old wight and compare
    float old = heart.heap[index].second;
    heart.heap[index].second = weight;
    if (weight < old)
    {
        heart.positions[elem] = Float(index);
    }
    else
    {
        //Just to add the posibility but it should not be used
        // in the A* algorithm, since we only change the weight to a lower one
        heart.positions[elem] = Sink(index);
    }
};
int ColaCasillas::SeekMinimum() { return heart.heap[1].first; };
void ColaCasillas::DeleteMinimum() { Delete(1); };

string ColaCasillas::ToString()
{
    string queue = "Heap: \n";
    for (int i = 1; i < heart.heap.size(); i++)
    {
        queue.append(to_string(heart.heap[i].first) + "|" + to_string(heart.heap[i].second) + "\n");
    }
    queue.append("\nPositions: \n");
    for (int i = 0; i < heart.positions.size(); i++)
    {
        queue.append(to_string(i) + "|" + to_string(heart.positions[i]) + "\n");
    }
    return queue;
}
#pragma endregion
#pragma region Private Queue Methods
int ColaCasillas::Sink(int i)
{
    //Is the element in the last position?
    if (i == last)
    {
        return i;
    }
    //Does it have children?
    else if ((i * 2) < last)
    {
        //Get the smallest child
        int child = i * 2;
        if (child + 1 < last && heart.heap[child].second > heart.heap[child + 1].second)
            child++;
        //Is the child smaller than the element?
        if (heart.heap[child].second < heart.heap[i].second)
        {
            /*
             * Replace the element with the smallest child and sink it down
             * <A,32> -> (<C,2>|<V,4>) ==>
             *   <C,2> -> (<A,32|<V,4>)
             */
            heart.positions[heart.heap[child].first] = i;
            pair<int, float> aux = heart.heap[child];
            heart.heap[child] = heart.heap[i];
            heart.heap[i] = aux;
            return Sink(child);
        }

    } 
    //Did the sink operation go too far?
    else if (i > last)
    {
        return i / 2;
    }
    //If no operation was done, return the current position
    return i;
};

int ColaCasillas::Float(int i)
{
    int father = i / 2;
    //Is the current position the root?
    if (i == 1)
    {
        return 1;
    }
    //Is the father bigger than the element?
    else if (heart.heap[father].second > heart.heap[i].second)
    {
        heart.positions[heart.heap[father].first] = i;
        pair<int, float> aux = heart.heap[father];
        heart.heap[father] = heart.heap[i];
        heart.heap[i] = aux;
        return Float(father);
    }
    //If no operation was done, return the current position
    else
    {
        return i;
    }
};
#pragma endregion