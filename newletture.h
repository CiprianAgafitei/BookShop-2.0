#ifndef NEWLETTURE_H
#define NEWLETTURE_H

#include <QDialog>

namespace Ui {
class NewLetture;
}

class NewLetture : public QDialog
{
    Q_OBJECT

public:
    explicit NewLetture(QWidget *parent = nullptr);
    ~NewLetture();
private slots:
    void confermaNuovaLettura();
    void checkFields();
private:
    Ui::NewLetture *ui;
};

#endif // NEWLETTURE_H
