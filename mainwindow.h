#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "list_of_types.h"

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
    void open_game_window() const;
    void open_constr_window() const;

};
#endif // MAINWINDOW_H
