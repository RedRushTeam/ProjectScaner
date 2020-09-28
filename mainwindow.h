#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include "change_size.h"
#include "about.h"
#include "help.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void open_help_window() const;
    void open_about_window() const;
    void open_game_window();
    void open_prep_window();
    void open_constr_window();

};
#endif // MAINWINDOW_H
