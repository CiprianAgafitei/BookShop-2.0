#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::on_pushButton_3_clicked()
{
    hide();
    letture_screen = new Letture(nullptr);
    letture_screen->show();
}

void MainMenu::on_pushButton_1_clicked()
{
    hide();
    libriDiTesto_screen = new Libri_Di_Testo(nullptr);
    libriDiTesto_screen->show();
}

void MainMenu::on_pushButton_2_clicked()
{
    hide();
    eserciziari_screen = new Eserciziari(nullptr);
    eserciziari_screen->show();
}
