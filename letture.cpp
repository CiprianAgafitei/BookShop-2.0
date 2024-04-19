#include <QtWidgets>
#include "letture.h"
#include "bookstore.h"
#include "ui_letture.h"
#include "mainmenu.h"

Letture::Letture(QWidget *parent) :
    QDialog(parent)
{
    // Dimensioni della finestra non modificabili
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    // Rende i campi della tabella non editabili
    ui->LettureTable->setEditTriggers(QTableWidget::NoEditTriggers);

    lista_sl* books = BookStore::getLibri();

    vector<Letture*> letture = books->getLetture();

    if(letture.size() > 0)
    {
        ui->LettureTable->setRowCount(static_cast<int>(letture.size()));

        int row = 0;
        for (Letture* l : letture) {
            ui->LettureTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(l->isbn)));
            ui->LettureTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(l->titolo)));
            ui->LettureTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(l->genere)));
            ui->LettureTable->setItem(row, 3, new QTableWidgetItem(QString::number(l->nr_pagine)));
            ui->LettureTable->setItem(row, 4, new QTableWidgetItem(QString::number(l->prezzo)));
            ui->LettureTable->setItem(row, 5, new QTableWidgetItem(QString::number(l->disponibilita)));
            ui->LettureTable->setItem(row, 6, new QTableWidgetItem(l->copertina_flessibile ? "SI" : "NO"));
            ++row;
        }
    }

    // Centra i campi delle righe nella tabella
    for (int row = 0; row < ui->LettureTable->rowCount(); ++row)
    {
        for(int j = 0; j < 7; ++j)
        {
            QTableWidgetItem* item = ui->LettureTable->item(row, j);
            item->setTextAlignment(Qt::AlignCenter);
        }
    }

    // Nessuna riga selezionata => opzioni di modifica nascoste
    ui->pushButton_DelL->hide();
    ui->pushButton_AddL->hide();
    ui->pushButton_RemL->hide();
    ui->pushButton_EditL->hide();

    // Connect the textChanged signal of the line edit to a slot
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &Letture::barraDiRicercaLettura);
    connect(ui->LettureTable, &QTableWidget::clicked, this, &Letture::elementoTabellaLettureCliccato);
}

Ui::Letture *Letture::ui = new Ui::Letture;

Letture::~Letture()
{
    delete ui;
}

void Letture::on_pushButton_L_clicked()
{
    hide();
    MainMenu *mainMenu = new MainMenu(this);
    mainMenu->show();
}

Letture::Letture(string isbn, string titolo, int disp, double prezzo, string gen, int pag, bool copFlex) : Libro(isbn, titolo, disp, prezzo), genere(gen), nr_pagine(pag), copertina_flessibile(copFlex) {}

/**
 * Indica il genere del libro selezionato
 *
 * @return string genere del libro
 */
string Letture::getGenere() {
    return genere;
}

/**
 * Indica il numero delle pagine del libro selezionato
 *
 * @return int numero delle pagine del libro
 */
int Letture::gerNr_pagine() {
    return nr_pagine;
}

/**
 * Indica de il libro ha copertina flessibile (true), cioè se è disponibile in forma cartacea, oppure
 * se ha copertina rigida (false), cioè se è dispobinile in forma digitale
 *
 * @return true se ha copertina flessibile
 * @return false se ha copertina digitale
 */
bool Letture::isCopertinaFlex() {
    return copertina_flessibile;
}

/**
 * Aggiorna il genere del libro-lettura con quello passato da parametro
 *
 * @param g è il nuovo genere aggiornato, del libro
 */
void Letture::updateGenere(string g) {
    genere = g;
}

/**
 * Aggiorna il numero delle pagine del libro-lettura
 *
 * @param np è il nuovo numero delle pagine del libro
 */
void Letture::updateNrPagine(int np) {
    nr_pagine = np;
}

/**
 * Aggiorna lo stato di copertina flessibile del libro-lettura
 *
 * @param cp è il nuovo stato del libro
 */
void Letture::updateIsCopFlex(bool cp) {
    copertina_flessibile = cp;
}

/**
 * Crea oggetto QJsonObject per la stampa su file json
 * @return un oggetto QJsonObject con le caratteristiche del libro
 */
QJsonObject Letture::book4Print() {
    QJsonObject book;
    book.insert("type", "lettura");
    book.insert("isbn", isbn.c_str());
    book.insert("titolo", titolo.c_str());
    book.insert("disponibilita", disponibilita);
    book.insert("prezzo", prezzo);
    book.insert("genere", genere.c_str());
    book.insert("nr_pagine", nr_pagine);
    book.insert("copertina_flessibile", copertina_flessibile);
    return book;
}

/**
 * Creazione di un nuovo libro della categoria letture da inserire
 *      |           |           |           |           |
 *      V           V           V           V           V
 * Mostra la finestra per l'inserimento dei dati di una letture
 */
void Letture::on_pushButton_NewL_clicked()
{
    newletture = new NewLetture(this);
    newletture->exec();     // Show the new window and disable current one
}

/**
 * Elimina il libro selezionato -> disponibile solo se la quantità è pari a 0
 */
