//
//  LinkedList.hpp
//  Listas_Enlazadas
//
//  Created by Matías Méndez on 25/09/20.
//

#ifndef LinkedList_hpp
#define LinkedList_hpp

#include <stdio.h>
#include "Node.hpp"


template <class T>
class LinkedList{
protected:
    //apuntador a primer elemento siempre y el nullptr es apra saber si esta vacia creo
    Node<T> * _first = nullptr;
    //se ira actulizando
    int _size = 0;
    

    //sobrecarga de operadores para hacer un for
    /* Clase Iterator */
    class Iterator {
        const LinkedList<T> * _data;
        int _position;
        
    public:
        /*aqui ya se está haciendo el constructor de la clase indicando que estará compuesto de
         -el objeto node
         -la posicion de parada
         */
        Iterator( const LinkedList<T> * _adata, int _aposition)
        : _data(_adata), _position(_aposition) {}
        
        Node<T> operator *() const { return *(_data->at(_position)); }
        const  Iterator & operator ++() { ++_position; return *this; }
        bool operator != (const Iterator & it) const { return _position != it._position; }
    };// todo lo de arriba es una clase protegida dentro de otra clase para heredar una clase iterador que finalmente será un for
    
public:
    LinkedList(){};
    //destrcutor que llamara los destrcutores de sus nodes
    virtual ~LinkedList();
    
    //metodo para tamaño de la lsita
    int size() const;
    
    //metodo para obtener apuntador a primer elemento
    Node<T> * first() const;
    
    //saber si la lista esta vacia o no
    bool empty() const;
    
    //insertar un elemento en alguna posicion
    void insert(const T &, int); //pasas referencia de algo que puede ser YA HECHO -> insert(5), se pasa una direccion de memoria de ese 5
    //para clonar creo
    void insert(const Node<T> *, int); //pasas objeto un objeto nuevo -> insert(new Node <int> 5), se crea nuevo espacio de memoria para ese 5
    
    /*______________ con T & pasas objeto ya hecho y con Node<T> * creas uno nuevo con nuevo espacio en memoria */
    void insert_front(const T &);
    void insert_front(Node<T> *);
    /* Insertar un elemento al final */
    
       void insert_back(const T &);
       void insert_back(Node<T> *);
    
    /* Eliminar el elemento en la posición dada */
      Node<T> * remove(int);
    /* Eliminar el primer elemento */
       Node<T> * remove_front();
       
       /* Eliminar el último elemento */
       Node<T> * remove_back();
       
       /* Eliminar un elemento dado */
       Node<T> * remove(Node<T> *);
       
       
       
       /* Obtener el elemento que se encuentra en una posición de dirección de memoria */
       Node<T> * at(int) const;
       
       /* Obtener la posición de un nodo */
       int at(Node<T> *) const;

    
    /* Obtener la posición de un nodo */
       virtual int index(Node<T> *) const;
       
       /* Obtener la posición de un valor */
       virtual int index(const T &) const;
    
    
       /* Mostrar el contenido de la lista */
    //es importante saber que aqui debes poner Tn para que no se confunda con T porque es una funcion generica FRIEND
    template <typename Tn>
    friend std::ostream & operator <<(std::ostream &, const LinkedList<Tn> &);
    
    
    /* Funciones que utiliza el foreach */
    Iterator begin() const { return { this, 0}; }
    Iterator end() const { return {this, _size }; }
       
    /* Sobrecarga del operador índice */
    Node<T> * operator [](const int);
    
    //ejercicio
    int count(const T &);
    /* Eliminar todos los elementos de la lista y liberar la memoria ocupada */
    virtual void clear();
    void SortedInsert (Node<T> * );
    void RemoveDuplicates ();
    void reverse();
    
    
    
    
};//__________________________________________________________________


template <class T>
LinkedList<T>::~LinkedList()
{
    this->clear();
}

/* Obtener el tamaño de la lista */
template <class T>
int LinkedList<T>::size() const
{
    return this->_size;
}

/* Obtener el primer elemento */
template <class T>
Node<T> * LinkedList<T>::first() const
{
    return this->_first;
}

//saber si la lista esta vacia o no
template <class T>
bool LinkedList<T>::empty() const{
    //si vacia se regresara que el primer elemento es nulo
    return this-> _first == nullptr;
}

/* Insertar un elemento en una posición dada */
template <class T>
void LinkedList<T>::insert(const T &, int)
{
    /* Por implementar */
}

