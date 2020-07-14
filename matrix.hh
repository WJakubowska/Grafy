#pragma once

#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>

#include "graf.hh"

/*****************************************************************************************************/
/*                         MACIERZ SASIEDZTWA                                                       */
/***************************************************************************************************/

class Matrix {
public:
    std::shared_ptr<Graf> graf; //graf
    Edge **matrix; // macierz sasiedztwa
    int *cost_m;  //tablica kosztow
    int *street_m; //tablica drogi dojscia do wierzcholka

    Matrix(std::shared_ptr<Graf> elem){ 
        graf=elem;
        int vertices =graf->n_vertices;
        matrix = new Edge *[vertices]; 
        for (int i=0; i<vertices; i++){
            matrix[i] = new Edge[vertices]; 
        }
     
        cost_m = new int[vertices]; 
        street_m = new int[vertices];

    }
    ~Matrix(){
        int vertices =graf->n_vertices;
        for (int i = 0; i < vertices;i++){
            delete [] matrix[i];
        }
        delete [] matrix;

        delete [] cost_m;
        delete [] street_m;
    }


    /*  METODY TWORZACE MACIERZ SASIEDZTWA                                 */

    void createMatrix(); // tworzy macierz
    void displayMatrix(); // wyswietla macierz  

    /*  ALGORYTM BELLMANA-FORDA                                          */

    bool BellmanFord();  // wykonanie algorytmu 
    void displayBF();  //wyswietla wynik algorytmu
    void saveScoreBF(std::string filename); //zapisuje wynik algorytmu do pliku 
    
};