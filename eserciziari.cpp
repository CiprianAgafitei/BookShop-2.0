#include <QtWidgets>
#include "eserciziari.h"
#include "bookstore.h"
#include "ui_eserciziari.h"
#include "mainmenu.h"

Eserciziari::Eserciziari(QWidget *parent) :
    QDialog(parent)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    // Disabilita elementi della tabella modificabili
    ui->EserciziariTable->setEditTriggers(QTableWidget::NoEditTriggers);

    lista_sl* books = BookStore::getLibri();

    // Inserimento eserciziari in tabella
    vector<Eserciziari*> eserciziari = books->getEserciziari();
    if(eserciziari.size() > 0)
    {
        ui->EserciziariTable->setRowCount(static_cast<int>(eserciziari.size()));

        int row = 0;
        for(Eserciziari* l : eserciziari)
        {
            ui->EserciziariTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(l->isbn)));
            ui->EserciziariTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(l->titolo)));
            ui->EserciziariTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(l->materia)));
            ui->EserciziariTable->setItem(row, 3, new QTableWidgetItem(QString::number(l->difficolta)));
            ui->EserciziariTable->setItem(row, 4, new QTableWidgetItem(QString::number(l->nr_esercizi)));
            ui->EserciziariTable->setItem(row, 5, new QTableWidgetItem(QString::number(l->prezzo)));
            ui->EserciziariTable->setItem(row, 6, new QTableWidgetItem(QString::number(l->disponibilita)));
            ++row;
        }
    }

    // Centra i campi delle righe nella tabella
    for (int row = 0; row < ui->EserciziariTable->rowCount(); ++row)
    {
        for(int j = 0; j < 7; ++j)
        {
            QTableWidgetItem* item = ui->EserciziariTable->item(row, j);
            item->setTextAlignment(Qt::AlignCenter);
        }
    }

    // Nessuna riga selezionata => opzioni di modifica nascoste
    ui->pushButton_DelE->hide();
    ui->pushButton_AddE->hide();
    ui->pushButton_RemE->hide();
    ui->pushButton_EditE->hide();

    // Connect the textChanged signal of the line edit to a slot
    connect(ui->lineEditE, &QLineEdit::textChanged, this, &Eserciziari::barraDiRicercaEserciziario);
    connect(ui->EserciziariTable, &QTableWidget::clicked, this, &Eserciziari::elementoTabellaEserciziariCliccato);
}

Ui::Eserciziari *Eserciziari::ui = new Ui::Eserciziari;

Eserciziari::~Eserciziari()
{
    delete ui;
}

void Eserciziari::on_pushButton_E_clicked()
{
    hide();
    MainMenu *mainMenu = new MainMenu(this);
    mainMenu->show();
}

Eserciziari::Eserciziari(string isbn, string titolo, int disp, double prezzo, string mat, int nr_ex, int diff) : Libro(isbn, titolo, disp, prezzo), materia(mat), nr_esercizi(nr_ex), difficolta(diff) {}

/**
 * Materia dell'eserciziario selezionato.
 *
 * @return string materia dell'oggetto
 */
string Eserciziari::getMateria() {
    return materia;
}

/**
 * Numero di esercizi dell'eserciziario selezionato
 *
 * @return int numero di esercizi
 */
int Eserciziari::getNrEsercizi() {
    return nr_esercizi;
}

/**
 * Difficoltà dell'eserciziario: 1, 2 o 3
 *
 * @return int la difficoltà degli esercizi del libro
 */
int Eserciziari::getDifficolta() {
    return difficolta;
}

/**
 * Aggiorna la materia dell'eserciziario, se quella nuova è accettabile
 *
 * @param m è la nuova materia del libro
 */
void Eserciziari::updateMateria(string m) {
    // Se non nulla
    if(m.size() > 0)
        materia = m;
}

/**
 * Aggiorna il numero degli esercizi dell'eserciziario, se la quantità nuova è accettabile
 *
 * @param nre è il nuovo numero di esercizi del libro
 */
void Eserciziari::updateNrEsercizi(int nre) {
    // Se almeno un esercizio
    if(nre > 1)
        nr_esercizi = nre;
}

/**
 * Aggiorna il grado di difficoltà dell'eserciziario, a patto che sia un valore compreso nell'intervallo 1-3
 *
 * @param d è il nuovo grado di difficoltà del libro
 */
void Eserciziari::updateDiff(int d) {
    // Controllo che il nuovo grado sia nel range da 1 a 3
    if(d > 0 && d < 4)
        difficolta = d;
}

/**
 * Crea oggetto QJsonObject per la stampa su file json
 * @return un oggetto QJsonObject con le caratteristiche del libro
 */
QJsonObject Eserciziari::book4Print() {

    QJsonObject book;
    book.insert("type", "eserciziario");
    book.insert("isbn", isbn.c_str());
    book.insert("titolo", titolo.c_str());
    book.insert("disponibilita", disponibilita);
    book.insert("prezzo", prezzo);
    book.insert("materia", materia.c_str());
    book.insert("nr_esercizi", nr_esercizi);
    book.insert("difficolta", difficolta);
    return book;
}

void Eserciziari::elementoTabellaEserciziariCliccato()
{
    // Mostra le opzioni per la riga selezioanata
    ui->pushButton_DelE->show();
    ui->pushButton_AddE->show();
    ui->pushButton_RemE->show();
    ui->pushButton_EditE->show();
}