/*template <class T>
void LinkedList<T>::insert(Node<T> * node, int v)
{
    Por implementar 
}*/

template <class T>
void LinkedList<T>::insert_front(const T & value){
    //creas un nuevo nodo
    Node<T> * node = new Node<T>(value);
    //se llama la funcion de abajo porque indica como se inserta ya
    this -> insert_front(node);
    //se debe actualizar size
    ++this->_size;
}

template <class T>
void LinkedList<T>::insert_front( Node<T> * node){
    //si esta vacia se pone este al frente
    if(this -> empty() ){
        this -> _first = node;
    }
    //si no vacia se poner el nuevo elemento al frente apuntando al viejo elemento
    else{
        //se apunta al siguiente
        node->setNext(this-> _first);
        //se pone en primera posicion
        this-> _first = node;
        //se debe actualizar size
        ++this->_size;
    }
}

template <class T>
//va a regresar el objeto eliminado
Node<T> * LinkedList<T>::remove_front(){
    //tiene que haber una variable temporal first para no perder el apuntador y despues ya se borra
    //el primer apuntador debe pasar al del segundo elemento
    //se tiene que liberar la memoria del antiguo primer elemento
    
    //tenemos que checar si el primero esta vacio porque para ver si no hay nada que borrar
    
    //variable temporal para guardar nodo que se quiere borrar
    Node<T> *old = nullptr;
    if(!this -> empty() ){
        //se guarda referencia lo que hay ahorita en el primer elemento, con esto se desvincula de la lista
        old = this->_first;
        //se poner first a apuntar a la siguiente posición
        this-> _first = old->getNext();
        //apuntas a direccion vacia y desligas de la lista
        old -> setNext(nullptr);
        
        //se debe actualizar size
        --this->_size;
    }
    return  old;
}

template <class T>
std::ostream & operator <<(std::ostream & os, const LinkedList<T> & list)
{
    /* Obtener el primer elemento de la lista */
    Node<T> * tmp = list._first;
    
    /* Desplazarse mientras tmp != nullptr */
    while (tmp != nullptr) {
        os << *tmp << std::endl;
        
        /* Desplazar el apuntador al siguiente elemento */
        tmp = tmp->getNext();
    }
    
    return os;
}

//Complejidad lineal
template <class T>
int LinkedList<T>::count(const T & value){
    int cont = 0;
 
    /* Obtener referencia el primer elemento de la lista */
    Node<T> * tmp = this->_first;
    
    /* Desplazarse mientras tmp != nullptr */
    while (tmp != nullptr  ) {
        if(value == tmp->getInfo() ){
            cont = cont +1;
        }
        tmp = tmp->getNext();
    }
    return cont;
    
}

//Complejidad lineal
template <class T>
void LinkedList<T>::clear(){


//variable temporal para guardar nodo que se quiere borrar
//se guarda referencia lo que hay ahorita en el primer elemento, con esto se desvincula de la lista
    Node<T> *old =  this->_first;
    
    //mientras la lista (direccion) no este vacía
    while (!this -> empty()) {
        
        //se pone first a apuntar a la siguiente posición
        this-> _first = old->getNext();
        //liberar memoria del nodo
        
        delete old;
        
        //se crea un nuevo old para el nuevo ciclo
        old = this -> _first;
        
    }
    //se debe actualizar size
    this->_size = 0;
    
    //al final del ciclo ya no puedes hacer delete al ultimo old, asi que lo borras así
    this-> _first = nullptr;
    
}

template <class T>
void LinkedList<T>::SortedInsert(Node<T> * node){
    //primero para asegurarnos que la lista no esté vacia
    if(!this -> empty()){
        
        //temporal que ira avanzado en la lista
        Node<T> * actual = _first;
        
        //temporal para guardar posicion previa
        Node<T> * prev = nullptr;

        //mientras no se llegue al final y el actual no sea mayor al nodo buscado
        while (actual != nullptr &&  (actual->getInfo() < node->getInfo())) {
            //el actual sera el nuevo previo
            prev = actual;
            //el actual se avanza un lugar
            actual = actual->getNext();
        }
        
        //se pondrá en el inicio el nodo si la lista esta vacia, ya que  no se cambio nullpt para prev
        if (prev == nullptr) {
            insert_front(node);
        }
        //si el nodo es igual o mayor al valor info actual
        else {
            //se pone al actual despues del node porque puede ser igual o mayor que este
        node->setNext( prev->getNext() );
            //se pone al node después del previo al actual
        prev->setNext (node);
        ++this->_size;
            
            cout <<"\n elemento : " << *node << " colocado \n";
        }
            
        
    }//IF NO VACIO
        
 
}

