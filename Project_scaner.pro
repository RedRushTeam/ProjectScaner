QT += core gui
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = bashenki.ico

SOURCES += \
    about.cpp \
    change_size.cpp \
    con_game.cpp \
    graphic_window.cpp \
    help.cpp \
    main.cpp \
    mainwindow.cpp \
    nastr_game.cpp \
    password_dialog.cpp \
    prepod_game.cpp \
    random_game.cpp

HEADERS += \
    about.h \
    change_size.h \
    con_game.h \
    graphic_window.h \
    help.h \
    list_of_types.h \
    mainwindow.h \
    nastr_game.h \
    password_dialog.h \
    prepod_game.h \
    random_game.h

FORMS += \
    about.ui \
    change_size.ui \
    con_game.ui \
    graphic_window.ui \
    help.ui \
    mainwindow.ui \
    nastr_game.ui \
    password_dialog.ui \
    random_game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

VERSION = 1.0.0
QMAKE_TARGET_COMPANY = QARASIQ_STUDIOS
QMAKE_TARGET_PRODUCT = SCANER
QMAKE_TARGET_COPYRIGHT = QARASIQ_STUDIOS

RESOURCES += \
    Textures_game.qrc
