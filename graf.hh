#pragma once

#include <cstdlib>
#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <memory>

#include "vector.hh"

const int weight_range= 40; // zakres liczb w jakim sa losowane wagi krawedzi
const int infinity = 2147483647; // oznaczenie nieskonczonosci dla algorytmu Bellmana-Forda
const int FLAG=-10; // flaga gdy krawedz nie istnieje
const int EXIST=10; //flaga gdy krawedz istnieje

/******************************************************************************************************/
/*                                              KRAWEDZIE                                            */
/****************************************************************************************************/
class Edge{
private:
    int vertex1; //wierzcholek poczatkowy
    int vertex2; //wierzcholek koncowy
    int weight; // waga krawedz
public:
    Edge *next;

    int getVertex1(){ return vertex1; } //zwraca wierzcholek poczatkowy
    int getVertex2(){ return vertex2; } //zwraca wierzcholek koncowy
    int getWeight(){  return weight;  } //zwraca wage krawedzi
    void setRandWeight(){ weight=rand()%weight_range;} // ustawia randomowa wage krawedzi 
    void setRandVertex1(int vertices){ vertex1=rand()%vertices;} //ustawia randomowy wierzcholek pierwszy
    void setRandVertex2(int vertices){ vertex2=rand()%vertices;} // ustawia randomowy wierzcholek drugi
    void setVertex1(int value) {vertex1=value;} //ustawia konkretna wartosc wierzcholka poczatkowego
    void setVertex2(int value) {vertex2=value;} //ustawia konkretna wartosc wierzcholka koncowego
    void setWeight(int value) {weight=value;}  //ustawia konkretna wartosc wagi krawedzi
    
    bool operator==(const Edge &edge){
        if(this->vertex1==edge.vertex1 && this->vertex2==edge.vertex2){
            return true;
        }
        else{
            return false;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& out, const Edge & edge){
            out <<edge.vertex1 <<"  "<<edge.vertex2<<"   "<<edge.weight<<"   "<<std::endl;
        return out;
    }

    Edge(int first_v, int end_v, int weight_edge){
        vertex1=first_v; 
        vertex2=end_v;
        weight=weight_edge;
        next=nullptr;
    }
    Edge(const Edge & edge){
        vertex1=edge.vertex1;
        vertex2=edge.vertex2;
        weight=edge.weight;
        next=edge.next;
    }
    Edge(){vertex1=0; vertex2=0; weight=0; next=nullptr;}
    ~Edge(){ delete next;}
};


/*****************************************************************************************************/
/*                         GRAF                                                                     */
/***************************************************************************************************/
class Graf{
public:    
    int first_vertex; // wierzcholek startowy
    int n_vertices;  // liczba wierzcholkow
    int n_edges;    //liczba krawedzi
    vector<std::shared_ptr<Edge>> list_edge;  //lista krawedzi 
    

    Graf(){}; 
    ~Graf(){};
    
    std::shared_ptr<Edge> getEdge(int i) {return list_edge[i];}

    void makeGraf(int vertices,int edges,double density); // funkcja generujaca graf w pamieci RAM
    void readFile(std::string filename); // funkcja odczytujaca graf z pliku
    void saveFile(std::string filename,int vertices,int edges,double density); //dunkcja generujaca graf i zapisujaca go do pliku

};