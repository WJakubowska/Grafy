#include "list.hh"

using namespace std;

void List::createList()
{   
    
    int edges = graf->n_edges;

    for (int i = 0; i < edges; i++)
    {
        Edge *object=new Edge;

        int vertex_start=graf->getEdge(i)->getVertex1();
        int vertex_end=graf->getEdge(i)->getVertex2();
        int weight=graf->getEdge(i)->getWeight();
    
        object->setVertex1(vertex_start);
        object->setVertex2(vertex_end);
        object->setWeight(weight);

        object->next = list[vertex_start];
        list[vertex_start] = object;

    }
}

void List::displayList()
{
    Edge *ptr;
    int vertices = graf->n_vertices;

    for (int i = 0; i < vertices; i++)
    {
        cout << i <<":";
        ptr = list[i];
        while(ptr!=NULL){
            cout << setw(3) << ptr->getVertex2();
            ptr = ptr->next;
        }
        cout << endl;
    }
}

bool List::BellmanFord()
{
    bool information;
    int vertices=graf->n_vertices;

    for (int i = 0; i < vertices; i++) {   // 
        cost_l[i] = infinity;  //tablice kosztow wypelniamy nieskonczonoscia
        street_l[i] = -1;     // wypelnienie tablicy -1
    }

    cost_l[graf->first_vertex] = 0; // wierzcholek poczatkowy jako koszt 0;

    for (int i=1; i<vertices; i++)
    {
        information = true;
        for (int  j=0; j<vertices; j++) {
           Edge  *object=list[j];
             while(object != nullptr){
                if (cost_l[object->getVertex2()] > cost_l[j]+object->getWeight()) {
                    information = false;
                    cost_l[object->getVertex2()]=cost_l[j]+object->getWeight();
                    street_l[object->getVertex2()]=j;
                }
                 object = object->next;
            }
          }
        

        if (information == true) return true;
    }

    return true;
}

void List::displayBF()
{
    int vertices=graf->n_vertices;
    int tmp=0;
    int *tab = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        cout << i << ":";
        for (int j= i; j!=-1; j=street_l[j]) 
                 tab[tmp++] = j;

        while (tmp){
            cout << tab[--tmp] << "  ";
        }
        cout  << " koszt : " << cost_l[i] << endl;
    }
    delete[] tab;
}

void List::saveScoreBF(string filename)
{
    ofstream file;
    file.open(filename);
    int vertices=graf->n_vertices;
    int tmp=0;
    int *tab = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        file << i << ":";
        for (int j= i; j!=-1; j=street_l[j]) 
                 tab[tmp++] = j;

        while (tmp){
            file << tab[--tmp] << "  ";
        }
        file << " koszt : " << cost_l[i] << endl;
    }
    delete[] tab;
 
    file.close();
}

