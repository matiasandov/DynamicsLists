//
//  Stack.hpp
//  Stack
//
//  Created by Matías Méndez on 11/10/20.
//


#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>
#include "/Users/matiasmendez/Desktop/PF/Listas_Enlazadas/Listas_Enlazadas/LinkedList.hpp"
using namespace std;

template<class T>
//estas declarando que todo de la clase linkedlits sera privado en esta clase nada mas para que no se vean los metodos publicos de linedlist y que la gente no se confunda
class Stack : private LinkedList<T>{
    
    //esto sis era public
public:
    //usar constructor de clase padre, no se pne punto y coma al final no se porque
    Stack() : LinkedList<T>(){ }
    //destructor que llamra a la funcion clear de LinkedList, recuerda que un destructor siempre se invoca con delete
    virtual ~Stack(){};
    
    //se pone apuntador para que se ahga espacio para el nodo geenrico que se recibirá
    //debemos declarar const el top porque no modifica nada
    Node<T> * top() const;
    Node<T> * pop();
    
    //falta push
    
    //para reusar solo ciertos métodos heredados de clase padre de manera publica aunque la herencia sea privada (no tienes que poner parentesis)
    using LinkedList<T>::empty;
    using LinkedList<T>::size;
    using LinkedList<T>::clear;
    
    //no se puede heredar la sobrecarga del operar << porque lo declaramos como atributo tipo friend, asi que podemos poner todo publico para poder acceder a él o podemos volver a hacerlo
    template <typename Tn>
    friend std::ostream & operator <<(std::ostream &, const Stack<Tn> &);
    
    /* Insertar un elemento en la pila */
        void push(const T &);
        void push(Node<T> *);
    
    
};
/* Obtener un apuntador al elemento de la parte superior de la pila
 * Complejidad: O(1)
 */
template <class T>
Node<T> * Stack<T>::top() const
{
    return this->first();
}

/* Eliminar el elemento de la parte superior de la pila
 * Complejidad: O(1)
 */
template <class T>
Node<T> * Stack<T>::pop()
{
    return this->remove_front();
}

/* Insertar un elemento en la pila
 * Complejidad: O(1)
 */
template <class T>
void Stack<T>::push(const T & value)
{
    this->insert_front(value);
}

template <class T>
void Stack<T>::push(Node<T> * node)
{
    this->insert_front(node);
}

template <class T>
std::ostream & operator <<(std::ostream & os, const Stack<T> & stack)
{
    /* Obtener el primer elemento de la lista */
    Node<T> * tmp = stack.top();
    
    /* Desplazarse mientras tmp != nullptr */
    while (tmp != nullptr) {
        os << *tmp << std::endl;
        
        /* Desplazar el apuntador al siguiente elemento */
        tmp = tmp->getNext();
    }
    
    return os;
}
#endif /* Stack_hpp */
#endif /* Stack_hpp */
