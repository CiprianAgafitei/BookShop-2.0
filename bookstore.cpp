#include <QMessageBox>
#include <iostream>
#include <QJsonDocument>
#include "bookstore.h"
#include "mainmenu.h"
#include "ui_bookstore.h"

lista_sl *BookStore::libri = new lista_sl();

BookStore::BookStore(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BookStore)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());

    // Caricamento libri da file json (se presenti)
    load();

    // Controllo se sono stati inseriti libri nel vettore == libri presenti sul file json
    // Se no, vengono inseriti dei libri di default per prova programma
    if(libri->size() == 0)
    {
        // Inserimento libri di default per prova
        Letture* l1 = new Letture("9781409558910", "Le mille e una notte", 5, 15.70, "Raccolta di novelle", 350, true);
        Letture* l2 = new Letture("9788807901812", "Il richiamo della foresta", 3, 9.99, "Avventura", 275, true);
        Letture* l3 = new Letture("B00XWHFL02", "I tre moschettieri", 1, 4, "Storico - Avventura", 534, false);

        Libri_Di_Testo* ldt1 = new Libri_Di_Testo("9788804604235", "La leggenda di Roma", 7, 28.50, "Storia", 9, 3, 5.0);
        Libri_Di_Testo* ldt2 = new Libri_Di_Testo("9781803248776", "Cybersecurity: Attack and Defense", 12, 31.18, "Informatica", 17, 1, 0);

        Eserciziari* e1 = new Eserciziari("9791280033666", "Medicina, odontoiatria e veterinaria", 4, 33.63, "Medicina", 597, 2);
        Eserciziari* e2 = new Eserciziari("9788848311939", "Eserciziario dei verbi in inglese", 2, 8.46, "Inglese", 187, 1);
        Eserciziari* e3 = new Eserciziari("9798599656548", "Eserciziario di fisica generale", 8, 39.99, "Fisica", 630, 2);
        Eserciziari* e4 = new Eserciziari("9788875342098", "Eserciziario di Excel", 12, 36.10, "Informatica", 160, 1);

        libri->pushFront(l1);
        libri->pushFront(l2);
        libri->pushFront(l3);
        libri->pushFront(ldt1);
        libri->pushFront(ldt2);
        libri->pushFront(e1);
        libri->pushFront(e2);
        libri->pushFront(e3);
        libri->pushFront(e4);

        // Salvataggio su file dei libri
        save();
    }
}

BookStore::~BookStore()
{
    delete ui;
}

/**
 * Restituisce il vettore dei libri
 * @return il vettore con i libri
 */
lista_sl *BookStore::getLibri()
{
    return libri;
}

void BookStore::on_pushButton_enter_clicked()
{
    hide();
    mainMenu = new MainMenu(this);
    mainMenu->show();
}

/**
 * Salvataggio su documento JSON dei libri
 */
void BookStore::save()
{
    //create main object for whole json data
    QJsonArray booksArray;

    for(int i = 0; i < libri->size(); i++)
    {
        QJsonObject obj;

        Libro *libro = libri->get(i);

        // Controllo tipo dinamico del libro per inserimento su file con gli attributi di ciascuna categoria
        Letture *lettura = dynamic_cast<Letture*>(libro);
        Libri_Di_Testo *libro_di_testo = dynamic_cast<Libri_Di_Testo*>(libro);
        Eserciziari *eserciziario = dynamic_cast<Eserciziari*>(libro);

        // Inserimento dati libro
        if(lettura) {                       // Lettura
            obj = lettura->book4Print();
        }
        else if(libro_di_testo) {                       // Libro di testo
            obj = libro_di_testo->book4Print();
        }
        else if(eserciziario) {                    // Eserciziario
            obj = eserciziario->book4Print();
        }

        // Inserimento libro nell'elenco dei libri da scrivere sul file
        if(lettura || libro_di_testo || eserciziario)
            booksArray.append(obj);
    }

    // Crea un documento JSON e imposta il mainObject come oggetto del documento
    QJsonDocument document;
    document.setArray(booksArray);
    QByteArray bytes = document.toJson(QJsonDocument::Indented);

    QFile file("libri.json");

    // Salvataggio su file con messaggio di esito finale
    if (!file.open(QIODevice::WriteOnly))
    {
        // Print error message
        QMessageBox msgBox;
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Non è possibile aprire il file per salvare i libri");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }
    else {
        file.write(bytes);
        file.flush();
        file.close();
    }
}

/**
 * Lettura e caricamento dei libri da file JSON in un vettore di libri
 */
void BookStore::load()
{
    // Lettura dal file json dei libri
    QFile file("libri.json");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Print error message
        QMessageBox msgBox;
        msgBox.setWindowTitle("Errore");
        msgBox.setText("Non è stato possibile aprire il file contenente i libri");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    // file vuoto
    if(jsonData.isEmpty())
        return;

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonArray = doc.array();

    // Lettura e inserimento nel vettore dei libri della classe Bookstore
    for (const auto &jsonValue : jsonArray)
    {
        QJsonObject jsonObject = jsonValue.toObject();
        QString type = jsonObject["type"].toString();

        // Controllo categoria del libro
        if (type.toStdString() == "lettura")
        {
            // creazione lettura
            Letture *lettura = new Letture(0);
            lettura->updateISBN(jsonObject["isbn"].toString().toStdString());
            lettura->updateTitolo(jsonObject["titolo"].toString().toStdString());
            lettura->modificaDisp(jsonObject["disponibilita"].toInt());
            lettura->updatePrezzo(jsonObject["prezzo"].toDouble());

            lettura->updateGenere(jsonObject["genere"].toString().toStdString());
            lettura->updateNrPagine(jsonObject["nr_pagine"].toInt());
            lettura->updateIsCopFlex(jsonObject["copertina_flessibile"].toBool());

            // inserimento della lettura nel vettore dei libri
            libri->pushFront(lettura);
        }
        else if (type.toStdString() == "libro_di_testo")
        {
            // creazione libro di testo
            Libri_Di_Testo *libroDT = new Libri_Di_Testo(0);
            libroDT->updateISBN(jsonObject["isbn"].toString().toStdString());
            libroDT->updateTitolo(jsonObject["titolo"].toString().toStdString());
            libroDT->modificaDisp(jsonObject["disponibilita"].toInt());
            libroDT->updatePrezzo(jsonObject["prezzo"].toDouble());

            libroDT->updateMateria(jsonObject["materia"].toString().toStdString());
            libroDT->updateNrArgomenti(jsonObject["nr_argomenti"].toInt());
            libroDT->updateLivelloApp(jsonObject["livello_app"].toInt());
            libroDT->updateSconto(jsonObject["sconto"].toDouble());

            // inserimento del libro di testo nel vettore dei libri
            libri->pushFront(libroDT);
        }
        else if (type.toStdString() == "eserciziario")
        {
            // creazione eserciziario
            Eserciziari *eserciziario = new Eserciziari(0);
            eserciziario->updateISBN(jsonObject["isbn"].toString().toStdString());
            eserciziario->updateTitolo(jsonObject["titolo"].toString().toStdString());
            eserciziario->modificaDisp(jsonObject["disponibilita"].toInt());
            eserciziario->updatePrezzo(jsonObject["prezzo"].toDouble());

            eserciziario->updateMateria(jsonObject["materia"].toString().toStdString());
            eserciziario->updateNrEsercizi(jsonObject["nr_esercizi"].toInt());
            eserciziario->updateDiff(jsonObject["difficolta"].toInt());

            // inserimento dell'eserciziario nel vettore dei libri
            libri->pushFront(eserciziario);
        }
    }
}
