#include <QtWidgets>
#include "libri_di_testo.h"
#include "bookstore.h"
#include "ui_libri_di_testo.h"
#include "mainmenu.h"

Libri_Di_Testo::Libri_Di_Testo(QWidget *parent) :
    QDialog(parent)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    // Disabilita elementi della tabella modificabili
    ui->LDTTable->setEditTriggers(QTableWidget::NoEditTriggers);

    lista_sl* books = BookStore::getLibri();

    // Inserimento dei libri di testo nella tabella
    vector<Libri_Di_Testo*> libriDiTesto = books->getLibriDiTesto();
    if(libriDiTesto.size() > 0)
    {
        ui->LDTTable->setRowCount(static_cast<int>(libriDiTesto.size()));

        int row = 0;
        for(Libri_Di_Testo* l : libriDiTesto)
        {
            ui->LDTTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(l->isbn)));
            ui->LDTTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(l->titolo)));
            ui->LDTTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(l->materia)));
            ui->LDTTable->setItem(row, 3, new QTableWidgetItem(QString::number(l->nr_argomenti)));
            ui->LDTTable->setItem(row, 4, new QTableWidgetItem(QString::number(l->livello_app)));
            ui->LDTTable->setItem(row, 5, new QTableWidgetItem(QString::number(l->prezzo)));
            ui->LDTTable->setItem(row, 6, new QTableWidgetItem(QString::number(l->disponibilita)));
            ui->LDTTable->setItem(row, 7, new QTableWidgetItem(QString::number(l->sconto)));
            ++row;
        }
    }

    // Centra i campi delle righe nella tabella
    for (int row = 0; row < ui->LDTTable->rowCount(); ++row)
    {
        for(int j = 0; j < 8; ++j)
        {
            QTableWidgetItem* item = ui->LDTTable->item(row, j);
            item->setTextAlignment(Qt::AlignCenter);
        }
    }

    // Nessuna riga selezionata => opzioni di modifica nascoste
    ui->pushButton_DelLDT->hide();
    ui->pushButton_AddLDT->hide();
    ui->pushButton_RemLDT->hide();
    ui->pushButton_EditLDT->hide();

    // Connect the textChanged signal of the line edit to a slot
    connect(ui->lineEditLDT, &QLineEdit::textChanged, this, &Libri_Di_Testo::barraDiRicercaLDT);
    connect(ui->LDTTable, &QTableWidget::clicked, this, &Libri_Di_Testo::elementoTabellaLDTCliccato);
}

Ui::Libri_Di_Testo *Libri_Di_Testo::ui = new Ui::Libri_Di_Testo;

Libri_Di_Testo::~Libri_Di_Testo()
{
    delete ui;
}

void Libri_Di_Testo::on_pushButton_LDT_clicked()
{
    hide();
    MainMenu *mainMenu = new MainMenu(this);
    mainMenu->show();
}

Libri_Di_Testo::Libri_Di_Testo(string isbn, string titolo, int disp, double prezzo, string mat, int nrArg, int lvlApp, double sc) : Libro(isbn, titolo, disp, prezzo), materia(mat), nr_argomenti(nrArg), livello_app(lvlApp), sconto(sc) {}

/**
 * Materia del libro di testo selezionato.
 *
 * @return string materia del libro
 */
string Libri_Di_Testo::getMateria() {
    return materia;
}

/**
 * Numero degli argomenti del manuale selezionato.
 *
 * @return int nr degli argomenti del libro
 */
int Libri_Di_Testo::getNrArgomenti() {
    return nr_argomenti;
}

/**
 * Livello di apprendimento consigliato per questo libro di testo
 *
 * @return int livello di apprendimento
 */
int Libri_Di_Testo::getLivelloApp() {
    return livello_app;
}

/**
 * Sconto pervisto per il libro di testo per docenti e studenti
 *
 * @return double sconto del libro di testo
 */
double Libri_Di_Testo::getSconto() {
    return sconto;
}

