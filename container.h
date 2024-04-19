#ifndef CONTAINER_H
#define CONTAINER_H

#include <vector>
#include "eserciziari.h"
#include "letture.h"
#include "libri_di_testo.h"

template <typename Libro>
class Container
{
    Libro* elenco;
    int size;

public:
    Container()
    {
        elenco = new Libro[1];
        size = 0;
    }

    ~Container()
    {
        delete[] elenco;
    }

    /**
     * INSERIMENTO di un libro all'interno del contenitore
     * incrementandone poi la dimensione
     *
     * (UTILIZZO AL MOMENTO DELL'INSERIMENTO DI UN NUOVO LIBRO IN UNA DELLE TRE TABELLE)
     *
     * @param data: è il libro da inserire (i relativi controlli
     * sul valore null sono previsti nella parte grafica, al momento
     * dell'inserimento dei dati del nuovo libro)
     */
    void push(const Libro& data)
    {
        elenco[size] = data;
        size++;
    }

    /**
     * METODO DI RESTITUZIONE TRAMITE LETTURA DI UN PARAMETRO
     * Restituisce il libro dall'elenco in posizione i
     * @param k è l'indice da dove restituire il libro
     * @return il libro in posizione k se esiste; nullptr altrimenti
     */
    Libro* operator[](int k)
    {
        for(int i = 0; i < size; i++)
        {
            if(i == k)
            {
                return &elenco[i];
            }
        }
        return nullptr;
    }

    /**
     * Rimozione di un libro con codice il codice isbn
     * se corrispondenza identificata (LETTURA ISBN DEI LIBRI)
     *
     * UTILIZZO AL MOMENTO DELLA RIMOZIONE DI UN LIBRO DA UNA DELLE TABELLE
     * CON CONDIZIONE (VERIFICATA NELL?INTERFACCIA GRAFICA) CHE LA DISPONIBILITA
     * SIA NULLA
     *
     * @param isbn è il codice del libro da rimuovere
     */
    void pop(string isbn)
    {
        for (int i = 0; i < size; i++)
        {
            if (elenco[i].getISBN() == isbn)
            {
                if (i < size - 1)
                {
                    elenco[i] = elenco[size - 1];
                }
                size--;
                return;
            }
        }
    }

    /**
     * Restituisce il libro in posizione index (gli eventuali controlli
     * sul valore di index non sono necessari in quanto i valori vengono
     * verificati nella parte di interfacciamento con l'utente)
     * @param index indica la posizione del libro da restituire
     * @return il libro in posizione indes
     */
    Libro* get(int index) {
        if (index >= size) {
            return nullptr;
        }
        return &elenco[index];
    }

    /**
     * Restituisce la dimensione del contenitore, ovvero il numero di libri contenuti
     * @return la dimensione del container
     */
    int getSize()
    {
        return size;
    }

    /**
     * METODO DI LETTURA DEI DATI (ISBN) DEI LIBRI
     * Dato un codice isbn cerca se esiste un libro con tale codice e lo restituisce
     * @param isbn è il codice da ricercare
     * @return il libro, se estiste; nullptr altrimenti
     */
    Libro* cercaLibro(string isbn)
    {
        for(int i = 0; i < size; i++)
        {
            if (elenco[i].getISBN() == isbn)
            {
                return &elenco[i];
            }
        }
        return nullptr;
    }

    /**
     * Aggiornamento della disponibilita di un libro da identificare tramite isbn
     * @param isbn è il codice del libro da identificare e per cui cambiare la
     * disponibilita con disp
     * @param disp è la nuova disponibilita del libro
     */
    void aggiornaDisp(string isbn, int disp)
    {
        for(int i = 0; i < size; i++)
        {
            if(elenco[i]->getISBN() == isbn)
            {
                elenco[i]->updateDisp(disp);
                return;
            }
        }
    }

    /**
     * Verifica la presenza nel contenitore di un libro con codice isbn
     * selezionato (Utilizzato al momento della creazione di un nuovo libro
     * per evitare di creare 2 libri diversi con stesso isbn)
     * @param isbn è il codice isbn per cui verificare l'assenza di altri libri
     * con stesso codice
     * @return true se il libro con codice isbn esiste gia; false altrimenti
     */
    bool verificaPresenzaLibro(string isbn)
    {
        for(int i = 0; i < size; i++)
        {
            if(elenco[i]->getISBN() == isbn)
            {
                return true;
            }
        }
        return false;
    }

    /**
     * Metodo di estrazione ed inserimento in un vettore di tutti i libri
     * della categoria LETTURE -> necessario per l'inserimento nella tabella
     * delle letture
     * @return un vettore con solo i libri della categoria letture
     */
    vector<Letture*> getLetture()
    {
        vector<Letture*> letture;

        for(int i = 0; i < size; i++)
        {
            if (dynamic_cast<Letture*>(elenco[i]) != nullptr)
            {
                letture.push_back(dynamic_cast<Letture*>(elenco[i]));
            }
        }

        return letture;
    }

    /**
     * Metodo di estrazione ed inserimento in un vettore di tutti i libri
     * della categoria ESERCIZIARI -> necessario per l'inserimento nella tabella
     * degli eserciziari
     * @return un vettore con solo i libri della categoria eserciziari
     */
    vector<Eserciziari*> getEserciziari()
    {
        vector<Eserciziari*> eserciziari;

        for(int i = 0; i < size; i++)
        {
            // Controllo tipo dinamico libro
            Eserciziari* l = dynamic_cast<Eserciziari*>(elenco[i]);

            if(l)  // se è un libro-lettura, inserimento in coda
                eserciziari.push_back(l);
        }
        return eserciziari;
    }

    /**
     * Metodo di estrazione ed inserimento in un vettore di tutti i libri
     * della categoria LIBRI DI TESTO -> necessario per l'inserimento nella tabella
     * dei libri di testo
     * @return un vettore con solo i libri della categoria libri di testo
     */
    vector<Libri_Di_Testo*> getLibriDiTesto()
    {
        vector<Libri_Di_Testo*> libriDiTesto;

        for(int i = 0; i < size; i++)
        {
            // Controllo tipo dinamico libro
            Libri_Di_Testo* l = dynamic_cast<Libri_Di_Testo*>(elenco[i]);

            if(l != nullptr)  // se è un libro-lettura, inserimento in coda
                libriDiTesto.push_back(l);
        }
        return libriDiTesto;
    }

    /**
     * Overloading operator ->
     * @return l'elenco dei libri
     */
    Libro* operator->()
    {
        return elenco;
    }

};

#endif // CONTAINER_H
