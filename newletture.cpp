#include <QtWidgets>
#include "bookstore.h"
#include "newletture.h"
#include "ui_letture.h"
#include "ui_newletture.h"

NewLetture::NewLetture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewLetture)
{
    // Dimensioni finestra non modificabili
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    ui->OkL->setDisabled(true);

    // Creazione connessione tra campi del "form" da completare e funzione di verifica che i campi non siano vuoti
    connect(ui->isbnLEL, &QLineEdit::textChanged, this, &NewLetture::checkFields);
    connect(ui->titoloLEL, &QLineEdit::textChanged, this, &NewLetture::checkFields);
    connect(ui->genereLEL, &QLineEdit::textChanged, this, &NewLetture::checkFields);
    connect(ui->pagineLEL, &QLineEdit::textChanged, this, &NewLetture::checkFields);
    connect(ui->prezzoLEL, &QLineEdit::textChanged, this, &NewLetture::checkFields);
    // OK button connection
    connect(ui->OkL, &QPushButton::clicked, this, &NewLetture::confermaNuovaLettura);
}

NewLetture::~NewLetture()
{
    delete ui;
}

/**
 * Controllo campi non vuoti: se così, il pulsante Ok viene abilitato; altrimenti disabilitato
 */
void NewLetture::checkFields()
{
    ui->OkL->setEnabled(!ui->isbnLEL->text().isEmpty() && !ui->titoloLEL->text().isEmpty() && !ui->genereLEL->text().isEmpty()
                         && !ui->pagineLEL->text().isEmpty() && !ui->prezzoLEL->text().isEmpty());
}

/**
 * Conferma creazione libro
 */
void NewLetture::confermaNuovaLettura()
{
    // Controllo esistenza libro tramite isbn

    if(BookStore::libri->verificaPresenzaLibro(ui->isbnLEL->text().toStdString()))
    {
        // Messaggio di avviso -> suggerimento: modificare solamente la disponibilità
        //                  incrementando il numero di libri del libro desiderato
        QMessageBox::warning(this, "Libro esistente", "Attenzione! Il codice isbn digitato è già associato ad un libro. Verificare la corrispondenza dei dati e aggiornare, se necessario, la disponibilità di quello già esistente.");
        return;
    }
    // Tutto ok: creazione libro lettura
    Letture* nuovo = new Letture(ui->isbnLEL->text().toStdString(),
                                ui->titoloLEL->text().toStdString(),
                                ui->dispL->text().toInt() < 0 ? 0 : ui->dispL->text().toInt(),
                                ui->prezzoLEL->text().toDouble() < 0.0 ? 0 : ui->prezzoLEL->text().toDouble(),
                                ui->genereLEL->text().toStdString(),
                                ui->pagineLEL->text().toInt() < 0 ? 0 : ui->pagineLEL->text().toInt(),
                                ui->copflexL->isChecked());

    // Applica le proprietà del prezzo
    nuovo->calcolaPrezzoTotale(nuovo->getPrezzo());

    // Inserimento nel vettore libri
    BookStore::libri->pushFront(nuovo);

    // Inserimento libro nella tabella
    int rows = Letture::ui->LettureTable->rowCount();
    Letture::ui->LettureTable->setRowCount(rows + 1);

    Letture::ui->LettureTable->setItem(rows, 0, new QTableWidgetItem(QString::fromStdString(nuovo->getISBN())));
    Letture::ui->LettureTable->setItem(rows, 1, new QTableWidgetItem(QString::fromStdString(nuovo->getTitolo())));
    Letture::ui->LettureTable->setItem(rows, 2, new QTableWidgetItem(QString::fromStdString(nuovo->getGenere())));
    Letture::ui->LettureTable->setItem(rows, 3, new QTableWidgetItem(QString::number(nuovo->gerNr_pagine())));
    Letture::ui->LettureTable->setItem(rows, 4, new QTableWidgetItem(QString::number(nuovo->getPrezzo())));
    Letture::ui->LettureTable->setItem(rows, 5, new QTableWidgetItem(QString::number(nuovo->getDisp())));
    Letture::ui->LettureTable->setItem(rows, 6, new QTableWidgetItem(nuovo->isCopertinaFlex() == true ? "SI" : "NO"));

    // Centra i campi delle righe nella tabella
    for(int j = 0; j < 7; ++j)
    {
        QTableWidgetItem* item = Letture::ui->LettureTable->item(rows, j);
        item->setTextAlignment(Qt::AlignCenter);
    }

    // Salvataggio su file del vettore libri
    BookStore::save();

    accept();
}
