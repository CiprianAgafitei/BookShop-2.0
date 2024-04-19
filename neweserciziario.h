#ifndef NEWESERCIZIARIO_H
#define NEWESERCIZIARIO_H

#include <QDialog>

namespace Ui {
class NewEserciziario;
}

class NewEserciziario : public QDialog
{
    Q_OBJECT

public:
    explicit NewEserciziario(QWidget *parent = nullptr);
    ~NewEserciziario();
private slots:
    void confermaNuovoEserciziario();
    void checkFields();
private:
    Ui::NewEserciziario *ui;
};

#endif // NEWESERCIZIARIO_H
