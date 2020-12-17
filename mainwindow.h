#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include "change_size.h"
#include "about.h"
#include "help.h"
#include "password_dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *mEvent);

private slots:
    void open_help_window() const;
    void open_about_window() const;
    void open_password_window();
    void open_game_window();
    void open_prep_window();
    void open_con_window();
    void open_constr_window();
private:

    ////
    myGraphicsView* view;
    QGraphicsScene* scene;
    ////

    bool is_password_true = false;
    QVBoxLayout *vbox;
    set<Pixmap *> set_of_main_menu_elements;
    QLabel *title;
    QPushButton* _pass;
    QPushButton *start_with_con;
    QPushButton *start_with_rand;
    QPushButton *start_with_settings;
    QPushButton *start_with_prep;
    QPushButton *help_;
    QPushButton *about_;
    QPushButton *exit_;
};
#endif // MAINWINDOW_H
