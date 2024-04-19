#ifndef EDITLETTURE_H
#define EDITLETTURE_H

#include <QDialog>

namespace Ui {
class EditLetture;
}

class EditLetture : public QDialog
{
    Q_OBJECT

public:
    explicit EditLetture(QWidget *parent = nullptr);
    ~EditLetture();
private slots:
    void confermaModificaLettura();
    void checkFields();
private:
    Ui::EditLetture *ui;
};

#endif // EDITLETTURE_H
