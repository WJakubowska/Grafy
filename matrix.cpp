#include "matrix.hh"

using namespace std;

void Matrix::createMatrix()
{
    int vertices = graf->n_vertices;
    int edges =graf->n_edges;
    
    for (int i = 0; i < vertices;i++) {
        for (int j = 0; j < vertices; j++) {
            Edge elem;
            elem.setVertex1(0);
            elem.setVertex2(0);
            elem.setWeight(0);
            matrix[i][j]=elem; 
        }
    }

    for (int i = 0; i < edges;i++)
    {
        int vertex_start=graf->getEdge(i)->getVertex1();
        int vertex_end=graf->getEdge(i)->getVertex2();

        matrix[vertex_start][vertex_end]=(*graf->getEdge(i)); 
    }

}

void Matrix::displayMatrix()
{
    int vertices = graf->n_vertices;

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices;j++){
            cout << "    " << matrix[i][j].getWeight();
        }
        cout <<endl;
    }
}

bool Matrix::BellmanFord()
{
    bool information;
    int vertices = graf->n_vertices;


    for (int i = 0; i < vertices; i++) {
        cost_m[i] = infinity;    //tablice kosztow wypelniamy nieskonczonoscia
        street_m[i] = -1;  //wypelnienie tabic wartoscia -1
    }

    cost_m[graf->first_vertex] = 0; // wierzcholek poczatkowy jako koszt 0;

    for (int i = 1; i < vertices;i++)
    {
        information = true;
        for (int j=0; j<vertices; j++) {
            for (int k=0; k<vertices; k++) {
                Edge elem=matrix[j][k];
                if (elem.getVertex2()!= 0) {
                    if (cost_m[elem.getVertex2()] > cost_m[j] + elem.getWeight())
                    {
                        information = false;
                        cost_m[elem.getVertex2()] = cost_m[j] + elem.getWeight();
                        street_m[elem.getVertex2()] = j;
                    }
                }
            }
        }
        if (information == true) return true;
    }

    return true;
}

void Matrix::displayBF()
{
    int vertices=graf->n_vertices;
    int tmp=0;
    int *tab = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        cout << i << ":";
        for (int j= i; j!=-1; j=street_m[j]) 
                 tab[tmp++] = j;

        while (tmp){
            cout << tab[--tmp] << "  ";
        }
        cout << " koszt : " << cost_m[i] << endl;
    }
    delete[] tab;
}

void Matrix::saveScoreBF(string filename)
{
    ofstream file;
    file.open(filename);
    int vertices=graf->n_vertices;
    int tmp=0;
    int *tab = new int[vertices];

    for (int i = 0; i < vertices; i++)
    {
        file << i << ":";
        for (int j= i; j!=-1; j=street_m[j]) 
                 tab[tmp++] = j;

        while (tmp){
            file << tab[--tmp] << "  ";
        }
        file << " koszt : " << cost_m[i] << endl;
    }
    delete[] tab;
 
    file.close();
}