template <class T>
void LinkedList<T>::RemoveDuplicates(){
    
    //primero para asegurarnos que la lista no esté vacia
    if(!this -> empty()){
        
        //temporal para guardar posicion previa
        Node<T> * prev = nullptr;
        
        //temporal que ira avanzado en la lista
        Node<T> * actual = _first;
        
        //se pone prev en primera posicion
        prev = actual;
        //se pone actual en segunda
        actual = actual->getNext();
        
        //mientras no se llegue al final y mientras el nodo actual y el siguiente no tengan valores iguales, se recorrera la lista
        while (actual != nullptr ){
            
            if(prev->getInfo() != actual->getInfo() )  {
                //el actual sera el nuevo previo
                prev = actual;
                //el actual se avanza un lugar
                actual = actual->getNext();
                
            }
            else{
                //se podría decir que se avanza 2 lugares al previo y el previo no se actualiza, porque el que sigue después del previo se borrará
                actual = actual->getNext();
                prev->setNext(nullptr);
                cout << " \n numero repetido eliminado ";
                --this->_size;
                
            }
        }
    }//IF NO VACIO
        
}

template <class T>
void LinkedList<T>::reverse(){
    /*se trabajará con un ciclo de 3 nodos a la vez, donde *actual será el ultimo de los 3, para que en la siguiente iteración se encuentre de nuevo a la mitad*/
    
    //temporal para guardar posicion previa
    Node<T> * prev = nullptr;
    
    //temporal que ira avanzado en la lista
    Node<T> * actual = _first;
    
    //temporal para gurdar el sig al actual
    Node<T> * sig = nullptr;
    
    
    while (actual != nullptr ) {
        //sig señala al next de actual
        sig = actual->getNext();
        
        //aqui es donde empieza el cambio, prev tambien señalará al next de actual
        actual->setNext(prev);
        
        //con esto prev se recorre un espacio adelante
        prev = actual;
        
        //el actual ahora queda de nuevo a la mitad de los 3 y sig ya no se mueve
        actual = sig;
        
    }
    _first = prev;
    
    
}
    
template  <class T>
Node<T> * LinkedList<T>::at(int position) const
{
        /* Cuando la lista está vacía o position es inválida */
        if (this->empty() || position < 0 || position >= this->_size) {
            return nullptr;
        }
        
        /*  Buscar el nodo que se encuentra en position */
        int pos = 0;
        
        /* Obtener una referencia al primer nodo */
        Node<T> * tmp = this->_first;
        
        /* Desplazarse por la lista hasta encontrar el nodo */
        while (tmp != nullptr && pos++ < position)
        {
            tmp = tmp->getNext();
        }
        
        return tmp;
    }

    /* Obtener la posición de un nodo
     * Complejidad: O(n)
     */
    template  <class T>
    int LinkedList<T>::index(Node<T> * node) const
    {
        /* Cuando la lista está vacía o node es nullptr */
        if (this->empty() || node == nullptr) {
            return -1;
        }
        
        /* Buscar el valor del nodo y regresar su posición */
        return this->index( node->getInfo() );
    }

    /* Obtener la posición de un valor
     * Complejidad: O(n)
     */
    template  <class T>
    int LinkedList<T>::index(const T & value) const
    {
        /* Cuando la lista está vacía */
        if ( this->empty() ) {
            return -1;
        }
        
        /* Buscar value y regresar su posición */
        int pos = 0;
        
        /* Obtener una referencia al primer nodo */
        Node<T> * tmp = this->_first;
        
        /* Desplazarse por la lista hasta encontrar el value */
        while (tmp != nullptr && tmp->getInfo() != value)
        {
            tmp = tmp->getNext();
            ++pos;
        }
        
        /* Si el value no se encuentra en la lista */
        if (pos == this->_size) { return -1; }
        
        return pos;
    }
    
/* Obtener el elemento de una posición
 * Complejidad: O(n)
 */
template  <class T>
Node<T> * LinkedList<T>::operator [](const int position)
{
    return this->at(position);
}


    

#endif /* LinkedList_hpp */
