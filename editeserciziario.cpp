#include <QtWidgets>
#include "bookstore.h"
#include "editeserciziario.h"
#include "ui_editeserciziario.h"
#include "ui_eserciziari.h"

EditEserciziario::EditEserciziario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditEserciziario)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    // Ottenimento delle informazioni dell'oggetto selezionato nella tabella
    QModelIndexList selectedIndexes = Eserciziari::ui->EserciziariTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)
    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento delle informazioni dell'eserciziario selezionato nella tabella
    QVariant isbn = Eserciziari::ui->EserciziariTable->model()->data(Eserciziari::ui->EserciziariTable->model()->index(selectedIndex.row(), 0));
    QVariant titolo = Eserciziari::ui->EserciziariTable->model()->data(Eserciziari::ui->EserciziariTable->model()->index(selectedIndex.row(), 1));
    QVariant materia = Eserciziari::ui->EserciziariTable->model()->data(Eserciziari::ui->EserciziariTable->model()->index(selectedIndex.row(), 2));
    QVariant diff = Eserciziari::ui->EserciziariTable->model()->data(Eserciziari::ui->EserciziariTable->model()->index(selectedIndex.row(), 3));
    QVariant nrex = Eserciziari::ui->EserciziariTable->model()->data(Eserciziari::ui->EserciziariTable->model()->index(selectedIndex.row(), 4));
    QVariant prezzo = Eserciziari::ui->EserciziariTable->model()->data(Eserciziari::ui->EserciziariTable->model()->index(selectedIndex.row(), 5));
    QVariant disp = Eserciziari::ui->EserciziariTable->model()->data(Eserciziari::ui->EserciziariTable->model()->index(selectedIndex.row(), 6));

    // Imposta i valori dei campi dell'oggetto selezionato sui campi modificabili dall'utente
    ui->isbnLEE->setText(isbn.toString());
    ui->titoloLEE->setText(titolo.toString());
    ui->materiaLEE->setText(materia.toString());
    ui->diffLEE->setValue(diff.toInt());
    ui->nresLEE->setText(nrex.toString());
    ui->prezzoLEE->setText(prezzo.toString());
    ui->dispLEE->setValue(disp.toInt());

    // Creazione connessione tra campi del "form" da completare e funzione di verifica che i campi non siano vuoti
    connect(ui->isbnLEE, &QLineEdit::textChanged, this, &EditEserciziario::checkFields);
    connect(ui->titoloLEE, &QLineEdit::textChanged, this, &EditEserciziario::checkFields);
    connect(ui->materiaLEE, &QLineEdit::textChanged, this, &EditEserciziario::checkFields);
    connect(ui->prezzoLEE, &QLineEdit::textChanged, this, &EditEserciziario::checkFields);
    connect(ui->nresLEE, &QLineEdit::textChanged, this, &EditEserciziario::checkFields);
    // OK button connection
    connect(ui->OkE, &QPushButton::clicked, this, &EditEserciziario::confermaModificaEserciziario);
}

EditEserciziario::~EditEserciziario()
{
    delete ui;
}

/**
 * Controllo campi non vuoti: se così, il pulsante Ok viene abilitato; altrimenti disabilitato
 */
void EditEserciziario::checkFields()
{
    ui->OkE->setEnabled(!ui->isbnLEE->text().isEmpty() && !ui->titoloLEE->text().isEmpty() && !ui->materiaLEE->text().isEmpty()
                         && !ui->nresLEE->text().isEmpty() && !ui->prezzoLEE->text().isEmpty());
}

/**
 * Conferma creazione libro
 */
void EditEserciziario::confermaModificaEserciziario()
{
    // Modifica dati libro-lettura nel vettore dei libri tramite codice isbn (univoco, non modificabile):
    for(int i = 0; i < BookStore::libri->size(); i++)
    {
        // Individuazione libro da aggiornare
        if(BookStore::libri->get(i)->getISBN() == ui->isbnLEE->text().toStdString())
        {
            Eserciziari *lettura = dynamic_cast<Eserciziari*>(BookStore::libri->get(i));

            // Modifica campi del libro-lettura nel vettore
            lettura->updateTitolo(ui->titoloLEE->text().toStdString());
            lettura->updateMateria(ui->materiaLEE->text().toStdString());
            lettura->updateDiff(ui->diffLEE->text().toInt());
            lettura->updateNrEsercizi(ui->nresLEE->text().toInt());
            lettura->updatePrezzo(ui->prezzoLEE->text().toDouble());
            lettura->modificaDisp(ui->dispLEE->text().toInt());

            // Ottenimento indice tabella relativo alla riga selezionata
            QModelIndexList selectedIndexes = Eserciziari::ui->EserciziariTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)
            QModelIndex selectedIndex = selectedIndexes.at(0);

            // Modifica dati nella tabella
            Eserciziari::ui->EserciziariTable->item(selectedIndex.row(), 1)->setText(QString::fromStdString(lettura->getTitolo()));
            Eserciziari::ui->EserciziariTable->item(selectedIndex.row(), 2)->setText(QString::fromStdString(lettura->getMateria()));
            Eserciziari::ui->EserciziariTable->item(selectedIndex.row(), 3)->setText(QString::number(lettura->getDifficolta()));
            Eserciziari::ui->EserciziariTable->item(selectedIndex.row(), 4)->setText(QString::number(lettura->getNrEsercizi()));
            Eserciziari::ui->EserciziariTable->item(selectedIndex.row(), 5)->setText(QString::number(lettura->getPrezzo()));
            Eserciziari::ui->EserciziariTable->item(selectedIndex.row(), 6)->setText(QString::number(lettura->getDisp()));

            break;  // uscita dal for
        }
    }
    // Salvataggio su file del vettore libri
    BookStore::save();

    accept();
}
