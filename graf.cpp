#include "graf.hh"

using namespace std;

/*********************************************************************************************************************************/
/*                 FUNKCJE DO GRAFU                                                                                             */
/*******************************************************************************************************************************/
void Graf::saveFile(string filename,int vertices,int edges,double density)
{
	Edge E;
    
    ofstream file;
	file.open(filename);
  
	file << edges << "\t" << vertices << "\t" << 0 << "\n"; // zapis liczby wierzcholkow, liczby krawedzi i wierzcholek poczatkowy jako 0 
    
    int k=1; // do odpowiedniego przyliczania wierzcholków
    int l=0; // do zliczania krawdedzi 
 
    if(density==1){  // lacze kazdy wierzcholek z kazdym
        for(int i=0; i< vertices-k; i++){ 
            l++;

            int vertex1=i; //daj pierwszy wierzcholek
            int vertex2=i+k; //daj drugi wierzcholek
            E.setRandWeight();             // losuje wage krawedzi
            
            int weight=E.getWeight();

            if(weight==0){
            E.setRandWeight();
            weight=E.getWeight();
            }
        
            file << vertex1 << "\t" << vertex2 << "\t" << weight << endl;

            if(i==vertices-k-1) { i=-1;  k++; }       
            if(k==vertices) break; 
            if(l==edges) break;  
        }   
    }

    if(density==0.25 || density==0.5 || density==0.75){ //polaczenia pomiedzy wierzcholkami sa losowe
        int **tab=new int*[vertices];
        for (int i=0; i<vertices; i++){
            tab[i] = new int[vertices]; 
        }
               
        for(int i=0; i<vertices; i++){
            for(int j=0; j<vertices; j++){
                tab[i][j]=FLAG; //wypelnienie tablicy flaga -> krawedz nie istnieje
            }
        }        
        
        for(int i=0; i<vertices-1; i++){
            int vertex1=i; //losuje pierwszy wierzcholek
            int vertex2=i+1; //losuje drugi wierzcholek
            E.setRandWeight();
            int weight=E.getWeight();  // przypisuje wage krawedzi 
            
            if(weight==0){
            E.setRandWeight();
            weight=E.getWeight();
            }

             tab[vertex1][vertex2]=EXIST;
             file << vertex1 <<"\t" << vertex2 << "\t" << weight << endl;
        }
       
        for(int j=vertices-1; j<edges; j++){ 
            E.setRandVertex1(vertices);
            E.setRandVertex2(vertices);
            E.setRandWeight();

            int vertex1=E.getVertex1(); //losuje pierwszy wierzcholek
            int vertex2=E.getVertex2(); //losuje drugi wierzcholek
            int weight=E.getWeight();  // losuje wage krawedzi

            if(weight==0){
            E.setRandWeight();
            weight=E.getWeight();
            }
                //Sprawdzenie czy krawedz wystapila
                if((tab[vertex1][vertex2]==EXIST) || (vertex1==vertex2)) { j--; continue; }
                if(tab[vertex1][vertex2]==FLAG){
                    tab[vertex1][vertex2]=EXIST;
                
                    file << vertex1 <<"\t" << vertex2 << "\t" << weight << endl;
                }   
        }
        for (int i = 0; i < vertices;i++){
            delete [] tab[i];
        }
            delete [] tab;    
    }

	file.close();
}

void Graf::readFile(string filename)
{
    ifstream file; // uchwyt do pliku
	file.open(filename); //otwieranie pliku
    string line; // linijka pliku 
   
    int elem1,elem2,elem3;
    
		getline(file, line, '\t'); // zczytanie liczby krawedzi
        n_edges=stoi(line);
  
        getline(file, line, '\t'); // zczytanie liczby wierzcholkow
        n_vertices=stoi(line);
     
        getline(file, line, '\n'); // zczytanie wierzcholka startowego
        first_vertex=stoi(line);
   
    for(int i=2; i<n_edges+2;i++ ) // bo liczymy od elementu drugiego jak od zera 
    {
        getline(file,line,'\t'); 
        elem1=stoi(line);
        
        getline(file,line,'\t'); 
        elem2=stoi(line);

        getline(file,line,'\n'); 
        elem3=stoi(line);

        shared_ptr<Edge> elem =make_shared<Edge>(elem1,elem2,elem3);
        list_edge.push(elem);
    }

    file.close();
}

void Graf::makeGraf(int vertices,int edges,double density)
{
    Edge E;
    n_edges=edges;
    n_vertices=vertices;
    first_vertex=0;

    int k=1; // do odpowiedniego przyliczania wierzcholków
    int l=0; // do zliczania krawdedzi 
 
    if(density==1){  // lacze kazdy wierzcholek z kazdym
        for(int i=0; i< vertices-k; i++){ 
            l++;

            int vertex1=i; //daj pierwszy wierzcholek
            int vertex2=i+k; //daj drugi wierzcholek
            E.setRandWeight();             // losuje wage krawedzi
            
            int weight=E.getWeight();

            if(weight==0){
                E.setRandWeight();
                weight=E.getWeight();
            }
        
            shared_ptr<Edge> elem =make_shared<Edge>(vertex1,vertex2,weight);
            list_edge.push(elem);

            if(i==vertices-k-1) { i=-1;  k++; }       
            if(k==vertices) break; 
            if(l==edges) break;  
     
        }   
    }

    if(density==0.25 || density==0.5 || density==0.75){ //polaczenia pomiedzy wierzcholkami sa losowe
        int **tab=new int*[vertices];
        for (int i=0; i<vertices; i++){
            tab[i] = new int[vertices]; 
        }
               
        for(int i=0; i<vertices; i++){
            for(int j=0; j<vertices; j++){
                tab[i][j]=FLAG; //wypelnienie tablicy flaga -> krawedz nie istnieje
            }
        }        
        
        for(int i=0; i<vertices-1; i++){
            int vertex1=i; //losuje pierwsz wierzcholek
            int vertex2=i+1; //losuje drugi wierzcholek
            E.setRandWeight();
            int weight=E.getWeight();  // przypisuje wage krawedzi 
            
            if(weight==0){
            E.setRandWeight();
            weight=E.getWeight();
            }

             tab[vertex1][vertex2]=EXIST;
             shared_ptr<Edge> elem=make_shared<Edge>(vertex1,vertex2,weight);
             list_edge.push(elem);
        }
       
        for(int j=vertices-1; j<edges; j++){ 
            E.setRandVertex1(vertices);
            E.setRandVertex2(vertices);
            E.setRandWeight();

            int vertex1=E.getVertex1(); //losuje pierwsz wierzcholek
            int vertex2=E.getVertex2(); //losuje drugi wierzcholek
            int weight=E.getWeight();  // losuje wage krawedzi

            if(weight==0){
            E.setRandWeight();
            weight=E.getWeight();
            }

                if((tab[vertex1][vertex2]==EXIST) || (vertex1==vertex2)) { j--; continue; }
                if(tab[vertex1][vertex2]==FLAG){
                    tab[vertex1][vertex2]=EXIST;
                    
                    shared_ptr<Edge> elem=make_shared<Edge>(vertex1,vertex2,weight);
                    list_edge.push(elem);
                }   
        }
      
      for (int i = 0; i < vertices;i++){
        delete [] tab[i];
      }
      delete [] tab;    
    }
}