/**
 * Aggiorna la materia del libro di testo
 *
 * @param m è la nuova materia del libro
 */
void Libri_Di_Testo::updateMateria(string m) {
    materia = m;
}

/**
 * Aggiorna il numero degli argomenti del libro di testo
 *
 * @param na è il nuovo numero degli argomenti del libro
 */
void Libri_Di_Testo::updateNrArgomenti(int na) {
    nr_argomenti = na;
}

/**
 * Aggiorna il livello di apprendimento del libro di testo
 *
 * @param la è il nuovo livello di apprendimento del libro
 */
void Libri_Di_Testo::updateLivelloApp(int la) {
    livello_app = la;
}

/**
 * Aggiorna lo sconto del libro di testo (STUDENTI e DOCENTI)
 *
 * @param s è il nuovo sconto per il libro
 */
void Libri_Di_Testo::updateSconto(double s) {
    sconto = s;
}

/**
 * Crea oggetto QJsonObject per la stampa su file json
 * @return un oggetto QJsonObject con le caratteristiche del libro
 */
QJsonObject Libri_Di_Testo::book4Print() {

    QJsonObject book;
    book.insert("type", "libro_di_testo");
    book.insert("isbn", isbn.c_str());
    book.insert("titolo", titolo.c_str());
    book.insert("disponibilita", disponibilita);
    book.insert("prezzo", prezzo);
    book.insert("materia", materia.c_str());
    book.insert("nr_argomenti", nr_argomenti);
    book.insert("livello_app", livello_app);
    book.insert("sconto", sconto);
    return book;
}

void Libri_Di_Testo::elementoTabellaLDTCliccato()
{
    // Mostra le opzioni per la riga selezioanata
    ui->pushButton_DelLDT->show();
    ui->pushButton_AddLDT->show();
    ui->pushButton_RemLDT->show();
    ui->pushButton_EditLDT->show();
}

/**
 * Cerca nella tabella dei libri di testo i libri che contengono nei loro campi le parole
 * digitate nel campo di ricerca. Mostra solo le righe della tabella con tali criteri.
 * @param arg1 contiene il testo digitato nella barra di ricerca dei libri di testo
 */
void Libri_Di_Testo::barraDiRicercaLDT(const QString &arg1)
{
    QAbstractItemModel* model = ui->LDTTable->model();
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
        ui->LDTTable->setRowHidden(row, !match);
    }
}

/**
 * Mostra la finestra per l'inserimento dei dati per il nuovo libro di testo
 */
void Libri_Di_Testo::on_pushButton_NewLDT_clicked()
{
    newldt = new NewLDT(this);
    newldt->exec();
}

/**
 * Elimina il libro selezionato -> disponibile solo se la quantità è pari a 0
 */
