QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bookstore.cpp \
    editeserciziario.cpp \
    editletture.cpp \
    editlibDiTesto.cpp \
    eserciziari.cpp \
    letture.cpp \
    libri_di_testo.cpp \
    libro.cpp \
    main.cpp \
    mainmenu.cpp \
    neweserciziario.cpp \
    newletture.cpp \
    newlibDiTesto.cpp

HEADERS += \
    Nodo.h \
    bookstore.h \
    container.h \
    editeserciziario.h \
    editletture.h \
    editlibditesto.h \
    eserciziari.h \
    letture.h \
    libri_di_testo.h \
    libro.h \
    lista_sl.h \
    mainmenu.h \
    neweserciziario.h \
    newletture.h \
    newlibditesto.h

FORMS += \
    bookstore.ui \
    editeserciziario.ui \
    editletture.ui \
    editlibDiTesto.ui \
    eserciziari.ui \
    letture.ui \
    libri_di_testo.ui \
    mainmenu.ui \
    neweserciziario.ui \
    newletture.ui \
    newlibDiTesto.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

RC_ICONS = bookstore.ico

DISTFILES += \
    libri.json
