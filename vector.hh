#include <iostream>
#include <time.h>
#include <cmath>
#include <stddef.h>
#include <memory>
 
/*****************************************************************************************************/
/*                         VECTOR                                                                   */
/***************************************************************************************************/

template<class type> 
class vector{  
      type *tab_vector; //tablica przechowujaca vector 
      int max_size; //maksymalny rozmiar tablicy 
      int actual_size; // aktualny rozmiar tablicy 
public :  
    vector(){ tab_vector = new type [1]; max_size = 1; actual_size = 0; } 
    ~vector(){delete [] tab_vector; }
    type & operator[](int index ) {return tab_vector[index];}
    friend std::ostream& operator<<(std::ostream& out, const vector<type>& v){
        for(int i=0; i<v.actual_size; i++){
            out <<v.tab_vector[i] << std::endl;
        }
        return out;
    }
    void push(type value) //wstawianie elementu  
    { 
        if(actual_size==max_size) { //jesli dojdzie do aktualnego rozmiaru to powieksz tablice dwukrotnie 
            type *tmp = new type [2*max_size]; 
  
              for(int i=0; i<max_size; i++) { //przepisanie elementow z starej tablicy do nowej
                 tmp[i] = tab_vector[i]; 
               } 
 
            delete [] tab_vector; 
            max_size=max_size*2; 
            tab_vector = tmp; 
        } 

        tab_vector[actual_size] = value; // rozmiar ok to wstaw dane 
        actual_size++; 
     } 
 
    void push(type value, int index) //wstawianie elementu w wyzanczone miejsce 
    {    
        if(index==max_size) // wstawianie jako ostatni element
            push(value); 
        else 
            tab_vector[index]=value; 
    } 
    int getElem( int index){ return tab_vector[index]; }  
    void pop(){  actual_size--; } 
    int size(){ return actual_size; } 
    int getMaxSize(){ return max_size; } 
    void display() 
    { 
        for(int i=0; i<actual_size; i++){ 
            std::cout << tab_vector[i] << "   "; 
        } 
        std::cout << std::endl; 
    }
    bool check(type elem) // zwraca true gdy element juz wystapi
    {
        for(int i=0; i<actual_size; i++){
            if(tab_vector[i]==elem) return true;
        }
        return false;
    } 
 }; 
