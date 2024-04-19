#ifndef ESERCIZIARI_H
#define ESERCIZIARI_H

#include <QDialog>
#include <cmath>
#include "editeserciziario.h"
#include "libro.h"
#include "neweserciziario.h"

/* LIBRO-ESERCIZIARIO rappresentato dai seguenti attributi (ulteriori):
    - materia dell'eserciziario
    - numero degli esercizi presenti        (default -1 = nessuno)
    - grado di difficoltà degli esercizi:   (default 0)
        > 1=principiante
        > 2=intermedio
        > 3=avanzato */
namespace Ui {
class Eserciziari;
}

class Eserciziari : public QDialog, virtual public Libro
{
    Q_OBJECT
    friend class EditEserciziario;
    friend class NewEserciziario;
private:
    string materia;
    int nr_esercizi;
    int difficolta;
public:
    Eserciziari(string isbn="", string titolo="", int disp=0, double prezzo=0.0, string mat="", int nr_ex=-1, int diff=0);
    string getMateria();
    int getNrEsercizi();
    int getDifficolta();
    void updateMateria(string m);
    void updateNrEsercizi(int nre);
    void updateDiff(int d);

    // Applicazione della proprietà sul prezzo sugli eserciziari
    void calcolaPrezzoTotale(double pp) override;

    explicit Eserciziari(QWidget *parent = nullptr);
    ~Eserciziari();

    // Crea QJsonObject per la stampa su file json
    QJsonObject book4Print();

    // Inserisci eserciziari nella tabella
    void inserisciEserciziari(vector<Eserciziari*>& eserciziari);

private slots:
    void on_pushButton_E_clicked();

    void elementoTabellaEserciziariCliccato();

    void barraDiRicercaEserciziario(const QString &arg1);

    void on_pushButton_NewE_clicked();

    void on_pushButton_DelE_clicked();

    void on_pushButton_AddE_clicked();

    void on_pushButton_RemE_clicked();

    void on_pushButton_EditE_clicked();

private:
    static Ui::Eserciziari *ui;
    NewEserciziario *neweserciziario;
    EditEserciziario *editeserciziario;
};

#endif // ESERCIZIARI_H
