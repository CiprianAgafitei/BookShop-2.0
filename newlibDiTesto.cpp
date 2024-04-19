#include <QtWidgets>
#include "bookstore.h"
#include "newlibditesto.h"
#include "ui_libri_di_testo.h"
#include "ui_newlibDiTesto.h"

NewLDT::NewLDT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewLDT)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    ui->OkLDT->setDisabled(true);

    // Creazione connessione tra campi del "form" da completare e funzione di verifica che i campi non siano vuoti
    connect(ui->isbnLELDT, &QLineEdit::textChanged, this, &NewLDT::checkFields);
    connect(ui->titoloLELDT, &QLineEdit::textChanged, this, &NewLDT::checkFields);
    connect(ui->materiaLELDT, &QLineEdit::textChanged, this, &NewLDT::checkFields);
    connect(ui->argLELDT, &QLineEdit::textChanged, this, &NewLDT::checkFields);
    connect(ui->prezzoLELDT, &QLineEdit::textChanged, this, &NewLDT::checkFields);
    connect(ui->scontoLELDT, &QLineEdit::textChanged, this, &NewLDT::checkFields);
    // OK button connection
    connect(ui->OkLDT, &QPushButton::clicked, this, &NewLDT::confermaNuovoLDT);
}

NewLDT::~NewLDT()
{
    delete ui;
}

/**
 * Controllo campi non vuoti: se così, il pulsante Ok viene abilitato; altrimenti disabilitato
 */
void NewLDT::checkFields()
{
    ui->OkLDT->setEnabled(!ui->isbnLELDT->text().isEmpty() && !ui->titoloLELDT->text().isEmpty() && !ui->materiaLELDT->text().isEmpty()
                         && !ui->argLELDT->text().isEmpty() && !ui->prezzoLELDT->text().isEmpty() && !ui->scontoLELDT->text().isEmpty());
}

/**
 * Conferma creazione libro
 */
void NewLDT::confermaNuovoLDT()
{
    // Controllo esistenza libro tramite isbn

    if(BookStore::libri->verificaPresenzaLibro(ui->isbnLELDT->text().toStdString()))
    {
        // Messaggio di avviso -> suggerimento: modificare solamente la disponibilità
        //                  incrementando il numero di libri del libro desiderato
        QMessageBox::warning(this, "Libro esistente", "Attenzione! Il codice isbn digitato è già associato ad un libro. Verificare la corrispondenza dei dati e aggiornare, se necessario, la disponibilità di quello già esistente.");
        return;
    }
    // Tutto ok: creazione libro lettura
    Libri_Di_Testo* nuovo = new Libri_Di_Testo(ui->isbnLELDT->text().toStdString(),
                                ui->titoloLELDT->text().toStdString(),
                                ui->spinBox->text().toInt() < 0 ? 0 : ui->spinBox->text().toInt(),
                                ui->prezzoLELDT->text().toDouble() < 0.0 ? 0 : ui->prezzoLELDT->text().toDouble(),
                                ui->materiaLELDT->text().toStdString(),
                                ui->argLELDT->text().toInt() <= 0 ? 1 : ui->argLELDT->text().toInt(),
                                ui->spinBox_2->text().toInt() > 3 ? 3 : ui->spinBox_2->text().toInt(),
                                ui->scontoLELDT->text().toDouble());

    // Applica le proprietà del prezzo
    nuovo->calcolaPrezzoTotale(nuovo->getPrezzo());

    // Inserimento nel vettore libri
    BookStore::libri->pushFront(nuovo);

    // Inserimento libro nella tabella
    int rows = Libri_Di_Testo::ui->LDTTable->rowCount();
    Libri_Di_Testo::ui->LDTTable->setRowCount(rows + 1);

    Libri_Di_Testo::ui->LDTTable->setItem(rows, 0, new QTableWidgetItem(QString::fromStdString(nuovo->getISBN())));
    Libri_Di_Testo::ui->LDTTable->setItem(rows, 1, new QTableWidgetItem(QString::fromStdString(nuovo->getTitolo())));
    Libri_Di_Testo::ui->LDTTable->setItem(rows, 2, new QTableWidgetItem(QString::fromStdString(nuovo->getMateria())));
    Libri_Di_Testo::ui->LDTTable->setItem(rows, 3, new QTableWidgetItem(QString::number(nuovo->getNrArgomenti())));
    Libri_Di_Testo::ui->LDTTable->setItem(rows, 4, new QTableWidgetItem(QString::number(nuovo->getLivelloApp())));
    Libri_Di_Testo::ui->LDTTable->setItem(rows, 5, new QTableWidgetItem(QString::number(nuovo->getPrezzo())));
    Libri_Di_Testo::ui->LDTTable->setItem(rows, 6, new QTableWidgetItem(QString::number(nuovo->getDisp())));
    Libri_Di_Testo::ui->LDTTable->setItem(rows, 7, new QTableWidgetItem(QString::number(nuovo->getSconto())));

    // Centra i campi della riga
    for(int j = 0; j < 8; ++j)
    {
        QTableWidgetItem* item = Libri_Di_Testo::ui->LDTTable->item(rows, j);
        item->setTextAlignment(Qt::AlignCenter);
    }

    // Salvataggio su file
    BookStore::save();

    accept();
}
