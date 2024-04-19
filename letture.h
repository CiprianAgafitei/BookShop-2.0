#ifndef LETTURE_H
#define LETTURE_H

#include <QDialog>
#include "editletture.h"
#include "libro.h"
#include "newletture.h"

/* LIBRi-LETTURA di vari generi testuali, rappresentati dai seguenti attributi (ulteriori):
    - genere del libro (avventura, storico, romantico, SCI-FI, ... )
    - numero delle pagine del libro-lettura
    - numero dei capitoli del libro-lettura
    - copertina flessibile o rigida -> influenza sul calcolo del prezzo: stabilito uno "SCONTO GREEN" (per l'ambiente)
*/
namespace Ui {
class Letture;
}

class Letture : public QDialog, virtual public Libro
{
    Q_OBJECT
    friend class EditLetture;
    friend class NewLetture;
private:
    string genere;
    int nr_pagine;
    bool copertina_flessibile;
public:
    Letture(string isbn="", string titolo="", int disp=0, double prezzo=0.0, string gen="", int pag=0, bool copFlex=false);
    string getGenere();
    int gerNr_pagine();
    bool isCopertinaFlex();
    void updateGenere(string g);
    void updateNrPagine(int np);
    void updateIsCopFlex(bool cp);

    // Applicazione della proprietà sul prezzo sulle letture
    void calcolaPrezzoTotale(double pp) override;

    explicit Letture(QWidget *parent = nullptr);
    ~Letture();

    // Crea QJsonObject per la stampa su file json
    QJsonObject book4Print();

private slots:
    void on_pushButton_L_clicked();

    void on_pushButton_NewL_clicked();

    void on_pushButton_DelL_clicked();

    void on_pushButton_AddL_clicked();

    void on_pushButton_RemL_clicked();

    void on_pushButton_EditL_clicked();

    void elementoTabellaLettureCliccato();

    void barraDiRicercaLettura(const QString &arg1);

private:
    static Ui::Letture *ui;
    NewLetture *newletture;
    EditLetture *editletture;
};

#endif // LETTURE_H