void Letture::on_pushButton_DelL_clicked()
{
    QModelIndexList selectedIndexes = ui->LettureTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 5) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value_disp = ui->LettureTable->model()->data(ui->LettureTable->model()->index(selectedIndex.row(), 5));

    // Controllo disponibilità nulla
    if(value_disp.toInt() == 0)
    {
        // MESSAGGIO di richiesta conferma per la rimozione
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Avviso", "Sei sicuro di voler eliminare il libro selezionato?", QMessageBox::Yes|QMessageBox::No);

        // Controllo scelta ed eliminazione del libro dalla tabella, se scelta positiva
        if (reply == QMessageBox::Yes)
        {
            QVariant value = ui->LettureTable->model()->data(selectedIndex);   // Ottenimento isbn libro da rimuovere

            // Rimozione dall'elenco dei libri
            BookStore::libri->pop(value.toString().toStdString());

            // Rimozione della riga selezionata dalla tabella
            ui->LettureTable->removeRow(selectedIndex.row());

            // Salvataggio su file dell'elenco dei libri aggiornati
            BookStore::save();
        }
    }
    else    // Disponibilità > 0
    {
        QMessageBox::warning(this, "Attenzione!", "Non è possibile rimuovere il libro selezionato in quanto la sua disponibilità non è ancora nulla.");
    }
}

/**
 * Aggiungi libri aggiornando laquantità dei libri lettura
 */
void Letture::on_pushButton_AddL_clicked()
{
    QModelIndexList selectedIndexes = ui->LettureTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 5) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value_disp = ui->LettureTable->model()->data(ui->LettureTable->model()->index(selectedIndex.row(), 5));

    QVariant value = ui->LettureTable->model()->data(selectedIndex);   // Ottenimento isbn libro da inserire

    // Modifica dei dati relativi al libro nella tabella
    ui->LettureTable->item(selectedIndex.row(), 5)->setText(QString::number(value_disp.toInt() + 1));

    // Aggiornamento della disponibilità del libro nel vettore
    BookStore::libri->aggiornaDisp(value.toString().toStdString(), 1);        // Quantità da aggiungere alla disponibilità corrente

    // Messaggio di modifica avvenuto con successo
    QMessageBox::information(this, "Avviso", "1 libro inserito con successo!");

    // Salvataggio su file delle modifiche apportate
    BookStore::save();
}

/**
 * Rimuovi 1 libro aggiornando la quantità dei libri lettura rimasti -> disponibile solo se la quantità è > 0
 */
void Letture::on_pushButton_RemL_clicked()
{
    QModelIndexList selectedIndexes = ui->LettureTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 5) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value_disp = ui->LettureTable->model()->data(ui->LettureTable->model()->index(selectedIndex.row(), 5));

    // Controllo disponibilità non nulla
    if(value_disp.toInt() > 0)
    {
        QVariant value = ui->LettureTable->model()->data(selectedIndex);   // Ottenimento isbn libro da rimuovere

        // Rimozione di 1 libro -> aggiornamento della disponibilità del libro selezionato

        // Modifica dei dati relativi al libro nella tabella (quantità)
        ui->LettureTable->item(selectedIndex.row(), 5)->setText(QString::number(value_disp.toInt() - 1));

        // Aggiornamento della disponibilità del libro nel vettore
        BookStore::libri->aggiornaDisp(value.toString().toStdString(), -1);        // Quantità da aggiungere alla disponibilità corrente

        // Messaggio di modifica avvenuto con successo
        QMessageBox::information(this, "Avviso", "Libro rimosso con successo!");

        // Salvataggio modifiche su file
        BookStore::save();
    }
    else    // Disponibilità terminata
    {
        QMessageBox::warning(this, "Attenzione!", "La disponibilità del libro selezionato è esaurita.");
    }
}

/**
 * Rende modificabili i campi del libro della riga della tabella selezionata
 */
void Letture::on_pushButton_EditL_clicked()
{
    // Modifica dei campi dell'oggetto selezionato
    editletture = new EditLetture(this);
    editletture->exec();
}

void Letture::elementoTabellaLettureCliccato()
{
    // Mostra le opzioni per la riga selezioanata
    ui->pushButton_DelL->show();
    ui->pushButton_AddL->show();
    ui->pushButton_RemL->show();
    ui->pushButton_EditL->show();
}

/**
 * Cerca nella tabella delle letture i libri che contengono nei loro campi le parole
 * digitate nel campo di ricerca. Mostra solo le righe della tabella con tali criteri.
 * @param arg1 contiene il testo digitato nella barra di ricerca delle letture
 */
void Letture::barraDiRicercaLettura(const QString &arg1)
{
    QAbstractItemModel* model = ui->LettureTable->model();
    for (int row = 0; row < model->rowCount(); ++row) {
        bool match = false;
        for (int column = 0; column < model->columnCount(); ++column) {
            QModelIndex index = model->index(row, column);
            QString cellText = model->data(index, Qt::DisplayRole).toString();
            if (cellText.contains(arg1, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        ui->LettureTable->setRowHidden(row, !match);
    }
}

/**
 * Si calcola lo 0.05€ per ciascuna pagina, se il libro è in copertina flessibile,
 * e si confronta con il prezzo impostato per il libro. Si tiene il valore inferiore.
 * @param p è il prezzo proposto
 */
void Letture::calcolaPrezzoTotale(double p)
{
    double calc_prezzo;

    // Controllo copertina flessibile
    if(copertina_flessibile)
    {
        calc_prezzo = round(0.05 * nr_pagine * 100.0) / 100.0;

        // Confronto prezzo calcolato e quello passato come parametro
        if(calc_prezzo < p)
            prezzo = calc_prezzo;
        else
            prezzo = p;
    }
    else
        prezzo = p;
}
