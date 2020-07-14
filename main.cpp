#include <iostream>
#include <time.h>
#include <cmath>

#include "matrix.hh"
#include "list.hh"

using namespace std;

clock_t start,stop,start1,stop1;
double time1,time2,time_l=0,time_m=0;


int main()
{

  srand(time(NULL));
  
  int n_vertices;
  double density;
  ofstream file;
  char choice;

cout <<" PROGRAM GRAFY DLA ALGORYTMU BELLMANA-FORDA"<<endl;
cout <<"a - uruchom wersje programu dla testu efektywnosci grafu (wynik zapisuje sie w pliku) "<<endl;
cout <<"b - utworzenie listy i macierzy sasiedzta poprzez zapis grafu w pliku i odczytania grafu z tego pliku, oraz wywolanie dla nich algorytmu Bellmana-Forda wraz z zapisem do pliku" <<endl;
cout <<"WPISZ LITERE ODPOWIADAJACA CZYNNOSCI KTORA CHCESZ ZROBIC:  ";
cin >> choice;
switch(choice)
{
case 'a':
  cout <<" wykonuje testy ... wyniki zapisuje w pliku " <<endl;
  file.open("test.dat");
  for(int i=0; i<5; i++){
    int vertex[5]={10,50,100,500,1000};
    double d[4]={0.25,0.5,0.75,1};
    n_vertices=vertex[i];
    for(int j=0; j<4;j++){
        density=d[j];
         int  n_edge=0.5*density*n_vertices*(n_vertices-1);
          for(int k=0; k<100; k++){
              shared_ptr<Graf> graf=make_shared<Graf>();

              graf->makeGraf(n_vertices,n_edge,density);
                
              Matrix matrix(graf);
              matrix.createMatrix();
           //   matrix.displayMatrix();
              start=clock();
              matrix.BellmanFord();
              stop=clock();
              time1=(double)(stop-start)/CLOCKS_PER_SEC; 
              time_m=time_m+time1;
              start=0;
              stop=0;
              time1=0;

                
              List list(graf);
              list.createList();
            //  list.displayList();
              start1=clock();          
              list.BellmanFord();
              stop1=clock();
              time2=(double)(stop1-start1)/CLOCKS_PER_SEC;
              time_l=time_l+time2;
              start1=0;
              stop1=0;
              time2=0; 
          
          }
          double time_m_100=time_m/100;
          double time_l_100=time_l/100;

         file << "macierz sasiedztwa  liczba wierzcholkow : " << n_vertices << " gestosc: " << density << " czas: " << time_m_100 << " s" <<endl;
         file << "lista sasiedztwa  liczba wierzcholkow : " << n_vertices << " gestosc: " << density << " czas: " << time_l_100 << " s" <<endl;
  

          time_m_100=0;
          time_l_100=0;
    }
  }
  file.close();
  break;
case 'b':
    cout << "Graf tworze i zapisuje do pliku graf.txt. Efekt algorytmu Bellmana-Forda dla listy zapisuje sie w pliku result_list.txt.  Efekt algorytmu Bellmana-Forda dla macierzy znajduje sie w pliku result_macierz.txt" <<endl;
    shared_ptr<Graf> graf3=make_shared<Graf>();
    cout << "Wybierz liczbe wierzcholkow : 10, 50, 100, 500, 100. Wpisz wybrana liczbe :  ";
    cin >>n_vertices;
    cout << "Wybierz gestosc grafu : 0.25, 0.5, 0.75, 1. Wpisz wybrana liczbe:   ";
    cin >> density;
    int  n_edge=0.5*density*n_vertices*(n_vertices-1);
    graf3->saveFile("graf.txt",n_vertices,n_edge,density);
    graf3->readFile("graf.txt");
    List list2(graf3);
    list2.createList();          
    //list2.displayList();
    bool l;
    l=list2.BellmanFord();
    if(l==true) list2.saveScoreBF("result_list.txt");
    Matrix matrix2(graf3);
    matrix2.createMatrix();          
    //matrix2.displayMatrix();
    bool m;
    m=matrix2.BellmanFord();
    if(m==true) matrix2.saveScoreBF("result_matrix.txt");
break;
}
 return 0;
}