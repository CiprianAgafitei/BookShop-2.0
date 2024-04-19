#include <QtWidgets>
#include "bookstore.h"
#include "editlibditesto.h"
#include "ui_editlibDiTesto.h"
#include "ui_libri_di_testo.h"

EditLDT::EditLDT(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLDT)
{
    // Dimensioni finestra non modificabili
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    // Ottenimento delle informazioni dell'oggetto selezionato nella tabella
    QModelIndexList selectedIndexes = Libri_Di_Testo::ui->LDTTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)
    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento dati del libro di testo della riga selezionata
    QVariant isbn = Libri_Di_Testo::ui->LDTTable->model()->data(Libri_Di_Testo::ui->LDTTable->model()->index(selectedIndex.row(), 0));
    QVariant titolo = Libri_Di_Testo::ui->LDTTable->model()->data(Libri_Di_Testo::ui->LDTTable->model()->index(selectedIndex.row(), 1));
    QVariant materia = Libri_Di_Testo::ui->LDTTable->model()->data(Libri_Di_Testo::ui->LDTTable->model()->index(selectedIndex.row(), 2));
    QVariant nrarg = Libri_Di_Testo::ui->LDTTable->model()->data(Libri_Di_Testo::ui->LDTTable->model()->index(selectedIndex.row(), 3));
    QVariant lvlapp = Libri_Di_Testo::ui->LDTTable->model()->data(Libri_Di_Testo::ui->LDTTable->model()->index(selectedIndex.row(), 4));
    QVariant prezzo = Libri_Di_Testo::ui->LDTTable->model()->data(Libri_Di_Testo::ui->LDTTable->model()->index(selectedIndex.row(), 5));
    QVariant disp = Libri_Di_Testo::ui->LDTTable->model()->data(Libri_Di_Testo::ui->LDTTable->model()->index(selectedIndex.row(), 6));
    QVariant sconto = Libri_Di_Testo::ui->LDTTable->model()->data(Libri_Di_Testo::ui->LDTTable->model()->index(selectedIndex.row(), 7));

    // Imposta i valori dei campi dell'oggetto selezionato sui campi modificabili dall'utente
    ui->isbnLELDT->setText(isbn.toString());
    ui->titoloLELDT->setText(titolo.toString());
    ui->materiaLELDT->setText(materia.toString());
    ui->argLELDT->setText(nrarg.toString());
    ui->spinBox_2->setValue(lvlapp.toInt());    // Lvl. apprendimento
    ui->prezzoLELDT->setText(prezzo.toString());
    ui->spinBox->setValue(disp.toInt());        // Disponibilità
    ui->scontoLELDT->setText(sconto.toString());

    // Creazione connessione tra campi del "form" da completare e funzione di verifica che i campi non siano vuoti
    connect(ui->isbnLELDT, &QLineEdit::textChanged, this, &EditLDT::checkFields);
    connect(ui->titoloLELDT, &QLineEdit::textChanged, this, &EditLDT::checkFields);
    connect(ui->materiaLELDT, &QLineEdit::textChanged, this, &EditLDT::checkFields);
    connect(ui->argLELDT, &QLineEdit::textChanged, this, &EditLDT::checkFields);
    connect(ui->prezzoLELDT, &QLineEdit::textChanged, this, &EditLDT::checkFields);
    connect(ui->scontoLELDT, &QLineEdit::textChanged, this, &EditLDT::checkFields);
    // OK button connection
    connect(ui->OkLDT, &QPushButton::clicked, this, &EditLDT::confermaModificaLDT);
}

EditLDT::~EditLDT()
{
    delete ui;
}

/**
 * Controllo campi non vuoti: se così, il pulsante Ok viene abilitato; altrimenti disabilitato
 */
void EditLDT::checkFields()
{
    ui->OkLDT->setEnabled(!ui->isbnLELDT->text().isEmpty() && !ui->titoloLELDT->text().isEmpty() && !ui->materiaLELDT->text().isEmpty()
                         && !ui->argLELDT->text().isEmpty() && !ui->prezzoLELDT->text().isEmpty() && !ui->scontoLELDT->text().isEmpty());
}

/**
 * Conferma creazione libro
 */
void EditLDT::confermaModificaLDT()
{
    // Modifica dati libro-lettura nel vettore dei libri tramite codice isbn (univoco, non modificabile):
    for(int i = 0; i < BookStore::libri->size(); i++)
    {
        // Individuazione libro da aggiornare
        if(BookStore::libri->get(i)->getISBN() == ui->isbnLELDT->text().toStdString())
        {
            Libri_Di_Testo *ldt = dynamic_cast<Libri_Di_Testo*>(BookStore::libri->get(i));

            // Modifica campi del libro-lettura nel vettore
            ldt->updateTitolo(ui->titoloLELDT->text().toStdString());
            ldt->updateMateria(ui->materiaLELDT->text().toStdString());
            ldt->updateNrArgomenti(ui->argLELDT->text().toInt());
            ldt->updateLivelloApp(ui->spinBox_2->text().toInt());
            ldt->updatePrezzo(ui->prezzoLELDT->text().toDouble());
            ldt->modificaDisp(ui->spinBox->text().toInt());
            ldt->updateSconto(ui->scontoLELDT->text().toDouble());

            // Ottenimento indice tabella relativo alla riga selezionata
            QModelIndexList selectedIndexes = Libri_Di_Testo::ui->LDTTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)
            QModelIndex selectedIndex = selectedIndexes.at(0);

            // Modifica dati nella tabella
            Libri_Di_Testo::ui->LDTTable->item(selectedIndex.row(), 1)->setText(QString::fromStdString(ldt->getTitolo()));
            Libri_Di_Testo::ui->LDTTable->item(selectedIndex.row(), 2)->setText(QString::fromStdString(ldt->getMateria()));
            Libri_Di_Testo::ui->LDTTable->item(selectedIndex.row(), 3)->setText(QString::number(ldt->getNrArgomenti()));
            Libri_Di_Testo::ui->LDTTable->item(selectedIndex.row(), 4)->setText(QString::number(ldt->getLivelloApp()));
            Libri_Di_Testo::ui->LDTTable->item(selectedIndex.row(), 5)->setText(QString::number(ldt->getPrezzo()));
            Libri_Di_Testo::ui->LDTTable->item(selectedIndex.row(), 6)->setText(QString::number(ldt->getDisp()));
            Libri_Di_Testo::ui->LDTTable->item(selectedIndex.row(), 7)->setText(QString::number(ldt->getSconto()));

            break;  // uscita dal for
        }
    }
    // Salvataggio su file
    BookStore::save();

    accept();
}
