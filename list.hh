#pragma once

#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>

#include "graf.hh"

/*****************************************************************************************************/
/*                         LISTA SASIEDZTWA                                                         */
/***************************************************************************************************/

class List{
public:
    std::shared_ptr<Graf> graf; //graf 
    Edge **list; //lista sasiedztwa
    int *cost_l; //tablica kosztow
    int *street_l; //tablica drogi dojscia do wierzcholka

    List(std::shared_ptr<Graf> elem){ 
        graf=elem;
        int vertices =graf->n_vertices;
        list = new Edge *[vertices]; 
            for (int i=0; i<vertices; i++){
                list[i] = nullptr; 
            }
       
        cost_l = new int[vertices]; 
        street_l = new int[vertices];

    }
    ~List(){
        int vertices =graf->n_vertices;

        for (int i=0; i<vertices; i++){
            delete list[i];    
        }
         delete [] list;

         delete [] cost_l;
         delete [] street_l;
    }

    /*  METODY TWORZACE LISTE SASIEDZTWA                                   */

    void createList(); // tworzy liste sasiedztwa
    void displayList(); // wyswietla liste sasiedztwa

    /*  ALGORYTM BELLMANA-FORDA                                          */

    bool BellmanFord(); //realizuje algorytm Bellmana-Forda
    void displayBF(); //wyswietla wynik algorytmu
    void saveScoreBF(std::string filename); //zapisuje wynik algorytmu do pliku 

};