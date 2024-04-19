#ifndef EDITESERCIZIARIO_H
#define EDITESERCIZIARIO_H

#include <QDialog>

namespace Ui {
class EditEserciziario;
}

class EditEserciziario : public QDialog
{
    Q_OBJECT

public:
    explicit EditEserciziario(QWidget *parent = nullptr);
    ~EditEserciziario();
private slots:
    void confermaModificaEserciziario();
    void checkFields();
private:
    Ui::EditEserciziario *ui;
};

#endif // EDITESERCIZIARIO_H
