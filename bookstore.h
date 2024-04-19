#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <QMainWindow>
#include "lista_sl.h"
#include "mainmenu.h"

namespace Ui {
class BookStore;
}

class BookStore : public QMainWindow
{
    Q_OBJECT

public:
    static lista_sl *libri;

    explicit BookStore(QWidget *parent = nullptr);
    ~BookStore();

    static void save();    // SAVE TO FILE
    static void load();    // LOAD BOOKS FROM FILE

    static lista_sl* getLibri();

private slots:
    void on_pushButton_enter_clicked();

private:
    Ui::BookStore *ui;
    MainMenu *mainMenu;
};

#endif // BOOKSTORE_H
