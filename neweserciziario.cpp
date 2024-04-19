#include <QtWidgets>
#include "bookstore.h"
#include "neweserciziario.h"
#include "ui_eserciziari.h"
#include "ui_neweserciziario.h"

NewEserciziario::NewEserciziario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewEserciziario)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    ui->OkE->setDisabled(true);

    // Creazione connessione tra campi del "form" da completare e funzione di verifica che i campi non siano vuoti
    connect(ui->isbnLEE, &QLineEdit::textChanged, this, &NewEserciziario::checkFields);
    connect(ui->titoloLEE, &QLineEdit::textChanged, this, &NewEserciziario::checkFields);
    connect(ui->materiaLEE, &QLineEdit::textChanged, this, &NewEserciziario::checkFields);
    connect(ui->prezzoLEE, &QLineEdit::textChanged, this, &NewEserciziario::checkFields);
    connect(ui->nresLEE, &QLineEdit::textChanged, this, &NewEserciziario::checkFields);
    // OK button connection to function
    connect(ui->OkE, &QPushButton::clicked, this, &NewEserciziario::confermaNuovoEserciziario);
}

NewEserciziario::~NewEserciziario()
{
    delete ui;
}

/**
 * Controllo campi non vuoti: se così, il pulsante Ok viene abilitato; altrimenti disabilitato
 */
void NewEserciziario::checkFields()
{
    ui->OkE->setEnabled(!ui->isbnLEE->text().isEmpty() && !ui->titoloLEE->text().isEmpty() && !ui->materiaLEE->text().isEmpty()
                         && !ui->nresLEE->text().isEmpty() && !ui->prezzoLEE->text().isEmpty());
}

/**
 * Conferma creazione libro
 */
void NewEserciziario::confermaNuovoEserciziario()
{
    // Controllo esistenza libro tramite isbn

    if(BookStore::libri->verificaPresenzaLibro(ui->isbnLEE->text().toStdString()))
    {
        // Messaggio di avviso -> suggerimento: modificare solamente la disponibilità
        //                  incrementando il numero di libri del libro desiderato
        QMessageBox::warning(this, "Libro esistente", "Attenzione! Il codice isbn digitato è già associato ad un libro. Verificare la corrispondenza dei dati e aggiornare, se necessario, la disponibilità di quello già esistente.");
        return;
    }
    // Tutto ok: creazione libro lettura
    Eserciziari* nuovo = new Eserciziari(ui->isbnLEE->text().toStdString(),
                                ui->titoloLEE->text().toStdString(),
                                ui->dispLEE->text().toInt() < 0 ? 0 : ui->dispLEE->text().toInt(),
                                ui->prezzoLEE->text().toDouble() < 0.0 ? 0 : ui->prezzoLEE->text().toDouble(),
                                ui->materiaLEE->text().toStdString(),
                                ui->nresLEE->text().toInt() < 0 ? 0 : ui->nresLEE->text().toInt(),
                                ui->diffLEE->text().toInt() > 3 ? 3 : ui->diffLEE->text().toInt());

    // Applica le proprietà del prezzo
    nuovo->calcolaPrezzoTotale(nuovo->getPrezzo());

    // Inserimento nel vettore libri
    BookStore::libri->pushFront(nuovo);

    // Inserimento libro nella tabella
    int rows = Eserciziari::ui->EserciziariTable->rowCount();
    Eserciziari::ui->EserciziariTable->setRowCount(rows + 1);

    Eserciziari::ui->EserciziariTable->setItem(rows, 0, new QTableWidgetItem(QString::fromStdString(nuovo->getISBN())));
    Eserciziari::ui->EserciziariTable->setItem(rows, 1, new QTableWidgetItem(QString::fromStdString(nuovo->getTitolo())));
    Eserciziari::ui->EserciziariTable->setItem(rows, 2, new QTableWidgetItem(QString::fromStdString(nuovo->getMateria())));
    Eserciziari::ui->EserciziariTable->setItem(rows, 3, new QTableWidgetItem(QString::number(nuovo->getDifficolta())));
    Eserciziari::ui->EserciziariTable->setItem(rows, 4, new QTableWidgetItem(QString::number(nuovo->getNrEsercizi())));
    Eserciziari::ui->EserciziariTable->setItem(rows, 5, new QTableWidgetItem(QString::number(nuovo->getPrezzo())));
    Eserciziari::ui->EserciziariTable->setItem(rows, 6, new QTableWidgetItem(QString::number(nuovo->getDisp())));

    // Centra i campi delle righe nella tabella
    for(int j = 0; j < 7; ++j)
    {
        QTableWidgetItem* item = Eserciziari::ui->EserciziariTable->item(rows, j);
        item->setTextAlignment(Qt::AlignCenter);
    }

    // Salvataggio su file
    BookStore::save();

    accept();
}
