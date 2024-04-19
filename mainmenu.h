#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>
#include "letture.h"
#include "libri_di_testo.h"
#include "eserciziari.h"

namespace Ui {
class MainMenu;
}

class MainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainMenu *ui;
    Letture *letture_screen;
    Libri_Di_Testo *libriDiTesto_screen;
    Eserciziari *eserciziari_screen;
};

#endif // MAINMENU_H
