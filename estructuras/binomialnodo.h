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
     bool isHoja(){
         if (m_Son.empty()) return true;
         else return false;
     }
};
