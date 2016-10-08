
#include<iostream>
#include<list>
#include <math.h>

using namespace std;

template<class T>
class NodoB
{
    typedef NodoB<T> *  pNodo; 
    public:
      int                m_Grado;
      T                  m_Dato;
      pNodo              m_pPadre;
      list< pNodo >      m_Son; 
     NodoB(T d)
      {
           m_Dato = d;
           m_Grado =0;
      } 
};

template<class T>
class BinomialHeap
{
    typedef NodoB<T> *  pNodo; 
    typedef    list< NodoB<T> *>       TLista;
    typedef typename   TLista::iterator  TIterator; 
    
    private:
    	int num_datos;
      TLista  m_Heads;
    public:
      BinomialHeap(){
      	num_datos=0;
      };
      void Insert(T d)
      {
          m_Heads.push_back(new NodoB<T>(d));
          ++num_datos;
          merge();    
      }
      T minimo()
      {
            TIterator it = m_Heads.begin();
            T min =  (*it)->m_Dato;
             for(; it !=m_Heads.end() ; ++it)
                  if(min>(*it)->m_Dato)
                     min = (*it)->m_Dato;
            return min;
      }
      void merge()
      {		int n = log2(num_datos)+1;
            pNodo arreglo[n] ;

            for( int i =0;i<n ; ++i) arreglo[i] = 0;


            TIterator it = m_Heads.begin();
            while(it!=m_Heads.end()){
                int posicion = (*it)->m_Grado;

                if(arreglo[posicion] == 0){
                    arreglo[posicion] = (*it);
                    it++;
                }
                else{
                    if (arreglo[posicion]->m_Dato > (*it)->m_Dato){
                        swap(*(arreglo[posicion]),*(*it));


                        for(TIterator it2 = arreglo[posicion]->m_Son.begin() ;it2!= arreglo[posicion]->m_Son.end();++it2){
                            (*it2)->m_pPadre = arreglo[posicion];
                        }
                        for(TIterator it2 = (*it)->m_Son.begin(); it2!= (*it)->m_Son.end();++it2){
                            (*it2)->m_pPadre = *it;
                        }
                    }

                    arreglo[posicion]->m_Son.push_back(*it);
                    (*it)->m_pPadre = arreglo[posicion];
                    TIterator temp = it;
                    temp--;
                    m_Heads.erase(it);
                    it = temp;
                    arreglo[posicion]->m_Grado++;
                    arreglo[posicion] = 0;
                }


            }

            return ;
      }
      void Decrease_key(pNodo p , T d)
      {
          p->m_Dato = d;
          while(p->m_pPadre)
          {
                 if (p->m_Dato < p->m_pPadre->m_Dato)
                        swap(p->m_Dato,p->m_pPadre->m_Dato);
                 else return;
          }
      }
     
      void Extract_min()
      {

            TIterator it = m_Heads.begin();
            pNodo min = *it;
             for(; it !=m_Heads.end() ; ++it)
                  if(min->m_Dato>(*it)->m_Dato)
                     min = (*it);
            
             TIterator it_son = min->m_Son.begin();
             for(; it_son != min->m_Son.end() ; ++it_son)
                  m_Heads.push_back(*it_son);
             m_Heads.remove(min);
             merge();
      }
 
      void Delete(pNodo p)
      {
          Decrease_key(p,-10000);
          Extract_min();    
      }  



  
};
  
