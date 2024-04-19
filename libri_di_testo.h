#ifndef LIBRI_DI_TESTO_H
#define LIBRI_DI_TESTO_H

#include <QDialog>
#include "editlibditesto.h"
#include "libro.h"
#include "newlibditesto.h"

/* LIBRI DI TESTO di uso scolastico, rappresentati dai seguenti attributi (ulteriori):
    - materia del libro di testo
    - numero degli argomenti trattati (almeno 1 di default)
    - livello richiesto per l'apprendimento:
        > 0=base/elementare (scuole elementari)
        > 1=intermedio di grado 1 (scuola superiore di I grado)
        > 2=intermedio di grado 2 (scuola superiore di II grado)
        > 3=avanzato/universitario (universita')
    - sconti come studente/docente*/
namespace Ui {
class Libri_Di_Testo;
}

class Libri_Di_Testo : public QDialog, virtual public Libro
{
    Q_OBJECT
    friend class EditLDT;
    friend class NewLDT;
private:
    string materia;
    int nr_argomenti;
    int livello_app;
    double sconto;
public:
    Libri_Di_Testo(string isbn="", string titolo="", int disp=0, double prezzo=0.0, string mat="", int nrArg=1,int lvlApp=-1, double sconto=0.0);
    string getMateria();
    int getNrArgomenti();
    int getLivelloApp();
    double getSconto();
    void updateMateria(string m);
    void updateNrArgomenti(int na);
    void updateLivelloApp(int la);
    void updateSconto(double s);

    // Applicazione della proprietà sul prezzo sui libri di testo
    void calcolaPrezzoTotale(double pp) override;

    explicit Libri_Di_Testo(QWidget *parent = nullptr);
    ~Libri_Di_Testo();

    vector<Libri_Di_Testo*> getLibriDiTesto(vector<Libro*>& libri);

    // Crea QJsonObject per la stampa su file json
    QJsonObject book4Print();

private slots:
    void on_pushButton_LDT_clicked();

    void elementoTabellaLDTCliccato();

    void barraDiRicercaLDT(const QString &arg1);

    void on_pushButton_NewLDT_clicked();

    void on_pushButton_DelLDT_clicked();

    void on_pushButton_AddLDT_clicked();

    void on_pushButton_RemLDT_clicked();

    void on_pushButton_EditLDT_clicked();

private:
    static Ui::Libri_Di_Testo *ui;
    NewLDT *newldt;
    EditLDT *editlibroditesto;
};

#endif // LIBRI_DI_TESTO_H
