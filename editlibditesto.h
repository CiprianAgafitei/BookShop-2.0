#ifndef EDITLIBDITESTO_H
#define EDITLIBDITESTO_H

#include <QDialog>

namespace Ui {
class EditLDT;
}

class EditLDT : public QDialog
{
    Q_OBJECT

public:
    explicit EditLDT(QWidget *parent = nullptr);
    ~EditLDT();
private slots:
    void confermaModificaLDT();
    void checkFields();
private:
    Ui::EditLDT *ui;
};

#endif // EDITLIBDITESTO_H
