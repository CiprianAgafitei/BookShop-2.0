#ifndef LIBRO_H
#define LIBRO_H

#include <QFile>
#include <string>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

using namespace std;

/* LIBRO generico-astratto, suddiviso in 3 categorie principali (ed estendibile).
   Tutti i libri sono dotati delle seguenti caratteristiche comuni:
        - isbn: codice univoco di ciascun libro (2 libri sono uguali se hanno lo stesso isbn)
            Due libri possono avere lo stesso isbn se sono identici
        - titolo del libro
        - disponibilita' del libro: indica il numero di libri disponibili del tipo del Libro (Lettura/Testo/Eserciziario).
            Al momento dell'inserimento di un nuovo libro, per default la disponibilita' sarà 1.    */
class Libro {
    friend class Letture;
    friend class Libri_Di_Testo;
    friend class Eserciziari;    // friend per accesso a prezzo in libri di testo
private:
    string isbn;      // Codie identificativo ed univoco di ogni libro
    string titolo;
    int disponibilita;     // Disponibilità del libro: nr. libri disponibili (default=1, al momento di creazione)
    double prezzo;
public:
    Libro(string _isbn="", string tit="", int av=1, double pr=0.0);
    string getISBN();
    string getTitolo();
    int getDisp();
    double getPrezzo();
    void updateISBN(string Isbn);
    void updateTitolo(string s);
    void modificaDisp(int n);       // Modifica la disponibilità ponendola uguale a n
    void updateDisp(int nr);    // Incrementa di nr la disponibilità
    void updatePrezzo(double p);

    void operator=(const Libro& l);

    virtual void calcolaPrezzoTotale(double pp) = 0;

    Libro(const Libro& l);  // COPIA PROFONDA
    ~Libro();       // equivale al DISTRUTTORE di DEFAULT -> tipi primitivi
};

#endif // LIBRO_H