void Libri_Di_Testo::on_pushButton_DelLDT_clicked()
{
    QModelIndexList selectedIndexes = ui->LDTTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 6) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value = ui->LDTTable->model()->data(ui->LDTTable->model()->index(selectedIndex.row(), 6));

    // Controllo disponibilità nulla
    if(value.toInt() == 0)
    {
        // MESSAGGIO di richiesta conferma
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Avviso", "Sei sicuro di voler eliminare il libro selezionato?", QMessageBox::Yes|QMessageBox::No);

        // Controllo scelta ed eliminazione del libro dalla tabella, se scelta positiva
        if (reply == QMessageBox::Yes)
        {
            QVariant value = ui->LDTTable->model()->data(selectedIndex);   // Ottenimento isbn libro da rimuovere

            // Rimozione dall'elenco dei libri
            BookStore::libri->pop(value.toString().toStdString());

            // Rimozione della riga selezionata dalla tabella
            ui->LDTTable->removeRow(selectedIndex.row());

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
 * Aggiornamento della disponibilità del libro selezionato -> aggiunge un libro
 */
void Libri_Di_Testo::on_pushButton_AddLDT_clicked()
{
    QModelIndexList selectedIndexes = ui->LDTTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 6) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value_disp = ui->LDTTable->model()->data(ui->LDTTable->model()->index(selectedIndex.row(), 6));

    QVariant value = ui->LDTTable->model()->data(selectedIndex);   // Ottenimento isbn libro da inserire

    // Modifica dei dati relativi al libro nella tabella
    ui->LDTTable->item(selectedIndex.row(), 6)->setText(QString::number(value_disp.toInt() + 1));

    // Aggiornamento della disponibilità del libro nel vettore
    BookStore::libri->aggiornaDisp(value.toString().toStdString(), 1);        // Quantità da aggiungere alla disponibilità corrente

    // Messaggio di modifica avvenuto con successo
    QMessageBox::information(this, "Avviso", "1 libro inserito con successo!");

    // Salvataggio su file delle modifiche apportate
    BookStore::save();
}

/**
 * Rimuovi 1 libro aggiornando la quantità dei libri di testo rimasti -> disponibile solo se la quantità è > 0
 */
void Libri_Di_Testo::on_pushButton_RemLDT_clicked()
{
    QModelIndexList selectedIndexes = ui->LDTTable->selectionModel()->selectedIndexes();    // indice riga selezionata (indici, ma la tabellaammette solo 1 selezione per volta)

    QModelIndex selectedIndex = selectedIndexes.at(0);      // PRIMA riga selezionata (unica selezione ammessa nella tabella)

    // Ottenimento della disponibilità (colonna 6) del libro per verificare se == 0 -> altrimenti non sarà possibile rimuovere il libro
    QVariant value_disp = ui->LDTTable->model()->data(ui->LDTTable->model()->index(selectedIndex.row(), 6));

    // Controllo disponibilità non nulla
    if(value_disp.toInt() > 0)
    {
        QVariant value = ui->LDTTable->model()->data(selectedIndex);   // Ottenimento isbn libro da rimuovere

        // Rimozione di 1 libro -> aggiornamento della disponibilità del libro selezionato

        // Modifica dei dati relativi al libro nella tabella
        ui->LDTTable->item(selectedIndex.row(), 6)->setText(QString::number(value_disp.toInt() - 1));

        // Aggiornamento della disponibilità del libro nel vettore
        BookStore::libri->aggiornaDisp(value.toString().toStdString(), -1);        // Quantità da aggiungere alla disponibilità corrente

        // Messaggio di modifica avvenuto con successo
        QMessageBox::information(this, "Avviso", "1 libro rimosso con successo!");

        // Salvataggio modifiche su file
        BookStore::save();
    }
    else    // Disponibilità terminata
    {
        QMessageBox::warning(this, "Attenzione!", "La disponibilità del libro selezionato è esaurita.");
    }
}

/**
 * Pulsante modifica premuto -> i campi nelle righe della tabella diventano modificabili
 */
void Libri_Di_Testo::on_pushButton_EditLDT_clicked()
{
    // Modifica dei campi dell'oggetto selezionato
    editlibroditesto = new EditLDT(this);
    editlibroditesto->exec();
}

/**
 * Applicazione di uno scoto del 50-30-20% in base
 * alla quantità disponibile nel negozio:
 *      - 20% se la quantità dei libri è <= 15
 *      - 30% se la quantità dei libri è <= 25
 *      - 50% se la quantità dei libri è > 25
 * In questo modo si favorisce la vendita dei libri
 * maggiormente presenti in termini di quantità.
 * @param p è il prezzo proposto
 */
void Libri_Di_Testo::calcolaPrezzoTotale(double p)
{
    if(disponibilita <= 15)
    {
        prezzo = round((p - 20.0 * p / 100.0) * 100.0) / 100.0;
    }
    else if(disponibilita <= 25)
    {
        prezzo = round((p - 30.0 * p / 100.0) * 100.0) / 100.0;
    }
    else
        prezzo = round((p - 50.0 * p / 100.0) * 100.0) / 100.0;
}