/**
 * Cerca nella tabella degli eserciziari i libri che contengono nei loro campi le parole
 * digitate nel campo di ricerca. Mostra solo le righe della tabella con tali criteri.
 * @param arg1 contiene il testo digitato nella barra di ricerca degli eserciziari
 */
void Eserciziari::barraDiRicercaEserciziario(const QString &arg1)
{
    QAbstractItemModel* model = ui->EserciziariTable->model();
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
        ui->EserciziariTable->setRowHidden(row, !match);
    }
}

/**
 * Mostra la finestra per l'inserimento dei dati per un nuovo eserciziario
 */
void Eserciziari::on_pushButton_NewE_clicked()
{
    neweserciziario = new NewEserciziario(this);
    neweserciziario->exec();
}

/**
 * Elimina il libro selezionato -> disponibile solo se la quantità è pari a 0
 */
void Eserciziari::on_pushButton_DelE_clicked()
{
    QModelIndexList selectedIndexes = ui->EserciziariTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 6) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value = ui->EserciziariTable->model()->data(ui->EserciziariTable->model()->index(selectedIndex.row(), 6));

    // Controllo disponibilità nulla
    if(value.toInt() == 0)
    {
        // MESSAGGIO di richiesta conferma
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Avviso", "Sei sicuro di voler eliminare il libro selezionato?", QMessageBox::Yes|QMessageBox::No);

        // Controllo scelta ed eliminazione del libro dalla tabella, se scelta positiva
        if (reply == QMessageBox::Yes)
        {
            QVariant value = ui->EserciziariTable->model()->data(selectedIndex);   // Ottenimento isbn libro da rimuovere

            // Rimozione dall'elenco dei libri

            BookStore::libri->pop(value.toString().toStdString());

            // Rimozione della riga selezionata dalla tabella
            ui->EserciziariTable->removeRow(selectedIndex.row());

            // Salvataggio su file dell'elenco dei libri aggiornati
            BookStore::save();
        }
    }
    else    // Disponibilità > 0
    {
        QMessageBox::warning(this, "Attenzione!", "Non è possibile rimuovere il libro selezionato in quanto la sua disponibilità non è ancora nulla.");
    }
}

void Eserciziari::on_pushButton_AddE_clicked()
{
    QModelIndexList selectedIndexes = ui->EserciziariTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 6) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value_disp = ui->EserciziariTable->model()->data(ui->EserciziariTable->model()->index(selectedIndex.row(), 6));

    QVariant value = ui->EserciziariTable->model()->data(selectedIndex);   // Ottenimento isbn libro da inserire

    // Modifica dei dati relativi al libro nella tabella
    ui->EserciziariTable->item(selectedIndex.row(), 6)->setText(QString::number(value_disp.toInt() + 1));

    // Aggiornamento della disponibilità del libro nel vettore
    BookStore::libri->aggiornaDisp(value.toString().toStdString(), 1);        // Quantità da aggiungere alla disponibilità corrente

    // Messaggio di modifica avvenuto con successo
    QMessageBox::information(this, "Avviso", "1 libro inserito con successo!");

    // Salvataggio su file delle modifiche apportate
    BookStore::save();
}

/**
 * Rimuovi 1 libro aggiornando la quantità dei libri eserciziari rimasti -> disponibile solo se la quantità è > 0
 */
void Eserciziari::on_pushButton_RemE_clicked()
{
    QModelIndexList selectedIndexes = ui->EserciziariTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 6) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value_disp = ui->EserciziariTable->model()->data(ui->EserciziariTable->model()->index(selectedIndex.row(), 6));

    // Controllo disponibilità non nulla
    if(value_disp.toInt() > 0)
    {
        QVariant value = ui->EserciziariTable->model()->data(selectedIndex);   // Ottenimento isbn libro da rimuovere

        // Rimozione di 1 libro -> aggiornamento della disponibilità del libro selezionato

        // Modifica dei dati relativi al libro nella tabella
        ui->EserciziariTable->item(selectedIndex.row(), 6)->setText(QString::number(value_disp.toInt() - 1));

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
void Eserciziari::on_pushButton_EditE_clicked()
{
    // Modifica dei campi dell'oggetto selezionato
    editeserciziario = new EditEserciziario(this);
    editeserciziario->exec();
}

/**
 * Si calcola 0.05€ per il numero di esercizi e se il valore ottenuto sarà maggiore
 * di quello proposto, allora si applicherà:
 *      - il 10% di sconto se il libro ha grado di difficoltà pari a 1,
 *      - il 20% se il grado di difficoltà è pari a 2,
 *      - il 30% se il grado di difficoltà è pari a 3.
 * @param p è il prezzo proposto
 */
void Eserciziari::calcolaPrezzoTotale(double p)
{
    double calc_prezzo = round(0.2 * nr_esercizi * 100.0) / 100.0;

    if(calc_prezzo > p)
    {
        if(difficolta == 1)
            prezzo = round((calc_prezzo - 10.0 * calc_prezzo / 100.0) * 100.0) / 100.0;  // Applicazione sconto difficoltà 1
        else if(difficolta == 2)
            prezzo = round((calc_prezzo - 20.0 * calc_prezzo / 100.0) * 100.0) / 100.0;  // Applicazione sconto difficoltà 2
        else
            prezzo = round((calc_prezzo - 30.0 * calc_prezzo / 100.0) * 100.0) / 100.0;  // Applicazione sconto difficoltà 3
    }
    else
        prezzo = calc_prezzo;
}
