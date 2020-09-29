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
private:
    //apuntador a primer elemento siempre y el nullptr es apra saber si esta vacia creo
    Node<T> * _first = nullptr;
    //se ira actulizando
    int _size = 0;
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

       /* Mostrar el contenido de la lista */
    //es importante saber que aqui debes poner Tn para que no se confunda con T porque es una funcion generica FRIEND
       template <typename Tn>
       friend std::ostream & operator <<(std::ostream &, const LinkedList<Tn> &);
    
    
    
    //ejercicio
    int count(const T &);
    /* Eliminar todos los elementos de la lista y liberar la memoria ocupada */
    virtual void clear();
    void SortedInsert (Node<T> * );
    
};


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
    //si no vacia se poner el viejo elemento al frente apuntando al nuevo elemento
    else{
        node->setNext(this-> _first);
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

template <class T>
int LinkedList<T>::count(const T & value){
    int cont = 0;
 
    /* Obtener el primer elemento de la lista */
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

template <class T>
void LinkedList<T>::clear(){
//tiene que haber una variable temporal first para no perder el apuntador y despues ya se borra
//el primer apuntador debe pasar al del segundo elemento
//se tiene que liberar la memoria del antiguo primer elemento

//tenemos que checar si el primero esta vacio porque para ver si no hay nada que borrar

//variable temporal para guardar nodo que se quiere borrar
Node<T> *old = nullptr;
    //habia puestowhile (old != nullptr  ) y despues un if!this -> empty(), lo cual es hacer lo mismo dos veces, que es como negarlo creo
    //mientras la lista (direccion) no este vacía
    while (!this -> empty()) {
        //se guarda referencia lo que hay ahorita en el primer elemento, con esto se desvincula de la lista
        old = this->_first;
        //se pone first a apuntar a la siguiente posición
        this-> _first = old->getNext();
        //apuntas a direccion vacia y desligas de la lista el elemento old
        old -> setNext(nullptr);
        
        //se debe actualizar size
        --this->_size;
        
    }
}

template <class T>
void LinkedList<T>::SortedInsert(Node<T> * node){
    //primero para asegurarnos que la lista no esté vacia
    if(!this -> empty()){
        //nodo siguiente, el cual irá cambiando conforme se avance
        Node<T> *sig = node->getNext();
        while (node != nullptr ) {
            if (node->getInfo() < sig->getInfo() ) {
                //node avanza un lugar
                node = node->getNext();
                //sig node avanza un lugar
                sig = sig->getNext();
                cout << "\n avanzado ";
            }
            if(node->getInfo() >= sig->getInfo() ){
                cout << "\n ya se guardo ";
            }
        
        }
        
    }else{
        insert_front(node);
    }
}

#endif /* LinkedList_hpp */