#ifndef NODO_H
#define NODO_H

#include "libro.h"
class Nodo
{
public:

    Nodo(Libro* l = nullptr, Nodo* n = nullptr) : libro(l), next(n) {}

    Libro* getData() const
    {
        return libro;
    }

    void setData(Libro* l)
    {
        libro = l;
    }

    Nodo* getNext() const
    {
        return next;
    }

    void setNext(Nodo* n)
    {
        next = n;
    }

private:
    Libro* libro;
    Nodo* next;
};

#endif // NODO_H
