#include <QApplication>
#include "bookstore.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookStore m;
    m.show();
    return a.exec();
}
