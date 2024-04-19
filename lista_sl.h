#ifndef LISTA_SL_H
#define LISTA_SL_H

#include "Nodo.h"
#include "eserciziari.h"
#include "letture.h"
#include "libri_di_testo.h"
class lista_sl
{

private:
    Nodo* testa;
    int dimensione;

public:

    lista_sl() : testa(nullptr), dimensione(0) {}

    ~lista_sl()
    {
        clear();
    }

    void pushFront(Libro* l)
    {
        testa = new Nodo(l, testa);
        dimensione++;
    }

    void popFront()
    {
        if (testa)
        {
            Nodo* temp = testa;
            testa = testa->getNext();
            delete temp;
            dimensione--;
        }
    }

    void pop(const std::string& isbn)
    {
        Nodo* prev = nullptr;
        Nodo* curr = testa;

        while (curr != nullptr)
        {
            if (curr->getData()->getISBN() == isbn)
            {
                // Match found, remove node
                if (prev == nullptr) {
                    // Special case: head node
                    testa = curr->getNext();
                }
                else {
                    prev->setNext(curr->getNext());
                }
                delete curr;
                dimensione--;
                return;
            }
            prev = curr;
            curr = curr->getNext();
        }
    }


    void clear()
    {
        while (testa)
        {
            popFront();
        }
    }

    int size() const
    {
        return dimensione;
    }

    Libro* get(int index) const
    {
        if (index < 0 || index >= dimensione)
        {
            return nullptr;
        }

        Nodo* current = testa;

        for (int i = 0; i < index; i++)
        {
            current = current->getNext();
        }
        return current->getData();
    }

    void aggiornaDisp(string isbn, int disp)
    {
        Nodo* current = testa;

        for (int i = 0; i < dimensione; i++)
        {
            if(current->getData()->getISBN() == isbn)
            {
                current->getData()->updateDisp(disp);
                return;
            }
            current = current->getNext();
        }
    }

    bool verificaPresenzaLibro(string isbn)
    {
        Nodo* current = testa;

        for(int i = 0; i < dimensione; i++)
        {
            if(current->getData()->getISBN() == isbn)
            {
                return true;
            }
            current = current->getNext();
        }
        return false;
    }

    vector<Letture*> getLetture()
    {
        vector<Letture*> letture;
        Nodo* current = testa;

        for (int i = 0; i < dimensione; i++)
        {
            if (dynamic_cast<Letture*>(current->getData()) != nullptr)
            {
                // Cast the data pointer to a Letture pointer
                Letture* letturePtr = dynamic_cast<Letture*>(current->getData());

                // Add the Letture pointer to the vector
                letture.push_back(letturePtr);
            }
            current = current->getNext();
        }

        return letture;
    }

    vector<Eserciziari*> getEserciziari()
    {
        vector<Eserciziari*> esericiziari;
        Nodo* current = testa;

        for (int i = 0; i < dimensione; i++)
        {
            if (dynamic_cast<Eserciziari*>(current->getData()) != nullptr)
            {
                // Cast the data pointer to a Letture pointer
                Eserciziari* esericiziariPtr = dynamic_cast<Eserciziari*>(current->getData());

                // Add the Letture pointer to the vector
                esericiziari.push_back(esericiziariPtr);
            }
            current = current->getNext();
        }

        return esericiziari;
    }

    vector<Libri_Di_Testo*> getLibriDiTesto()
    {
        vector<Libri_Di_Testo*> libriDiTesto;
        Nodo* current = testa;

        for (int i = 0; i < dimensione; i++)
        {
            if (dynamic_cast<Libri_Di_Testo*>(current->getData()) != nullptr)
            {
                // Cast the data pointer to a Letture pointer
                Libri_Di_Testo* libriDiTestoPtr = dynamic_cast<Libri_Di_Testo*>(current->getData());

                // Add the Letture pointer to the vector
                libriDiTesto.push_back(libriDiTestoPtr);
            }
            current = current->getNext();
        }

        return libriDiTesto;
    }

};

#endif // LISTA_SL_H
