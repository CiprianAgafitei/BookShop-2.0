#ifndef NEWLIBDITESTO_H
#define NEWLIBDITESTO_H

#include <QDialog>

namespace Ui {
class NewLDT;
}

class NewLDT : public QDialog
{
    Q_OBJECT

public:
    explicit NewLDT(QWidget *parent = nullptr);
    ~NewLDT();
private slots:
    void confermaNuovoLDT();
    void checkFields();
private:
    Ui::NewLDT *ui;
};

#endif // NEWLIBDITESTO_H
