#include <QtWidgets>
#include "bookstore.h"
#include "editletture.h"
#include "ui_editletture.h"
#include "ui_letture.h"

EditLetture::EditLetture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLetture)
{
    // Dimensioni finestra non modificabili
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    // Ottenimento delle informazioni dell'oggetto selezionato nella tabella
    QModelIndexList selectedIndexes = Letture::ui->LettureTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento informazioni del libro lettura selezionato nella tabella
    QVariant isbn = Letture::ui->LettureTable->model()->data(Letture::ui->LettureTable->model()->index(selectedIndex.row(), 0));
    QVariant titolo = Letture::ui->LettureTable->model()->data(Letture::ui->LettureTable->model()->index(selectedIndex.row(), 1));
    QVariant genere = Letture::ui->LettureTable->model()->data(Letture::ui->LettureTable->model()->index(selectedIndex.row(), 2));
    QVariant pagine = Letture::ui->LettureTable->model()->data(Letture::ui->LettureTable->model()->index(selectedIndex.row(), 3));
    QVariant prezzo = Letture::ui->LettureTable->model()->data(Letture::ui->LettureTable->model()->index(selectedIndex.row(), 4));
    QVariant disp = Letture::ui->LettureTable->model()->data(Letture::ui->LettureTable->model()->index(selectedIndex.row(), 5));
    QVariant copflex = Letture::ui->LettureTable->model()->data(Letture::ui->LettureTable->model()->index(selectedIndex.row(), 6));

    // Imposta i valori dei campi dell'oggetto selezionato sui campi modificabili dall'utente
    ui->isbnLEL->setText(isbn.toString());
    ui->titoloLEL->setText(titolo.toString());
    ui->genereLEL->setText(genere.toString());
    ui->pagineLEL->setText(pagine.toString());
    ui->prezzoLEL->setText(prezzo.toString());
    ui->dispL->setValue(disp.toInt());
    ui->copflexL->setChecked(copflex.toString() == "SI" ? true : false);

    // Creazione connessione tra campi del "form" da completare e funzione di verifica che i campi non siano vuoti
    connect(ui->isbnLEL, &QLineEdit::textChanged, this, &EditLetture::checkFields);
    connect(ui->titoloLEL, &QLineEdit::textChanged, this, &EditLetture::checkFields);
    connect(ui->genereLEL, &QLineEdit::textChanged, this, &EditLetture::checkFields);
    connect(ui->pagineLEL, &QLineEdit::textChanged, this, &EditLetture::checkFields);
    connect(ui->prezzoLEL, &QLineEdit::textChanged, this, &EditLetture::checkFields);
    // OK button connection
    connect(ui->OkL, &QPushButton::clicked, this, &EditLetture::confermaModificaLettura);
}

EditLetture::~EditLetture()
{
    delete ui;
}

/**
 * Controllo campi non vuoti: se così, il pulsante Ok viene abilitato; altrimenti disabilitato
 */
void EditLetture::checkFields()
{
    ui->OkL->setEnabled(!ui->isbnLEL->text().isEmpty() && !ui->titoloLEL->text().isEmpty() && !ui->genereLEL->text().isEmpty()
                         && !ui->pagineLEL->text().isEmpty() && !ui->prezzoLEL->text().isEmpty());
}

/**
 * Conferma creazione libro
 */
void EditLetture::confermaModificaLettura()
{
    // Modifica dati libro-lettura nel vettore dei libri tramite codice isbn (univoco, non modificabile):
    for(int i = 0; i < BookStore::libri->size(); i++)
    {
        // Individuazione libro da aggiornare
        if(BookStore::libri->get(i)->getISBN() == ui->isbnLEL->text().toStdString())
        {
            Letture *lettura = dynamic_cast<Letture*>(BookStore::libri->get(i));

            // Modifica campi del libro-lettura nel vettore
            lettura->updateTitolo(ui->titoloLEL->text().toStdString());
            lettura->updateGenere(ui->genereLEL->text().toStdString());
            lettura->updateNrPagine(ui->pagineLEL->text().toInt());
            lettura->modificaDisp(ui->dispL->text().toInt());
            lettura->updatePrezzo(ui->prezzoLEL->text().toDouble());
            lettura->updateIsCopFlex(ui->copflexL->isChecked());

            // Ottenimento indice tabella relativo alla riga selezionata
            QModelIndexList selectedIndexes = Letture::ui->LettureTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)
            QModelIndex selectedIndex = selectedIndexes.at(0);

            // Modifica dati nella tabella
            Letture::ui->LettureTable->item(selectedIndex.row(), 1)->setText(QString::fromStdString(lettura->getTitolo()));
            Letture::ui->LettureTable->item(selectedIndex.row(), 2)->setText(QString::fromStdString(lettura->getGenere()));
            Letture::ui->LettureTable->item(selectedIndex.row(), 3)->setText(QString::number(lettura->gerNr_pagine()));
            Letture::ui->LettureTable->item(selectedIndex.row(), 4)->setText(QString::number(lettura->getPrezzo()));
            Letture::ui->LettureTable->item(selectedIndex.row(), 5)->setText(QString::number(lettura->getDisp()));
            Letture::ui->LettureTable->item(selectedIndex.row(), 6)->setText(lettura->isCopertinaFlex() == true ? "SI" : "NO");

            break;  // uscita dal for
        }
    }
    // Salvataggio su file del vettore libri
    BookStore::save();

    accept();
}
