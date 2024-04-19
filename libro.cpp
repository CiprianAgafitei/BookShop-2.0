#include "libro.h"

Libro::Libro(string _isbn, string tit, int av, double pr) : isbn(_isbn), titolo(tit), disponibilita(av), prezzo(pr) {}

Libro::Libro(const Libro& l) : isbn(l.isbn), titolo(l.titolo), disponibilita(l.disponibilita), prezzo(l.prezzo) {}

Libro::~Libro() {}

/**
 * Restituisce il codice ISBN del libro selezionato
 *
 * @return string isbn del libro selezionato
 */
string Libro::getISBN() {
    return isbn;
}

/**
 * Imposta un dato ISBN
 * @param Isbn è il codice ISBN da impostare sul libro
 */
void Libro::updateISBN(string Isbn) {
    isbn = Isbn;
}

/**
 * Restituisce il titolo del libro selezionato
 *
 * @return string titolo del libro selezionato
 */
string Libro::getTitolo() {
    return titolo;
}

/**
 * Restituisce la quantità disponibile del libro selezionato
 *
 * @return int disponibilita del libro selezionato
 */
int Libro::getDisp() {
    return disponibilita;
}

/**
 * Prezzo del libro selezionato.
 *
 * @return double con il prezzo del libro selezionato
 */
double Libro::getPrezzo() {
    return prezzo;
}

/**
 * Modifica il titolo sostituendolo con s.
 *
 * @param s è il nuovo titolo
 */
void Libro::updateTitolo(string s) {
    titolo = s;
}

/**
 * Modifica la disponibilità ponendola UGUALE a n
 * @param n è la quantità della nuova disponibilità
 */
void Libro::modificaDisp(int n) {
    disponibilita = n;
}

/**
 * Aggiorna la disponibilita' del libro, aggiungendo o togliendo nr libri.
 *
 * @param nr è il numero di libri da aggiungere/togliere:
 *   - se positivo (+) i libri verranno aggiunti (la quantità aumenterà)
 *   - se negativo (-) i libri verranno tolti (la quantità diminuirà)
 */
void Libro::updateDisp(int nr) {
    disponibilita += nr;
}

/**
 * Aggiorna il prezzo sostituendolo con p
 *
 * @param p è il nuovo prezzo
 */
void Libro::updatePrezzo(double p) {
    prezzo = p;
}

void Libro::operator=(const Libro& l)
{
    isbn = l.isbn;
    titolo = l.titolo;
    disponibilita = l.disponibilita;
    prezzo = l.prezzo;
}
